#include "helperdb.hpp"

#include <QSqlError>
#include <QStringView>

namespace SW {

HelperDataBase_t::HelperDataBase_t()
:db_{QSqlDatabase::database(QStringLiteral("xxxConection"))},
  qry_(db_),
encryptionKey_{SW::Helper_t::deriveEncryptionKey()}
{
}

bool HelperDataBase_t::userExists(QStringView user) noexcept {

  qry_.prepare(R"(SELECT fn_user_exists(?))");
  qry_.addBindValue(user.toString());  // texto plano — fn_user_exists hashea internamente

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }

  return qry_.first() ? qry_.value(0).toBool() : false;
}

bool HelperDataBase_t::userExists() noexcept {

  qry_.prepare(R"(SELECT fn_any_user_exists())");

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }

  return qry_.first() ? qry_.value(0).toBool() : false;
}

bool HelperDataBase_t::categoryExists(QStringView category, uint32_t userId) noexcept {

  qry_.prepare(R"(SELECT fn_category_exists(?, ?))");
  qry_.addBindValue(category.toString());
  qry_.addBindValue(userId);

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }

  return qry_.first() ? qry_.value(0).toBool() : false;
}


bool HelperDataBase_t::urlExists(QStringView url, uint32_t categoryid) noexcept {

  qry_.prepare(R"(SELECT fn_url_exists(?, ?))");
  qry_.addBindValue(url.toString().simplified());
  qry_.addBindValue(categoryid);

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }

  return qry_.first() ? qry_.value(0).toBool() : false;
}


bool HelperDataBase_t::createUser(QStringView user, QStringView password, QStringView user_prof,
								  QStringView rescue_type, QStringView val1, QStringView val2) noexcept{

  qry_.prepare(R"(SELECT fn_create_user(?,?,?,?,?,?,?))");
  qry_.addBindValue(user.toString());
  qry_.addBindValue(password.toString());
  qry_.addBindValue(user_prof.toString());
  qry_.addBindValue(rescue_type.toString());
  qry_.addBindValue(val1.toString());
  qry_.addBindValue(val2.toString());
  qry_.addBindValue(encryptionKey_);

  bool result = qry_.exec();
  if(!result){
	errorMessage_ = qry_.lastError().text();
  } else {
	errorMessage_.clear();
  }
  return result;
}

bool HelperDataBase_t::logIn(QStringView user, QStringView password) noexcept{

  qry_.prepare(R"(SELECT fn_login(?, ?))");
  qry_.addBindValue(user.toString());
  qry_.addBindValue(password.toString());

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }

  if(!qry_.first()) return false;

  // PostgreSQL BOOLEAN → Qt lo devuelve como bool directamente
  return qry_.value(0).toBool();
}


bool HelperDataBase_t::saveCategoryData(QStringView catName, QStringView desc, uint32_t userid) noexcept {

  qry_.prepare(R"(SELECT fn_save_category(?, ?, ?))");
  qry_.addBindValue(catName.toString());
  qry_.addBindValue(desc.toString());
  qry_.addBindValue(userid);

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }

  errorMessage_.clear();
  return true;
}


bool HelperDataBase_t::updateCategory(QStringView url, QStringView desc, uint32_t category_id, uint32_t user_id) noexcept{

  qry_.prepare(R"(SELECT fn_update_category(?, ?, ?, ?))");
  qry_.addBindValue(url.toString());
  qry_.addBindValue(desc.toString());
  qry_.addBindValue(category_id);
  qry_.addBindValue(user_id);

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }
  return qry_.first() ? qry_.value(0).toBool() : false;
}


bool HelperDataBase_t::saveData_url(QStringView url, QStringView desc, uint32_t id) noexcept {

  qry_.prepare(R"(SELECT fn_save_url(?, ?, ?, ?))");
  qry_.addBindValue(url.toString().simplified());
  qry_.addBindValue(desc.toString());
  qry_.addBindValue(id);
  qry_.addBindValue(encryptionKey_);

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }

  errorMessage_.clear();
  return true;
}


bool HelperDataBase_t::updateData_url(QStringView url, QStringView desc, uint32_t id, uint32_t categoryId) noexcept{

  qry_.prepare(R"(SELECT fn_update_url(?, ?, ?, ?, ?))");
  qry_.addBindValue(url.toString());
  qry_.addBindValue(desc.toString());
  qry_.addBindValue(id);
  qry_.addBindValue(categoryId);
  qry_.addBindValue(encryptionKey_);

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }

  if(!qry_.first()){
	errorMessage_ = "fn_update_url no retornó valor";
	return false;
  }

  bool result = qry_.value(0).toBool();
  if(!result){
	errorMessage_ = "No se actualizó ninguna URL (ID o categoría incorrectos)";
  } else {
	errorMessage_.clear();
  }
  return result;
}


bool HelperDataBase_t::deleteUrls(DeleteUrlMode op, uint32_t categoryId, uint32_t urlId) noexcept{

  if(op == DeleteUrlMode::ByCategory){
	qry_.prepare(R"(SELECT fn_delete_urls_by_category(?))");
	qry_.addBindValue(categoryId);
  }else{
	qry_.prepare(R"(SELECT fn_delete_url_by_id(?))");
	qry_.addBindValue(urlId);
  }

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }
  return qry_.first() ? qry_.value(0).toBool() : false;
}


QHash<uint32_t, QString> HelperDataBase_t::loadList_Category(uint32_t user_id) noexcept {

  QHash<uint32_t, QString> categoryList{};

  qry_.prepare(R"(SELECT * FROM fn_load_category_list(?))");
  qry_.addBindValue(user_id);

  if(qry_.exec()){
	while(qry_.next()){
	  categoryList.insert(qry_.value(0).toUInt(), qry_.value(1).toString());
	}
  } else {
	errorMessage_ = qry_.lastError().text();
  }
  return categoryList;
}


bool HelperDataBase_t::deleteCategory(uint32_t categoryId) noexcept {

  qry_.prepare(R"(SELECT fn_delete_category(?))");
  qry_.addBindValue(categoryId);

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }
  return qry_.first() ? qry_.value(0).toBool() : false;
}


bool HelperDataBase_t::validateAnswer(QStringView respuesta, uint32_t userId) noexcept{

  qry_.prepare(R"(SELECT fn_validate_answer(?, ?))");
  qry_.addBindValue(userId);
  qry_.addBindValue(respuesta.toString().simplified());

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }
  return qry_.first() ? qry_.value(0).toBool() : false;
}

bool HelperDataBase_t::resetPassword(QStringView password, uint32_t userId) noexcept{

  qry_.prepare(R"(SELECT fn_reset_password(?, ?))");
  qry_.addBindValue(userId);
  qry_.addBindValue(password.toString());

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }

  return qry_.first() ? qry_.value(0).toBool() : false;
}


bool HelperDataBase_t::moveUrlToOtherCategory(uint32_t categoryId, uint32_t urlId) noexcept{

  qry_.prepare(R"(SELECT fn_move_url_to_category(?, ?))");
  qry_.addBindValue(urlId);
  qry_.addBindValue(categoryId);

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return false;
  }
  return qry_.first() ? qry_.value(0).toBool() : false;
}


bool HelperDataBase_t::isDataBase_empty() noexcept {

	auto tables = db_.tables();
	uint32_t count{0};
	foreach (const auto& table, tables) {
		if(table == "users"){
			continue;
		}
		qry_.prepare(QString("SELECT COUNT(*) FROM %1").arg(table));
		if(qry_.exec()){
			qry_.next();
			if(qry_.value(0).toInt() == 0) ++count;
		}
	}
	return (count == tables.size()-1);
}


int HelperDataBase_t::getUser_id(const QString& user, SW::User user_profile) noexcept {

  qry_.prepare(R"(SELECT fn_get_user_id(?, ?))");
  qry_.addBindValue(user);
  qry_.addBindValue(SW::Helper_t::currentUser_.value(user_profile).simplified());

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return 0;
  }

  return qry_.first() ? qry_.value(0).toInt() : 0;
}


QStringList HelperDataBase_t::dataCategory(uint32_t category_id) noexcept {
  QStringList dataCategory{};

  qry_.prepare(R"(SELECT * FROM fn_get_category_data(?))");
  qry_.addBindValue(category_id);

  if(qry_.exec() && qry_.next()){
	dataCategory.append(qry_.value(0).toString());
	dataCategory.append(qry_.value(1).toString());
  } else {
	errorMessage_ = qry_.lastError().text();
  }
  return dataCategory;
}


QString HelperDataBase_t::validateRescueType(uint32_t userId) noexcept{
  qry_.prepare(R"(SELECT * FROM fn_validate_rescue_type(?))");
  qry_.addBindValue(userId);

  if(qry_.exec() && qry_.next()){
	return qry_.value(0).toString();
  }
  errorMessage_ = qry_.lastError().text();
  return QString();
}

QString HelperDataBase_t::getQuestion(uint32_t userId) noexcept {

  qry_.prepare(R"(SELECT fn_get_question(?, ?))");
  qry_.addBindValue(userId);
  qry_.addBindValue(encryptionKey_);

  if(!qry_.exec()){
	errorMessage_ = qry_.lastError().text();
	return {};
  }

  return qry_.first() ? qry_.value(0).toString() : QString{};
}

}//namespace SW