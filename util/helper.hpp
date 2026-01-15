#pragma once

#include <QStandardPaths>
#include <QCryptographicHash>
#include <QStringView>
#include <QDesktopServices>
#include <QApplication>
#include <QPalette>

class QTableView;

namespace SW {

enum class [[deprecated("Usar mejor Qt::ColorScheme")]] Theme{ Light_Mode, Dark_Mode };
enum class SessionStatus{ Session_start, Session_closed };
enum class User{ U_public, U_user };
enum class AuthType{ Numeric_pin, Secret_Question };

struct Helper_t{

  explicit Helper_t() = delete;

  Helper_t(const Helper_t&) = delete;
  Helper_t(Helper_t&&) = delete;
  Helper_t& operator=(const Helper_t&) = delete;
  Helper_t& operator=(Helper_t&&) = delete;

  [[nodiscard]]static bool verify_Values(const QStringView text1, const QStringView text2) noexcept{return (text1.toString() == text2.toString());}
  [[nodiscard]]static bool open_Url(const QUrl& url) noexcept{return QDesktopServices::openUrl(url);}
  [[nodiscard]]static bool urlValidate(QStringView url) noexcept;


  [[nodiscard]]static bool createDataBase_dir() noexcept;

  [[nodiscard]]static QString generateSecurePassword(uint32_t length = 8) noexcept;
  [[nodiscard]]static bool isPasswordSecure(const QString& password) noexcept;


  [[nodiscard]]static QByteArray setColorReg(const QString &color) noexcept;
  [[nodiscard]]static QString getColorReg(QByteArray dataColor) noexcept;

  [[nodiscard]]static QString hashGenerator(const QByteArray&) noexcept;

  [[nodiscard]]static QPalette set_Theme(Qt::ColorScheme theme) noexcept;

  // [[nodiscard]]static Qt::ColorScheme checkSystemColorScheme() noexcept;
  [[nodiscard]]static Qt::ColorScheme detectSystemColorScheme();
  static void applyManjaroDarkColor(QTableView* table);



  //var member

  inline static const QHash<Qt::ColorScheme, QString> lblColorMode{

    {Qt::ColorScheme::Light, "#008cf9"},
      {Qt::ColorScheme::Dark, "#16A085"}
  };

  [[nodiscard]]static QString AppLocalDataLocation(){return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation).append(dbDir_name);}
  [[nodiscard]]static QString app_pathLocation(){return QApplication::applicationDirPath();}
  [[nodiscard]]static QString appName(){return QApplication::applicationName();}

  static void setLastOpenedDirectory(const QString &directory);
  [[nodiscard]]static QString getLastOpenedDirectory();

  [[nodiscard]] static QVariant readData(QByteArray&& data);
  [[nodiscard]]static QByteArray writeData(const QVariant& data);

  static bool nativeRegistryKeyExists(const QString &path);

  //encryp/decrypt metods

  static QString encrypt(const QString& plainText, const QByteArray& key = hashKey, const QByteArray& iv = hashIv);
  static QString decrypt(const QString& encryptedText, const QByteArray& key = hashKey, const QByteArray& iv = hashIv);
  inline static const QHash<SW::User, QString> currentUser_{
    {SW::User::U_public, "PUBLIC"},
    {SW::User::U_user, "USER"}
  };

  inline static const QString defaultUser{QStringLiteral("public")};
  inline static QString current_user_{defaultUser};
  inline static SW::SessionStatus sessionStatus_{SW::SessionStatus::Session_closed};


private:

  inline static const QString dbDir_name{"/xxxdatabase"};
  inline static const QPalette standardPalette_{QGuiApplication::palette()};

  //variables y constantes de encriptacion

  inline static const QString key {"AbCdEfGhIjKlMnOpQrStUvWxYz@!#$%&/()=?¡1234567890"};
  inline static const QString iv {"lincoln_carolina@m1am0r"};
  inline static const QByteArray hashKey {QCryptographicHash::hash(key.toLatin1(), QCryptographicHash::Sha256)};
  inline static const QByteArray hashIv {QCryptographicHash::hash(iv.toLatin1(), QCryptographicHash::Md5)};

};

} // namespace SW
