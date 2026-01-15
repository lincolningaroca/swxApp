#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>

#include "util/helper.hpp"


class QStringView;
namespace SW {



struct HelperDataBase_t{

  explicit HelperDataBase_t();

  HelperDataBase_t(const HelperDataBase_t&) = delete;
  HelperDataBase_t(HelperDataBase_t&&) = delete;
  HelperDataBase_t& operator=(const HelperDataBase_t&) = delete;
  HelperDataBase_t& operator=(HelperDataBase_t&&) = delete;

  bool userExists(QStringView user) noexcept;
  bool userExists() noexcept;
  bool categoryExists(QStringView category, uint32_t userId) noexcept;
  bool urlExists(QStringView url, uint32_t categoryid) noexcept;
  bool createUser(QStringView, QStringView, QStringView user_prof,
                  QStringView rescue_type, QStringView val1, QStringView val2) noexcept;
  bool logIn(QStringView user, QStringView password) noexcept;
  ///////////******************///////////////////////////////////////////////////////////////////////////////////////
  //funciones del formulario principal
  bool saveCategoryData(QStringView catName, QStringView desc, uint32_t userid) noexcept;
  bool updateCategory( QStringView url,  QStringView desc, uint32_t category_id, uint32_t user_id) noexcept;
  bool saveData_url(QStringView url, QStringView desc, std::uint32_t id) noexcept;
  bool deleteUrls(std::uint8_t op, uint32_t categoryId=0, uint32_t urlId=0) noexcept;
  bool deleteCategory(uint32_t categoryId) noexcept;
  bool validateAnswer(QStringView respuesta, uint32_t userId) noexcept;
  bool resetPassword(QStringView password, uint32_t userId) noexcept;
  bool moveUrlToOtherCategory(uint32_t categoryId, uint32_t urlId) noexcept;

  //verificar si la base d edatos existe
  bool dataBase_exists(QStringView db_name) const;

  bool isDataBase_empty() noexcept;



  QHash<uint32_t, QString> loadList_Category(uint32_t user_id) noexcept;

  // uint32_t getUser_id(const QString &user, const QString &user_profile = QStringLiteral("PUBLIC")) noexcept;
  int getUser_id(const QString &user, SW::User user_profile) noexcept;
  QStringList dataCategory(uint32_t category_id) noexcept;
  std::tuple<bool, QString> verifyDeleteCategory(uint32_t categoryId) noexcept;
  QString validateRescueType(uint32_t userId) noexcept;
  QString getQuestion(uint32_t userId) noexcept;

private:
  const QSqlDatabase db_{};
  QSqlQuery qry_{};



};

} // namespace SW
