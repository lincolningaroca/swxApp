#include "configdialog.hpp"
#include "helperdatabase/helperdb.hpp"
#include "mainform.hpp"
#include "util/helper.hpp"

#include <QApplication>
#include <QDir>
#include <QFontDatabase>
#include <QLocalServer>
#include <QLocalSocket>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QUrl>

constexpr int MIN_POSTGRESQL_VERSION = 17;
const QString PG_DOWNLOAD_URL = QStringLiteral("https://www.postgresql.org/download/");

/**
 * @brief Comprueba la existencia y versión mínima del motor PostgreSQL en el cliente.
 * @return true si la verificación es exitosa; false si debe cerrarse el programa.
 */
bool verifyPostgreSQLRequirement() {

  auto pgStatus = SW::Helper_t::checkPostgresqlInstallation();

  if (!pgStatus.isInstalled) {
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle(qApp->applicationName());
	msgBox.setText(QStringLiteral("<b>PostgreSQL no está instalado en el sistema.</b>"));
	msgBox.setInformativeText(
	  QStringLiteral("Esta aplicación requiere el motor de base de datos PostgreSQL (versión %1 o superior) para funcionar.\n\n"
					 "¿Desea abrir el sitio oficial de PostgreSQL para descargarlo?")
		.arg(MIN_POSTGRESQL_VERSION));
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);

	if (msgBox.exec() == QMessageBox::Yes) {
	  if(!SW::Helper_t::open_Url(QUrl(PG_DOWNLOAD_URL))){
		qWarning() << "No se pudo abrir el navegador web predeterminado.";
	  }
	}
	return false;
  }

  if (pgStatus.majorVersion > 0 && pgStatus.majorVersion < MIN_POSTGRESQL_VERSION) {
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setWindowTitle(qApp->applicationName());
	msgBox.setText(QStringLiteral("<b>Versión de PostgreSQL incompatible.</b>"));
	msgBox.setInformativeText(
	  QStringLiteral("Se detectó PostgreSQL versión %1 en su equipo.\n"
					 "Esta aplicación requiere como mínimo la versión %2.\n\n"
					 "Por favor, actualice su instalación de PostgreSQL desde el sitio oficial.")
		.arg(pgStatus.majorVersion)
		.arg(MIN_POSTGRESQL_VERSION));
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);

	if (msgBox.exec() == QMessageBox::Yes) {
	  if(!SW::Helper_t::open_Url(QUrl(PG_DOWNLOAD_URL))){
		qWarning() << "No se pudo abrir el navegador web predeterminado.";
	  }
	}
	return false;
  }

  return true;
}

/**
 * @brief The SingleIntsanceManager class
 * Esta estructura determina si hay una instancia de la apliacion abierta;
 * si es asi ya no se vuelve a lanzar otra app.
 */
struct SingleIntsanceManager{

  static bool isRunning(const QString& serverName){

	QLocalSocket socket{};
	socket.connectToServer(serverName);

	if(socket.waitForConnected(500)){
	  socket.disconnectFromServer();
	  return true;
	}
	return false;
  }

  static bool initServer(const QString& serverName, QObject* parent = nullptr){

	auto* server = new QLocalServer(parent);
	QLocalServer::removeServer(serverName);

	if(!server->listen(serverName)){
	  delete server;
	  return false;
	}
	return true;
  }
};


/**
 * @brief connectToDatabase
 * Establece la conexión a la base de datos PostgreSQL existente
 * @return true si la conexión fue exitosa
 */

// bool connectToDatabase(){
//   // Intenta conectar con la configuración existente
//   auto tryConnect = []() -> bool {
// 	const auto config = SW::Helper_t::loadDbConfig();

// 	if (QSqlDatabase::contains(QStringLiteral("xxxConection"))) {
// 	  QSqlDatabase::removeDatabase(QStringLiteral("xxxConection"));
// 	}

// 	QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"), QStringLiteral("xxxConection"));
// 	db.setHostName(config.host);
// 	db.setPort(config.port);
// 	db.setDatabaseName(config.dbName);
// 	db.setUserName(config.userName);
// 	db.setPassword(config.password);

// 	return db.open();
//   };

  // if (tryConnect()) {
// 	return true;
//   }

//   // Si no pudo conectar, abrir el diálogo de configuración para pedir credenciales
//   QMessageBox::warning(nullptr, qApp->applicationName(),
// 					   QStringLiteral("No se pudo conectar a la base de datos. Por favor revise las credenciales."));

//   ConfigDialog dlg(SW::Helper_t::detectSystemColorScheme(), true);
//   dlg.setCurrentPage(2); // Abre en la pestaña 2 (Base de datos)

//   if (dlg.exec() == QDialog::Accepted) {
// 	// Reintentar conexión con los nuevos datos guardados
// 	if (tryConnect()) {
// 	  return true;
// 	}
//   }

//   QMessageBox::critical(nullptr, qApp->applicationName(),
// 						QStringLiteral("Imposible continuar sin conexión a la base de datos."));
//   return false;
// }
/**
 * @brief connectToDatabase
 * Establece la conexión principal de la app usando la configuración guardada
 */
bool connectToDatabase(const DbConfig& config) {
  const QString connectionName = QStringLiteral("xxxConection");

  if (QSqlDatabase::contains(connectionName)) {
	QSqlDatabase::removeDatabase(connectionName);
  }

  QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"), connectionName);
  db.setHostName(config.host);
  db.setPort(config.port);
  db.setDatabaseName(config.dbName);
  db.setUserName(config.userName);
  db.setPassword(config.password);

  if (!db.open()) {
	qCritical() << "Error abriendo conexión principal:" << db.lastError().text();
	return false;
  }

  return true;
}

/**
 * @brief publicUserExists
 * Verifica si el usuario 'public' existe en la tabla users
 * @return true si el usuario existe
 */
bool publicUserExists(){
  QSqlDatabase db = QSqlDatabase::database(QStringLiteral("xxxConection"));
  if(!db.isOpen()) return false;

  QSqlQuery qry(db);
  qry.prepare(R"(SELECT fn_user_exists(?))");
  qry.addBindValue(QStringLiteral("public"));

  if(qry.exec() && qry.next()){
	return qry.value(0).toBool();
  }

  return false;
}

/**
 * @brief initializeDefaultData
 * Carga y ejecuta el script SQL de inicialización desde los recursos de la aplicación
 * @return true si la ejecución fue exitosa o si los datos ya existían
 */
bool initializeDefaultData(){
  // Verificar si el usuario 'public' ya existe
  if(publicUserExists()){
	qInfo() << "El usuario 'public' ya existe. No se requiere inicialización.";
	return true;
  }

  // Cargar el script SQL desde los recursos
  QFile file(":/database/seed.sql");
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
	QMessageBox::critical(nullptr, qApp->applicationName(),
						  "Error al cargar el script de inicialización:\n" + file.errorString());
	return false;
  }

  QTextStream in(&file);
  QString sqlScript = in.readAll();
  file.close();

  // Ejecutar el script
  QSqlDatabase db = QSqlDatabase::database(QStringLiteral("xxxConection"));
  QSqlQuery qry(db);

  if(!qry.exec(sqlScript)){
	QMessageBox::critical(nullptr, qApp->applicationName(),
						  "Error al ejecutar el script de inicialización:\n" + qry.lastError().text());
	return false;
  }

  qInfo() << "Usuario 'public' inicializado correctamente!";
  return true;
}


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setApplicationName(QStringLiteral("SWUrlManager"));
  a.setApplicationVersion(QStringLiteral("1.0"));
  a.setOrganizationName(QStringLiteral("SWSystem's"));


  // Instalar el interceptor de Logs de Qt
  qInstallMessageHandler(SW::customLogHandler);

  qInfo() << "============================================";
  qInfo() << "Iniciando aplicación:" << a.applicationName() << a.applicationVersion();

  const QString serverName{a.applicationName()};
  if(SingleIntsanceManager::isRunning(serverName)){
	return -1;
  }

  if(!SingleIntsanceManager::initServer(serverName, &a)){
	QMessageBox::critical(nullptr, qApp->applicationName(), "No se pudo iniciar el control de instancia única.");
	return -1;
  }


  // 1. Conectar a la base de datos PostgreSQL
  if(!verifyPostgreSQLRequirement()){
	return -1;
  }

  auto config = SW::Helper_t::loadDbConfig();

  qDebug() << "config.host:"     << config.host;
  qDebug() << "config.port:"     << config.port;
  qDebug() << "config.dbName:"   << config.dbName;
  qDebug() << "config.userName:" << config.userName;
  qDebug() << "config.password está vacío:" << config.password.isEmpty();
  qDebug() << "hasDbConfig:"     << SW::Helper_t::hasDbConfig();

  if (!SW::HelperDataBase_t::ensureDatabaseAndSchemaReady(config)) {
	QMessageBox::critical(nullptr, SW::Helper_t::appName(),
						  QStringLiteral("No se pudo preparar la base de datos para la aplicación. El programa se cerrará."));
	return -1;
  }

  // 2. Conectar a la base de datos PostgreSQL
  qInfo() << "Conectando a PostgreSQL...";
  if(!connectToDatabase(config)){
	return -1;
  }

  // 3. Verificar e inicializar datos por defecto (usuario 'public')
  qInfo() << "Verificando usuario 'public'...";
  if(!initializeDefaultData()){
	return -1;
  }

  //Creacion de la carpeta de la aplicación
  QDir dir(SW::Helper_t::AppLocalDataLocation());
  if(!dir.exists()){
	if(SW::Helper_t::createDataBase_dir())
	  qInfo() << "Carpeta del sistema creado!";
  }

  qInfo() << "Creando MainForm...";
  MainForm w;
  qInfo() << "MainForm creado. Estableciendo título...";

  w.setWindowTitle(a.applicationName());
  qInfo() << "Mostrando MainForm...";

  w.show();
  qInfo() << "MainForm mostrado. Iniciando event loop...";

  int result = a.exec();
  qInfo() << "Event loop terminado con código:" << result;

  return result;
}
