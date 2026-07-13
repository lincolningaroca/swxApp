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

  static bool initServer(const QString & serverName){

	auto* server = new QLocalServer();
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
bool connectToDatabase(){
  QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"), QStringLiteral("xxxConection"));

  // TODO: Cargar estas credenciales desde QSettings o archivo de configuración
  db.setHostName("localhost");
  db.setPort(5432);
  db.setDatabaseName("xdatabase");
  db.setUserName("postgres");
  db.setPassword(qEnvironmentVariable("SW_DB_PASSWORD", "2311046"));  // ← CAMBIAR

  if(!db.open()){
	QMessageBox::critical(nullptr, qApp->applicationName(),
						  "Error al conectar con PostgreSQL:\n" + db.lastError().text());
	return false;
  }

  qInfo() << "Conexión exitosa a PostgreSQL!";
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
  qry.prepare(R"(SELECT COUNT(*) FROM users WHERE user_name = 'public')");

  if(qry.exec() && qry.next()){
	return (qry.value(0).toInt() > 0);
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
 //  QApplication a(argc, argv);

 //  a.setApplicationName(QStringLiteral("SWUrlManager"));
 //  a.setApplicationVersion(QStringLiteral("1.0"));
 //  a.setOrganizationName(QStringLiteral("SWSystem's"));

 //  const QString serverName{a.applicationName()};
 //  if(SingleIntsanceManager::isRunning(serverName)){
	// // QMessageBox::warning(nullptr, qApp->applicationName(), "Ya existe una instancia de la aplicación corriendo.");
	// return -1;
 //  }

 //  if(!SingleIntsanceManager::initServer(serverName)){
	// QMessageBox::critical(nullptr, qApp->applicationName(), "No se pudo iniciar el control de instancia única.");
	// return -1;
 //  }

 //  // 1. Conectar a la base de datos PostgreSQL
 //  if(!connectToDatabase()){
	// return -1;
 //  }

 //  // 2. Verificar e inicializar datos por defecto (usuario 'public')
 //  if(!initializeDefaultData()){
	// return -1;
 //  }

 //  //Creacion de la carpeta de la aplicación
 //  QDir dir(SW::Helper_t::AppLocalDataLocation());
 //  if(!dir.exists()){
	// if(SW::Helper_t::createDataBase_dir())
	//   qInfo() << "Carpeta del sistema creado!";
 //  }



 //  MainForm w;
 //  w.setWindowTitle(a.applicationName());
 //  w.show();
 //  return a.exec();
 QApplication a(argc, argv);
 a.setApplicationName(QStringLiteral("SWUrlManager"));
 a.setApplicationVersion(QStringLiteral("1.0"));
 a.setOrganizationName(QStringLiteral("SWSystem's"));

 const QString serverName{a.applicationName()};
 if(SingleIntsanceManager::isRunning(serverName)){
   return -1;
 }
 if(!SingleIntsanceManager::initServer(serverName)){
   QMessageBox::critical(nullptr, qApp->applicationName(), "No se pudo iniciar el control de instancia única.");
   return -1;
 }

 // 1. Conectar a la base de datos PostgreSQL
 qInfo() << "Conectando a PostgreSQL...";
 if(!connectToDatabase()){
   return -1;
 }

 // 2. Verificar e inicializar datos por defecto (usuario 'public')
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
