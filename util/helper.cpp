#include "helper.hpp"

#include <QDir>
#include <QFileInfo>
#include <QIODevice>
#include <QMutex>
#include <QPainter>
#include <QPixmap>
#include <QProcess>
#include <QRegularExpression>
#include <QSettings>
#include <QStyle>
#include <QStyleFactory>
#include <QStyleHints>
#include <QSvgRenderer>
#include <QTextStream>
#include <random>

extern "C"{
#include "openssl/rand.h"
}

namespace SW {



// En util/helper.cpp
QString Helper_t::deriveEncryptionKey() noexcept {

  // Material único por instalación — no hardcodeado
  const auto machineId  = QSysInfo::machineUniqueId();
  const auto orgName    = qApp->organizationName().toLatin1();
  const auto appName    = qApp->applicationName().toLatin1();

  // Salt desde datos del sistema
  const QByteArray salt = machineId + orgName + appName;

  // Passphrase base — no es la clave final
  const QByteArray passphrase = machineId + QByteArray("SWSystem's_xApp");

  // Derivar clave con PBKDF2-SHA256 — 100000 iteraciones
  QByteArray derived(32, 0);  // 256 bits

  PKCS5_PBKDF2_HMAC(
	passphrase.constData(),
	static_cast<int>(passphrase.size()),
	reinterpret_cast<const unsigned char*>(salt.constData()),
	static_cast<int>(salt.size()),
	100000,
	EVP_sha256(),
	32,
	reinterpret_cast<unsigned char*>(derived.data())
	);

  return QString::fromLatin1(derived.toHex());
}

QColor Helper_t::currentIconColor(Qt::ColorScheme scheme) noexcept {
  bool isDark = false;
  if (scheme == Qt::ColorScheme::Dark) {
	isDark = true;
  } else if (scheme == Qt::ColorScheme::Light) {
	isDark = false;
  } else {
	// Unknown → detectar por paleta
	const QColor windowColor = qApp->palette().color(QPalette::Window);
	isDark = (windowColor.lightness() < 128);
  }
  return isDark ? QColor(220, 220, 220) : QColor(30, 30, 30);
}

QColor Helper_t::currentIconColor() noexcept {
  // Sin parámetro → siempre por paleta (para forms sin esquema explícito)
  const QColor windowColor = qApp->palette().color(QPalette::Window);
  return (windowColor.lightness() < 128) ? QColor(220, 220, 220) : QColor(30, 30, 30);
}

PgCheckResult Helper_t::checkPostgresqlInstallation() noexcept {
  PgCheckResult result;

  // 1. Determinar la ruta ejecutable de psql
  QString psqlExecutable = QStringLiteral("psql");

#ifdef Q_OS_WIN
  // Si no está en el PATH, buscar en los directorios por defecto en Windows
  QProcess checkPath;
  checkPath.start(psqlExecutable, {QStringLiteral("--version")});
  if (!checkPath.waitForStarted(1000)) {
	// Buscar versiones comunes (18, 17, 16, 15...) en Program Files
	const QString programFiles = qEnvironmentVariable("ProgramFiles", QStringLiteral("C:\\Program Files"));
	for (int ver = 20; ver >= 14; --ver) {
	  QString candidate = QStringLiteral("%1/PostgreSQL/%2/bin/psql.exe").arg(programFiles).arg(ver);
	  if (QFileInfo::exists(candidate)) {
		psqlExecutable = candidate;
		break;
	  }
	}
  }
#endif

  // 2. Ejecutar la comprobación con el binario hallado
  QProcess process;
  process.start(psqlExecutable, {QStringLiteral("--version")});

  if (!process.waitForStarted(1000) || !process.waitForFinished(3000)) {
	result.isInstalled = false;
	return result;
  }

  if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
	result.isInstalled = false;
	return result;
  }

  QString output = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
  result.rawOutput = output;

  static QRegularExpression rxVersion(R"(psql\s+\(PostgreSQL\)\s+(\d+)\.)", QRegularExpression::CaseInsensitiveOption);
  auto match = rxVersion.match(output);

  if (match.hasMatch()) {
	result.isInstalled = true;
	result.majorVersion = match.captured(1).toInt();
  } else {
	result.isInstalled = true;
	result.majorVersion = 0;
  }

  return result;
}


Qt::ColorScheme Helper_t::detectSystemColorScheme() {

  return QGuiApplication::styleHints()->colorScheme();
}

QByteArray Helper_t::setColorReg(const QString& color) noexcept
{
  QByteArray data;
  QDataStream dataStream(&data, QIODevice::WriteOnly);
  dataStream << color;
  return data;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
QString Helper_t::getColorReg(QByteArray dataColor) noexcept
{
  QDataStream dataStream(&dataColor, QIODevice::ReadOnly);
  QString color;
  dataStream >> color;

  return color;

}

bool Helper_t::urlValidate(QStringView url) noexcept
{
  static QRegularExpression regex(
	R"(^(https?://|ftp://)(www\.)?[a-zA-Z0-9]([a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?)*\.[a-zA-Z]{2,10}(:[0-9]{1,5})?(/[^\s]*)?$)");
  auto match = regex.matchView(url);
  return match.hasMatch();
}

bool Helper_t::createDataBase_dir() noexcept{

  auto appLocation = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  QDir docDir(appLocation);

  return docDir.mkpath(QStringLiteral("xxxdatabase"));

}

QString Helper_t::generateSecurePassword(uint32_t length) noexcept{

  const QString chars = R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*?:{}|<>~-_=+[]/;\)";
  const int lowercaseEnd = 26;
  const int uppercaseEnd = 52;
  const int numbersEnd = 62;

  QString password;

  // Generar bytes aleatorios
  QByteArray randomBytes(length, 0);
  if (RAND_bytes(reinterpret_cast<unsigned char*>(randomBytes.data()), length) != 1) {
	qFatal("Error al generar bytes aleatorios con OpenSSL");
  }

  // Asegurar un carácter de cada tipo
  password += chars[static_cast<unsigned char>(randomBytes[0]) % lowercaseEnd];
  password += chars[lowercaseEnd + (static_cast<unsigned char>(randomBytes[1]) % (uppercaseEnd - lowercaseEnd))];
  password += chars[uppercaseEnd + (static_cast<unsigned char>(randomBytes[2]) % (numbersEnd - uppercaseEnd))];
  password += chars[numbersEnd + (static_cast<unsigned char>(randomBytes[3]) % (chars.length() - numbersEnd))];

  // Llenar el resto de la contraseña
  for (uint32_t i = 4; i < length; ++i) {
	password += chars[static_cast<unsigned char>(randomBytes[i]) % chars.length()];
  }

  // Mezclar los caracteres
  std::shuffle(password.begin(), password.end(), std::default_random_engine(static_cast<unsigned long>(randomBytes[0])));

  return password;


}

bool Helper_t::isPasswordSecure(const QString &password) noexcept{

  static QRegularExpression passwordRegex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%^&*(),.?\":{}|<>])[A-Za-z\d!@#$%^&*(),.?\":{}|<>]{8,}$)");

  return passwordRegex.match(password).hasMatch();

}

void  Helper_t::set_Theme(Qt::ColorScheme theme) noexcept{

#ifdef Q_OS_LINUX
  if (qApp->style()->objectName().toLower() != "fusion") {
	qApp->setStyle(QStyleFactory::create("Fusion"));
  }
#endif

  auto *hints = QGuiApplication::styleHints();

  switch (theme) {
	case Qt::ColorScheme::Dark:
	  hints->setColorScheme(Qt::ColorScheme::Dark);
	  break;
	case Qt::ColorScheme::Light:
	  hints->setColorScheme(Qt::ColorScheme::Light);
	  break;
	case Qt::ColorScheme::Unknown:
	default:
	  hints->setColorScheme(Qt::ColorScheme::Unknown);
	  break;
  }



}
QIcon SW::Helper_t::svgIcon(const QString& resourcePath,
							const QColor& color,
							const QSize& size) noexcept {
  QFile file(resourcePath);
  if (!file.open(QIODevice::ReadOnly))
	return QIcon();

  QString svgContent = QString::fromUtf8(file.readAll());
  svgContent.replace(QLatin1String("currentColor"), color.name());

  QSvgRenderer renderer(svgContent.toUtf8());
  if (!renderer.isValid())
	return QIcon();

  // Pixmap normal (estado activo / On)
  QPixmap pixmapOn(size);
  pixmapOn.fill(Qt::transparent);
  QPainter painterOn(&pixmapOn);
  painterOn.setOpacity(1.0);
  renderer.render(&painterOn);
  painterOn.end();

  // Pixmap inactivo (estado Off) - misma forma pero con opacidad reducida
  QPixmap pixmapOff(size);
  pixmapOff.fill(Qt::transparent);
  QPainter painterOff(&pixmapOff);
  painterOff.setOpacity(0.85);  // 35% de opacidad para estado Off
  renderer.render(&painterOff);
  painterOff.end();

  // Pixmap deshabilitado - aún más tenue
  QPixmap pixmapDisabled(size);
  pixmapDisabled.fill(Qt::transparent);
  QPainter painterDis(&pixmapDisabled);
  painterDis.setOpacity(0.45);  // 20% para disabled
  renderer.render(&painterDis);
  painterDis.end();

  QIcon icon;
  icon.addPixmap(pixmapOn,       QIcon::Normal,   QIcon::On);
  icon.addPixmap(pixmapOff,      QIcon::Normal,   QIcon::Off);
  icon.addPixmap(pixmapOn,       QIcon::Active,   QIcon::On);
  icon.addPixmap(pixmapOff,      QIcon::Active,   QIcon::Off);
  icon.addPixmap(pixmapOn,       QIcon::Selected, QIcon::On);
  icon.addPixmap(pixmapOff,      QIcon::Selected, QIcon::Off);
  icon.addPixmap(pixmapDisabled, QIcon::Disabled, QIcon::On);
  icon.addPixmap(pixmapDisabled, QIcon::Disabled, QIcon::Off);


  return icon;
}

QIcon SW::Helper_t::svgIcon(const QString& resourcePath,
							const QColor& color) noexcept {
  return svgIcon(resourcePath, color, QSize(24, 24));
}


QString Helper_t::encrypt(const QString& plainText, const QByteArray& key, const QByteArray& iv){

  const QByteArray& k = key.isEmpty() ? encryptKey() : key;
  const QByteArray& i = iv.isEmpty()  ? encryptIv()  : iv;

  QByteArray plainData = plainText.toUtf8();
  QByteArray encryptedData(plainData.size() + EVP_MAX_BLOCK_LENGTH, 0);
  int encryptedLen = 0;

  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  EVP_EncryptInit(ctx, EVP_aes_256_cbc(), reinterpret_cast<const unsigned char*>(k.data()), reinterpret_cast<const unsigned char*>(i.data()));
  EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(encryptedData.data()), &encryptedLen, reinterpret_cast<const unsigned char*>(plainData.data()), static_cast<int>(plainData.size()));

  int finalLen = 0;
  EVP_EncryptFinal(ctx, reinterpret_cast<unsigned char*>(encryptedData.data()) + encryptedLen, &finalLen);
  encryptedLen += finalLen;

  EVP_CIPHER_CTX_free(ctx);

  return QString::fromUtf8(encryptedData.left(encryptedLen).toBase64());
}


QString Helper_t::decrypt(const QString& encryptedText, const QByteArray& key, const QByteArray& iv){

  const QByteArray& k = key.isEmpty() ? encryptKey() : key;
  const QByteArray& i = iv.isEmpty()  ? encryptIv()  : iv;

  QByteArray encryptedData = QByteArray::fromBase64(encryptedText.toUtf8());
  QByteArray decryptedData(encryptedData.size(), 0);
  int decryptedLen = 0;

  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  EVP_DecryptInit(ctx, EVP_aes_256_cbc(), reinterpret_cast<const unsigned char*>(k.data()), reinterpret_cast<const unsigned char*>(i.data()));
  EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(decryptedData.data()), &decryptedLen, reinterpret_cast<const unsigned char*>(encryptedData.data()), static_cast<int>(encryptedData.size()));

  int finalLen = 0;
  EVP_DecryptFinal(ctx, reinterpret_cast<unsigned char*>(decryptedData.data()) + decryptedLen, &finalLen);
  decryptedLen += finalLen;

  EVP_CIPHER_CTX_free(ctx);

  return QString::fromUtf8(decryptedData.left(decryptedLen));
}


void Helper_t::saveDbConfig(const DbConfig& config) noexcept {

  QSettings settings(qApp->organizationName(), qApp->applicationName());
  settings.beginGroup(QStringLiteral("Database"));

  settings.setValue(QStringLiteral("host"),     config.host);
  settings.setValue(QStringLiteral("port"),     config.port);
  settings.setValue(QStringLiteral("dbName"),   config.dbName);
  settings.setValue(QStringLiteral("userName"), config.userName);

  // Password cifrado con clave derivada del hardware
  settings.setValue(QStringLiteral("password"),
					config.password.isEmpty() ? QString() : encrypt(config.password));

  settings.endGroup();
}

DbConfig Helper_t::loadDbConfig() noexcept{

  QSettings settings(qApp->organizationName(), qApp->applicationName());
  settings.beginGroup("Database");
  DbConfig config;
  config.host     = settings.value("host",     "localhost").toString();
  config.port     = settings.value("port",     5432).toInt();
  config.dbName   = settings.value("dbName",   "xdatabase").toString();
  config.userName = settings.value("userName", "postgres").toString();
  config.password = decrypt(settings.value("password", "").toString());
  settings.endGroup();
  return config;

}

bool Helper_t::hasDbConfig() noexcept{

  QSettings settings(qApp->organizationName(), appName());
  return settings.contains("Database/host");

}

QString Helper_t::getLastOpenedDirectory(){

  QSettings settings(qApp->organizationName(), qApp->applicationName());
  auto ret = readData(settings.value("lastOpenedDirectory", QDir::homePath()).toByteArray());
  return ret.toString();

}

void Helper_t::setLastOpenedDirectory(const QString &directory){

  QSettings settings(qApp->organizationName(), qApp->applicationName());
  settings.setValue("lastOpenedDirectory", writeData(directory));
}

QByteArray Helper_t::writeData(const QVariant &data){
  QByteArray data_{};
  QDataStream out{&data_, QIODevice::WriteOnly};
  out.setVersion(QDataStream::Qt_6_2);
  out << data;
  return data_;

}

bool Helper_t::nativeRegistryKeyExists(const QString &path) {
  // Usamos el formato Nativo y el nombre de tu organización/app
  // Esto apunta a HKEY_CURRENT_USER\Software\SWSystem's\xxxApp
  QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QApplication::organizationName(), appName());

  // contains() es muy potente en Qt:
  // Si le pasas "Theme", verifica si existe el grupo o carpeta.
  // Si le pasas "Theme/ColorMode", verifica si existe esa clave específica dentro.
  return settings.contains(path) || settings.childGroups().contains(path);
}

QVariant Helper_t::readData(QByteArray &&data){

  QVariant data_{};
  QDataStream in(&data, QIODevice::ReadOnly);
  in.setVersion(QDataStream::Qt_6_2);
  in >> data_;
  return data_;

}

void customLogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){

  static QMutex mutex;
  QMutexLocker locker(&mutex);

  // Carpeta de logs dentro de la ubicación local de la app
  const QString logDirPath = Helper_t::AppLocalDataLocation() + QStringLiteral("/logs");
  QDir dir(logDirPath);
  if (!dir.exists()) {
	dir.mkpath(QStringLiteral("."));
  }

  // Nombre de archivo diario: app_YYYY-MM-DD.log
  const QString fileName = QStringLiteral("%1/app_%2.log")
							 .arg(logDirPath, QDate::currentDate().toString(QStringLiteral("yyyy-MM-dd")));

  QFile logFile(fileName);
  if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
	return;
  }

  QTextStream out(&logFile);
  out.setEncoding(QStringConverter::Utf8);

  const QString timeStamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss.zzz"));

  QString levelTxt;
  switch (type) {
	case QtDebugMsg:    levelTxt = QStringLiteral("DEBUG"); break;
	case QtInfoMsg:     levelTxt = QStringLiteral("INFO "); break;
	case QtWarningMsg:  levelTxt = QStringLiteral("WARN "); break;
	case QtCriticalMsg: levelTxt = QStringLiteral("CRIT "); break;
	case QtFatalMsg:    levelTxt = QStringLiteral("FATAL"); break;
  }

  out << QStringLiteral("[%1] [%2] %3\n").arg(timeStamp, levelTxt, msg);

#ifndef NDEBUG
  if (context.file) {
	out << QStringLiteral("    (En %1:%2, %3)\n")
	.arg(QString::fromUtf8(context.file))
	  .arg(context.line)
	  .arg(QString::fromUtf8(context.function));
  }
#endif

  out.flush();
  logFile.close();

}




} // namespace SW

