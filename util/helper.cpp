#include "helper.hpp"

#include <random>
#include <QIODevice>
#include <QStyle>
#include <QRegularExpression>
#include <QDir>
#include <QSettings>
#include <QStyleFactory>
#include <QStyleHints>
#include <QTableView>

extern "C"{
#include "openssl/rand.h"
}

namespace SW {

Qt::ColorScheme Helper_t::detectSystemColorScheme() {

  return QGuiApplication::styleHints()->colorScheme();
}

QString Helper_t::hashGenerator(const QByteArray &data) noexcept{
  QCryptographicHash crypto(QCryptographicHash::Sha3_512);
  crypto.addData(data);
  return QString{crypto.result().toHex()};

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
  static QRegularExpression regex(R"(^(https?://|ftp://)?(www\.)?[a-zA-Z0-9.-]+(\.[a-zA-Z]{2,6})(/[^\s]*)?$)");
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

QPalette  Helper_t::set_Theme(Qt::ColorScheme theme) noexcept
{
  QPalette mPalette{};

  if(theme == Qt::ColorScheme::Light){
    qApp->setStyle(QStyleFactory::create("Windowsvista"));
    mPalette = QPalette();

  }else{
    qApp->setStyle(QStyleFactory::create("Fusion"));

    // --- ROLES PRINCIPALES DE FONDO Y TEXTO ---
    mPalette.setColor(QPalette::Window,          QColor(43, 48, 52));    // Gris oscuro azulado
    mPalette.setColor(QPalette::WindowText,      QColor(252, 252, 252)); // Blanco puro para lectura
    mPalette.setColor(QPalette::Base,            QColor(35, 38, 41));    // Fondo de tablas y editores
    mPalette.setColor(QPalette::AlternateBase,   QColor(43, 48, 52));    // Filas alternas
    mPalette.setColor(QPalette::ToolTipBase,     QColor(43, 48, 52));
    mPalette.setColor(QPalette::ToolTipText,     QColor(252, 252, 252));
    mPalette.setColor(QPalette::PlaceholderText, QColor(127, 140, 141)); // Gris medio
    mPalette.setColor(QPalette::Text,            QColor(252, 252, 252));

    // --- ROLES DE BOTONES ---
    mPalette.setColor(QPalette::Button,          QColor(43, 48, 52));
    mPalette.setColor(QPalette::ButtonText,      QColor(252, 252, 252));
    mPalette.setColor(QPalette::BrightText,      QColor(255, 255, 255));

    // --- SELECCIÓN Y ENLACES (Aquí brilla el verde Manjaro) ---
    mPalette.setColor(QPalette::Highlight,       QColor(22, 160, 133));          // Resaltado verde
    mPalette.setColor(QPalette::HighlightedText, QColor(255, 255, 255)); // Texto blanco sobre verde
    mPalette.setColor(QPalette::Link,            QColor(29, 153, 243));  // Azul para links
    mPalette.setColor(QPalette::LinkVisited,     QColor(155, 89, 182));  // Púrpura para visitados

    // --- ROLES DE PROFUNDIDAD (Bordes y Sombreados) ---
    mPalette.setColor(QPalette::Light,           QColor(65, 71, 77));    // Iluminación de bordes
    mPalette.setColor(QPalette::Midlight,        QColor(55, 60, 65));
    mPalette.setColor(QPalette::Mid,             QColor(40, 44, 48));
    mPalette.setColor(QPalette::Dark,            QColor(25, 28, 31));    // Sombra fuerte
    mPalette.setColor(QPalette::Shadow,          QColor(0, 0, 0));       // Negro absoluto

    // --- ESTADO DESACTIVADO (DISABLED) ---
    mPalette.setColor(QPalette::Disabled, QPalette::WindowText,    QColor(127, 140, 141));
    mPalette.setColor(QPalette::Disabled, QPalette::Text,          QColor(127, 140, 141));
    mPalette.setColor(QPalette::Disabled, QPalette::ButtonText,    QColor(127, 140, 141));
    mPalette.setColor(QPalette::Disabled, QPalette::Base,          QColor(43, 48, 52));
    mPalette.setColor(QPalette::Disabled, QPalette::Highlight,     QColor(65, 71, 77));
  }

  return mPalette;

}

void Helper_t::applyManjaroDarkColor(QTableView *table){

  if(!table) return;

  table->setStyleSheet(

    "QTableView::item:hover {"
    "    background-color: rgba(22, 160, 133, 50);" /* Verde suave al pasar el mouse */
    "}"

    );


}

QString Helper_t::encrypt(const QString& plainText, const QByteArray& key, const QByteArray& iv){

  QByteArray plainData = plainText.toUtf8();
  QByteArray encryptedData(plainData.size() + EVP_MAX_BLOCK_LENGTH, 0);
  int encryptedLen = 0;

  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  EVP_EncryptInit(ctx, EVP_aes_256_cbc(), reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));
  EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(encryptedData.data()), &encryptedLen, reinterpret_cast<const unsigned char*>(plainData.data()), static_cast<int>(plainData.size()));

  int finalLen = 0;
  EVP_EncryptFinal(ctx, reinterpret_cast<unsigned char*>(encryptedData.data()) + encryptedLen, &finalLen);
  encryptedLen += finalLen;

  EVP_CIPHER_CTX_free(ctx);

  return QString::fromUtf8(encryptedData.left(encryptedLen).toBase64());
}


QString Helper_t::decrypt(const QString& encryptedText, const QByteArray& key, const QByteArray& iv){

  QByteArray encryptedData = QByteArray::fromBase64(encryptedText.toUtf8());
  QByteArray decryptedData(encryptedData.size(), 0);
  int decryptedLen = 0;

  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  EVP_DecryptInit(ctx, EVP_aes_256_cbc(), reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));
  EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(decryptedData.data()), &decryptedLen, reinterpret_cast<const unsigned char*>(encryptedData.data()), static_cast<int>(encryptedData.size()));

  int finalLen = 0;
  EVP_DecryptFinal(ctx, reinterpret_cast<unsigned char*>(decryptedData.data()) + decryptedLen, &finalLen);
  decryptedLen += finalLen;

  EVP_CIPHER_CTX_free(ctx);

  return QString::fromUtf8(decryptedData.left(decryptedLen));
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


} // namespace SW

