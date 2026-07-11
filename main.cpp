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


bool validate{false};

/**
 * @brief createDataBase:
 * metodo que se encarga de crear labase de datos y tablas,tambien de insertar el usuario por defecto.
 * @return retorna true, si todo sale bien; en todo caso false.
 */
// bool createDataBase(){
//   QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), QStringLiteral("xxxConection"));
//   db.setDatabaseName(SW::Helper_t::AppLocalDataLocation().append("/xdatabase.db"));
//   return db.open();
// }
// bool dataBaseExists(){
//   const auto path = SW::Helper_t::AppLocalDataLocation().append("/xdatabase.db");
//   QFile file(path);
//   return file.exists();
// }

//! \brief Verifica si las tablas ya existen en PostgreSQL
bool dataBaseExists(){
  QSqlDatabase db = QSqlDatabase::database(QStringLiteral("xxxConection"));
  if(!db.isOpen()) return false;

  QSqlQuery qry(db);
  // Verificamos si la tabla 'users' existe
  return qry.exec("SELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_schema = 'public' AND table_name = 'users')") &&
		 qry.next() && qry.value(0).toBool();
}

//! \brief Crea la conexión a la base de datos PostgreSQL
bool createDataBase(){
  QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"), QStringLiteral("xxxConection"));

  // Configuración de conexión
  db.setHostName("localhost");
  db.setPort(5432);
  db.setDatabaseName("xdatabase");  // Nombre de tu base de datos
  db.setUserName("postgres");
  db.setPassword(qEnvironmentVariable("SW_DB_PASSWORD", "2311046"));  // ← CAMBIA ESTO

  if(!db.open()){
	QMessageBox::critical(nullptr, qApp->applicationName(),
						  "Error al conectar con PostgreSQL:\n" + db.lastError().text());
	return false;
  }
  return true;
}

//! \brief Crea las tablas con sintaxis PostgreSQL
bool createTables(){
  QSqlQuery qry(QSqlDatabase::database(QStringLiteral("xxxConection")));

  // Usamos GENERATED ALWAYS AS IDENTITY como en tu script
  return(qry.exec(R"(CREATE TABLE IF NOT EXISTS users(
		user_id integer NOT NULL GENERATED ALWAYS AS IDENTITY,
		user TEXT NOT NULL UNIQUE,
		password TEXT NOT NULL,
		user_profile VARCHAR(20) NOT NULL,
		rescue_type VARCHAR(40) NOT NULL,
		first_value TEXT NOT NULL,
		confirm_value TEXT NOT NULL,
		CONSTRAINT pk_user PRIMARY KEY (user_id)
	))") &&
		  qry.exec(R"(INSERT INTO users (user, password, user_profile, rescue_type, first_value, confirm_value)
				VALUES('public','public','PUBLIC','PUBLIC','PUBLIC','PUBLIC')
				ON CONFLICT (user) DO NOTHING)") &&
		  qry.exec(R"(CREATE TABLE IF NOT EXISTS urls(
		url_id integer NOT NULL GENERATED ALWAYS AS IDENTITY,
		url TEXT NOT NULL,
		"desc" TEXT,
		categoryid INTEGER NOT NULL,
		CONSTRAINT pk_url PRIMARY KEY (url_id),
		CONSTRAINT uq_url UNIQUE (url)
	))") &&
		  qry.exec(R"(CREATE TABLE IF NOT EXISTS category(
		category_id integer NOT NULL GENERATED ALWAYS AS IDENTITY,
		category_name TEXT NOT NULL,
		"desc" TEXT,
		userid INTEGER NOT NULL,
		CONSTRAINT pk_category PRIMARY KEY (category_id)
	))") &&
		  qry.exec(R"(ALTER TABLE public.urls
				ADD CONSTRAINT fk_category_urls
				FOREIGN KEY (categoryid)
				REFERENCES category(category_id))") &&
		  qry.exec(R"(ALTER TABLE public.category
				ADD CONSTRAINT fk_user_category
				FOREIGN KEY (userid)
				REFERENCES users(user_id))")
		  );
}
// bool createTables(){
//   QSqlQuery qry(QSqlDatabase::database(QStringLiteral("xxxConection")));
//   return(qry.exec(R"(CREATE TABLE users(user_id INTEGER PRIMARY KEY AUTOINCREMENT,
//                                   user TEXT NOT NULL UNIQUE,
//                                   password TEXT NOT NULL,
//                                   user_profile VARCHAR(20) NOT NULL,
//                                   rescue_type VARCHAR(40) NOT NULL,
//                                   first_value TEXT NOT NULL,
//                                   confirm_value TEXT NOT NULL))") &&

//           qry.exec(R"(INSERT INTO users VALUES(1,'public','public','PUBLIC','PUBLIC','PUBLIC','PUBLIC'))") &&
//           qry.exec(R"(CREATE TABLE urls(url_id INTEGER PRIMARY KEY AUTOINCREMENT,
//                                   url TEXT NOT NULL,
//                                   desc TEXT,
//                                   categoryid INTEGER REFERENCES category(category_id)))") &&

//           qry.exec(R"(CREATE TABLE category(category_id INTEGER PRIMARY KEY AUTOINCREMENT,
//                                   category_name TEXT NOT NULL,
//                                   desc TEXT,
//                                   userid INTEGER REFERENCES users(user_id)))")
//           );


// }



int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  a.setApplicationName(QStringLiteral("SWUrlManager"));
  a.setApplicationVersion(QStringLiteral("1.0"));
  a.setOrganizationName(QStringLiteral("SWSystem's"));
  // a.setStyle("Fusion");

  const QString serverName{a.applicationName()};
  if(SingleIntsanceManager::isRunning(serverName)){
	// QMessageBox::warning(nullptr, qApp->applicationName(), "Ya existe una instancia de la aplicación corriendo.");
	return -1;
  }

  if(!SingleIntsanceManager::initServer(serverName)){
	QMessageBox::critical(nullptr, qApp->applicationName(), "No se pudo iniciar el control de instancia única.");
	return -1;
  }


  //Creacion de la carpeta de la aplicación
  QDir dir(SW::Helper_t::AppLocalDataLocation());
  if(!dir.exists()){
	if(SW::Helper_t::createDataBase_dir())
	  qInfo() << "Carpeta del sistema creado!";
  }

  if(!dataBaseExists()){
	createDataBase();
	createTables();
	validate = true;
	qInfo() << "Todo los datos y tablas fueron creadas!";

  }
  if(!validate){
	createDataBase();
  }



  MainForm w;
  w.setWindowTitle(a.applicationName());
  w.show();
  return a.exec();
}
