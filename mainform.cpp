#include "mainform.hpp"
#include "ui_mainform.h"

#include "acercadedialog.hpp"
#include "categorydialog.hpp"
#include "changepwddialog.hpp"
#include "configdialog.hpp"
#include "dlgnewcategory.hpp"
#include "logindialog.hpp"
#include "midlewidget.hpp"
#include "publicurldialog.hpp"
#include "resetpassworddialog.hpp"
#include "swwidgets/switemdelegate.hpp"
#include "swwidgets/swtablemodel.hpp"
#include "util/excelexporter.hpp"

#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QProcess>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStyleHints>
#include <QStyleFactory>
#include <QTimer>
#include <QTextEdit>


MainForm::MainForm(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::MainForm),
  db_{QSqlDatabase::database(QStringLiteral("xxxConection"))}
{

  ui->setupUi(this);

  defaultStyleName_ = qApp->style()->objectName();


  QObject::connect(ui->showHideDatabaseAction, &QAction::toggled, this, [this](bool checked = false){

	ui->dataBasetoolBar->setVisible(checked);
  });

  QObject::connect(ui->showHideAction, &QAction::toggled, this, [this](bool checked = false){

	ui->logIntoolBar->setVisible(checked);
  });
  QObject::connect(ui->actionPreferencias, &QAction::toggled, this, [this](bool checked = false){

	ui->preferenceToolBar->setVisible(checked);
  });
  setUpShowMenuAction();

  QObject::connect(ui->actionPreference, &QAction::triggered, this, &MainForm::on_showSettingsDialog);


  userId_ = helperdb_.getUser_id(SW::Helper_t::defaultUser, SW::User::U_public);


  initFrm();
  setUpStatusBar();

  loadListCategory(userId_);

  setUpTable(currentCategoryId());

  QObject::connect(ui->tvUrl, &QTableView::doubleClicked, this, &MainForm::on_showDescriptionDialog);
  canCreateBackUp();
  canStartSession();

  has_data();

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //context menu implementation

  setUpCboCategoryContextMenu();
  setUptvUrlContextMenu();
  verifyContextMenu();

  canRestoreDataBase();


  ui->tvUrl->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->tvUrl, &QTableView::customContextMenuRequested, this, &MainForm::on_showTableContextMenu);
  /**
   * @brief QObject::connect
   * connect to btnResetPassword
   */
  QObject::connect(ui->btnResetPassword, &QAction::triggered, this, &MainForm::on_showResetPasswordDialog);

  /**
   * @brief QObject::connect
   */
  QObject::connect(exportToExcelFile_, &QAction::triggered, this, &MainForm::on_exportToExcel);
  /**
   * @brief QObject::connect
   */
  QObject::connect(delCategory_, &QAction::triggered, this, &MainForm::on_deleteCategory);
  /**
   * @brief QObject::connect
   * btnDeleteCategory
   */
  QObject::connect(ui->btnDeleteCategory, &QPushButton::clicked, this, &MainForm::on_deleteCategory);
  /**
   * @brief QObject::connect
   */
  QObject::connect(ui->btnAdd,&QPushButton::clicked, this, &MainForm::on_addNewUrl);
  /**
   * @brief connect
   */
  QObject::connect(ui->btnNewCategory, &QToolButton::clicked, this, &MainForm::on_showNewCategoryDialog);
  /**
   * @brief QObject::connect
   */
  QObject::connect(ui->btnEditCategory, &QPushButton::clicked, this, &MainForm::on_editCategory);


  QObject::connect(midleWidget, &MidleWidget::urlTextChanged, this, [this](const QString& text){
	ui->btnAdd->setEnabled(!text.simplified().isEmpty());
  });

  /**
   * @brief QObject::connect
   */
  QObject::connect(ui->btnQuit, &QPushButton::clicked,this, &MainForm::on_quitUrl);

  /**
   * @brief QObject::connect
   */
  QObject::connect(quitUrl_, &QAction::triggered,this, &MainForm::on_quitUrl);

  /**
   * @brief QObject::connect
   */
  QObject::connect(ui->actionAcerca_del_autor, &QAction::triggered, this, &MainForm::on_showAboutDialog);
  /**
   * @brief connect
   */
  QObject::connect(ui->btnEdit, &QPushButton::clicked, this, &MainForm::on_btnEdit);

  /**
   * @brief QObject::connect
   */
  QObject::connect(editUrl_, &QAction::triggered, this, &MainForm::on_btnEdit);


  QObject::connect(ui->btnopen, &QPushButton::clicked, this, [this](){
	if(!validateSelectedRow()) return;

	openUrl();


  });

  QObject::connect(openUrl_, &QAction::triggered, this, [this](){
	if(!validateSelectedRow()) return;

	openUrl();
  });

  readSettings();

  QObject::connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged, this, [this](){
	// Solo reaccionamos si el usuario eligió "Sistema" (Unknown)
	// Si eligió Dark o Light fijo, ignoramos el cambio del SO
	if(currentScheme_ == Qt::ColorScheme::Unknown){
	  applyPreferredTheme(Qt::ColorScheme::Unknown);

	}
  });

  /**
   * @brief QObject::connect
   */
  QObject::connect(ui->cboCategory, &QComboBox::currentIndexChanged, this, &MainForm::on_categorySelectedChanged);

  setCboCategoryToolTip();
  hastvUrlData();

  /**
   * @brief QObject::connect
   */
  QObject::connect(ui->btnLogIn, &QAction::triggered, this, &MainForm::on_loadLoginForm);

  /**
   * @brief QObject::connect
   */
  QObject::connect(ui->btnLogOut, &QAction::triggered, this, &MainForm::on_callLogout);

  /**
   * @brief QObject::connect
   */
  QObject::connect(ui->btnBackUp, &QAction::triggered, this, &MainForm::on_makeBackup);

  /**
   * @brief QObject::connect
   */
  QObject::connect(ui->btnRestore, &QAction::triggered, this, &MainForm::on_restoreDatabase);


  QObject::connect(ui->btnCancel, &QAbstractButton::clicked, this, &MainForm::on_cancelAction);
  QObject::connect(showDescDetail_, &QAction::triggered, this, &MainForm::on_showAllDescription);
  QObject::connect(showPublicUrl_, &QAction::triggered, this, &MainForm::on_showPublicUrlDialog);
  QObject::connect(moveUrl_, &QAction::triggered, this, &MainForm::on_moveUrl);

  QObject::connect(ui->firstTimeLogInBtn, &QAction::triggered, this, &MainForm::on_firstTimeLoginDialog);

  QObject::connect(ui->btnSettings, &QAction::triggered, this, &MainForm::on_showSettingsDialog);


  QObject::connect(ui->actionActualizar_password, &QAction::triggered, this, &MainForm::on_showChangePasswordDialog);
  QObject::connect(ui->actionVer_url_s_publicas, &QAction::triggered, this, &MainForm::on_showPublicUrlDialog);

  ui->showGridAction->setCheckable(true);
  connect(ui->showGridAction, &QAction::toggled, this, [this](bool checked){
	ui->tvUrl->setShowGrid(checked);
	ui->tvUrl->viewport()->update();

  });

}

MainForm::~MainForm()
{
  delete ui;
}

uint32_t MainForm::currentCategoryId() const noexcept{

  return ui->cboCategory->currentData().isValid() ? ui->cboCategory->currentData().toUInt() : 1;

}

void MainForm::has_data() noexcept{

  if(categoryList_.isEmpty()){
	ui->btnEditCategory->setDisabled(true);
	ui->btnDeleteCategory->setDisabled(true);

	midleWidget->setInputsEnabled(false);

  }else{
	ui->btnEditCategory->setEnabled(true);
	ui->btnDeleteCategory->setEnabled(true);

	midleWidget->setInputsEnabled(true);
  }

}

void MainForm::hastvUrlData() noexcept{

  if(ui->tvUrl->model()->rowCount() == 0){
	openUrl_->setDisabled(true);
	ui->btnopen->setDisabled(true);
	ui->btnEdit->setDisabled(true);
	ui->btnQuit->setDisabled(true);
	editUrl_->setDisabled(true);
	quitUrl_->setDisabled(true);
	moveUrl_->setVisible(false);
	showDescDetail_->setVisible(false);
	exportToExcelFile_->setVisible(false);
  }else{
	openUrl_->setEnabled(true);
	ui->btnopen->setEnabled(true);
	ui->btnEdit->setEnabled(true);
	ui->btnQuit->setEnabled(true);
	editUrl_->setEnabled(true);
	quitUrl_->setEnabled(true);
	moveUrl_->setVisible(true);
	showDescDetail_->setVisible(true);
	exportToExcelFile_->setVisible(true);
  }

}

void MainForm::on_showNewCategoryDialog(){

  dlgNewCategory newCategory(SW::OpenMode::New, QStringList(), this);

  if(newCategory.exec() == QDialog::Rejected)
	return;

  if(!helperdb_.saveCategoryData(newCategory.category(), newCategory.description(), userId_)){
	QMessageBox::critical(this, SW::Helper_t::appName(), QStringLiteral("Error al guardar los datos!\n"));
	return;
  }

  loadListCategory(userId_);
  setUpTable(currentCategoryId());
  has_data();

  hastvUrlData();
  checkStatusContextMenu();

}

void MainForm::checkStatusContextMenu(){

  const bool sessionActive = (SW::Helper_t::sessionStatus_ == SW::SessionStatus::Session_start);
  showPublicUrl_->setVisible(sessionActive);

}

void MainForm::verifyUserState(){

  const auto sessionStatus = SW::Helper_t::sessionStatus_;
  const auto u_public = SW::Helper_t::currentUser_.value(SW::User::U_public);
  const auto userName = (sessionStatus == SW::SessionStatus::Session_start)
						  ? SW::Helper_t::current_user_ : u_public;

  lblState_->setText(QString("<strong style=\"color:%1;\">User: %2</strong>").arg(getEnfasisColor().name(), userName));

}

void MainForm::loadListCategory(uint32_t user_id) noexcept{

  QSignalBlocker blocker(ui->cboCategory);

  ui->cboCategory->clear();
  categoryList_ = helperdb_.loadList_Category(user_id);

  // Recorremos el Hash e insertamos el nombre en el ComboBox guardando su respectivo ID en Qt::UserRole (oculto)
  auto it = categoryList_.constBegin();
  while (it != categoryList_.constEnd()) {
	ui->cboCategory->addItem(it.value(), it.key());
	++it;
  }

}

void MainForm::applyPreferredTheme(Qt::ColorScheme scheme){

  // Delega el esquema al sistema via Helper
  QSignalBlocker blocker(QGuiApplication::styleHints());
  SW::Helper_t::set_Theme(scheme);
  qApp->setPalette(qApp->palette());
  applyIcons(scheme);

  QPalette tablePalette = ui->tvUrl->palette();
  if (scheme == Qt::ColorScheme::Dark || scheme == Qt::ColorScheme::Unknown) {
	tablePalette.setColor(QPalette::AlternateBase, QColor(35, 35, 35));
  } else {
	tablePalette.setColor(QPalette::AlternateBase, QColor(245, 245, 245));
  }
  ui->tvUrl->setPalette(tablePalette);
  this->update();

}

void MainForm::on_loadLoginForm(){

  LogInDialog logDialog(this);
  if(logDialog.exec() == QDialog::Accepted){

	SW::Helper_t::current_user_ = logDialog.userName();

	const auto user = SW::Helper_t::hashGenerator(logDialog.userName().toLatin1());
	userId_ = helperdb_.getUser_id(user, SW::User::U_user);

	loadListCategory(userId_);

	ui->btnLogOut->setEnabled(true);
	ui->btnLogIn->setDisabled(true);
	ui->btnResetPassword->setVisible(false);

	const auto userDes = QString(" - Sesión inicada como: '%1'").arg(SW::Helper_t::current_user_);
	setWindowTitle(QApplication::applicationName().append(userDes));


	lblIcon_->setPixmap(QPixmap(":/img/user-log.png").scaled(16,16, Qt::KeepAspectRatio, Qt::SmoothTransformation));

	SW::Helper_t::sessionStatus_ = SW::SessionStatus::Session_start;

	setUpTable(currentCategoryId());
	has_data();
	checkStatusContextMenu();
	canRestoreDataBase();
	verifyUserState();
	ui->actionActualizar_password->setVisible(true);
	ui->toolBar->setVisible(true);
	ui->actionVer_url_s_publicas->setVisible(true);

  }

}

void MainForm::on_showResetPasswordDialog(){

  ResetPasswordDialog resetDialog(this);
  resetDialog.setWindowTitle(SW::Helper_t::appName()+" - Restablecer clave o password");
  resetDialog.exec();

}

void MainForm::on_exportToExcel(){

  const auto filePath = QFileDialog::getSaveFileName(this, "Guardar archivo excel", SW::Helper_t::getLastOpenedDirectory(), "Hojas de calculo (*.xlsx)" );
  if(filePath.isEmpty())
	return;

  if(!SW::ExcelExporter::exportTableView(ui->tvUrl, filePath)){

	QMessageBox::warning(this, SW::Helper_t::appName(), tr("Error al exportar el archivo.\n").arg(SW::ExcelExporter::lastError()));
	return;
  }

  const QFileInfo fileInfo(filePath);

  SW::Helper_t::setLastOpenedDirectory(fileInfo.absolutePath());
  QMessageBox::information(this, SW::Helper_t::appName(), tr("El archivo fue guardado en:\n%1").arg(filePath));

}

void MainForm::on_deleteCategory(){

  QMessageBox msgBox(this);
  msgBox.setWindowTitle(SW::Helper_t::appName()+" - Advertencia");
  msgBox.setText(QStringLiteral("<p style='color:#FB4934;'>"
								"<cite><strong>Esta a punto de eliminar ésta categoría y todo su contenido.<br>"
								"Recuerde que al aceptar, eliminará de forma permanente estos datos.<br>"
								"Desea continuar y eliminar los datos?</strong></cite></p>"));

  msgBox.setIcon(QMessageBox::Warning);

  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.button(QMessageBox::Yes)->setText("Borrar categoría");
  msgBox.button(QMessageBox::No)->setText("Cancelar");

  if(msgBox.exec() == QMessageBox::No)
	return;
  if(deleteAll()){
	QMessageBox::information(this, SW::Helper_t::appName(),QStringLiteral("Datos eliminados."));

	loadListCategory(userId_);
	setUpTable(currentCategoryId());
	has_data();
	checkStatusContextMenu();


  }

}

void MainForm::on_addNewUrl(){

  if(ui->btnAdd->text().compare("Agregar") == 0){
	if(!SW::Helper_t::urlValidate(midleWidget->url())){
	  QMessageBox::warning(this, SW::Helper_t::appName(), midleWidget->errorMessage());

	  midleWidget->selectAndFocus();
	  return;
	}

	const auto categoryId = currentCategoryId();

	if(helperdb_.urlExists(midleWidget->url(), categoryId)){

	  auto warningMsg = QString("<p>La url: <cite><strong>%1</strong></cite></p> ya esta registrada!!").arg(midleWidget->url());
	  QMessageBox::warning(this, SW::Helper_t::appName(), warningMsg);

	  midleWidget->selectAndFocus();
	  return;
	}

	if(helperdb_.saveData_url(midleWidget->url(), midleWidget->description(), categoryId)){

	  midleWidget->clearInputs();

	  setUpTable(currentCategoryId());
	  verifyContextMenu();

	  hastvUrlData();
	  checkStatusContextMenu();
	  canCreateBackUp();
	}
  }else{


	if(!SW::Helper_t::urlValidate(midleWidget->url())){
	  QMessageBox::warning(this, SW::Helper_t::appName(), midleWidget->errorMessage());

	  midleWidget->selectAndFocus();
	  return;
	}

	auto currentRow = ui->tvUrl->currentIndex().row();
	auto id = ui->tvUrl->model()->index(currentRow,0).data().toInt();

	const auto categoryId = currentCategoryId();

	if(!helperdb_.updateData_url(midleWidget->url(), midleWidget->description(), id, categoryId)){
	  QMessageBox::critical(this, SW::Helper_t::appName(), tr("Fallo la ejecución de la sentencia!\n%1"));
	  return;

	}

	setUpTable(currentCategoryId());

	ui->btnAdd->setText(QStringLiteral("Agregar"));
	editAction(false);

	midleWidget->clearInputs();
  }

}

void MainForm::on_editCategory(){

  const auto id = currentCategoryId();

  const QStringList dataLocal = helperdb_.dataCategory(id);
  dlgNewCategory editCategory(SW::OpenMode::Edit, dataLocal, this);
  if(editCategory.exec() == QDialog::Rejected){
	return;
  }
  if(helperdb_.updateCategory(editCategory.category(), editCategory.description(), id, userId_)){
	QMessageBox::information(this, SW::Helper_t::appName(), QStringLiteral("Datos actualizados!\n"));
	ui->cboCategory->clear();
	loadListCategory(userId_);

	setUpTable(currentCategoryId());
  }

}

void MainForm::on_quitUrl(){

  if(!validateSelectedRow()) return;

  auto currentRow = ui->tvUrl->currentIndex().row();

  const auto url = ui->tvUrl->model()->index(currentRow, 1).data().toString();

  QMessageBox msgBox(this);
  msgBox.setText(QString("<span>Confirma que desea eliminar esta dirección:<br>"
						 " <cite style='color:#ff0800;'><strong>%1</strong></cite></span>").arg(url));
  msgBox.setIcon(QMessageBox::Question);
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.button(QMessageBox::Yes)->setText("Eliminar");
  msgBox.button(QMessageBox::No)->setText("Cancelar");

  if(msgBox.exec() == QMessageBox::Yes){
	const auto urlId=urlList_.key(url);
	if(helperdb_.deleteUrls(SW::DeleteUrlMode::ByUrlId, 0, urlId)){
	  ui->tvUrl->model()->removeRow(ui->tvUrl->currentIndex().row());

	  setUpTable(currentCategoryId());
	}

  }

  verifyContextMenu();
  hastvUrlData();

}

void MainForm::on_btnEdit(){

  if( !validateSelectedRow() ) return;

  auto currentRow = ui->tvUrl->currentIndex().row();

  midleWidget->setUrl(ui->tvUrl->model()->index(currentRow,1).data().toString());

  const auto urlId = ui->tvUrl->model()->index(currentRow, 0).data().toUInt();
  QSqlQuery query(db_);
  query.prepare("SELECT desc FROM urls WHERE url_id = ?");
  query.addBindValue(urlId);
  if(query.exec() && query.next()){

	midleWidget->setDescription(SW::Helper_t::decrypt(query.value(0).toString()));
  }


  editAction(true);

  midleWidget->selectAndFocus();
  ui->btnAdd->setText(QStringLiteral("Actualizar"));

}


void MainForm::on_categorySelectedChanged(int index){

  Q_UNUSED(index);

  setUpTable(currentCategoryId());
  verifyContextMenu();

  setCboCategoryToolTip();
  hastvUrlData();
  checkStatusContextMenu();

}

void MainForm::on_callLogout(){

  userId_ = helperdb_.getUser_id(SW::Helper_t::defaultUser, SW::User::U_public);

  ui->btnLogOut->setDisabled(true);
  ui->btnLogIn->setEnabled(true);
  ui->btnResetPassword->setVisible(true);
  setWindowTitle(QApplication::applicationName());

  loadListCategory(userId_);
  setUpTable(currentCategoryId());

  lblIcon_->setPixmap(QPixmap(":/img/user-public.png").scaled(16,16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  SW::Helper_t::sessionStatus_ = SW::SessionStatus::Session_closed;
  has_data();
  checkStatusContextMenu();
  SW::Helper_t::current_user_ = SW::Helper_t::defaultUser;
  canRestoreDataBase();

  verifyUserState();

  ui->actionActualizar_password->setVisible(false);
  ui->toolBar->setVisible(false);
  ui->actionVer_url_s_publicas->setVisible(false);



}

void MainForm::on_makeBackup(){

  QProcess process(this);
  const auto path_app {SW::Helper_t::app_pathLocation()+"/tools/sqlite-tools-win-x64-3450100/sqlite3.exe"};
  // qInfo() << path_app << '\n';

  const auto databasePath = SW::Helper_t::AppLocalDataLocation()+"/xdatabase.db";
  const auto filePath = QFileDialog::getSaveFileName(this, QStringLiteral("Crear una copia de seguridad"), SW::Helper_t::getLastOpenedDirectory(),
													 QStringLiteral("Archivos de copia de seguridad (*.bak)"));


  if(filePath.isEmpty())
	return;

  if(filePath.contains(' ')){
	QMessageBox::warning(this, SW::Helper_t::appName(), QStringLiteral("El nombre del archivo no puede contener espacios."));
	return;
  }

  const QFileInfo fileInfo(filePath);


  const auto absolutePath{fileInfo.absolutePath()};
  const auto baseName{fileInfo.baseName()};
  const auto extension{fileInfo.suffix()};

  const auto fecha{QDateTime::currentDateTime().toString("yyyy-MM-dd_hhmmss")};
  // QString path{".backup %1/%2-%3.%4"};
  const auto backupCommand = QString(".backup '%1/%2-%3.%4'").arg(absolutePath, baseName, fecha, extension);

  // Verificar si el ejecutable sqlite3 existe
  if(!QFile::exists(path_app)) {
	QMessageBox::critical(this, SW::Helper_t::appName(), QStringLiteral("No se encontró el ejecutable sqlite3"));
	return;
  }

  SW::Helper_t::setLastOpenedDirectory(absolutePath);

  QStringList argv{};

  argv << databasePath << backupCommand;
  qDebug() << "Ejecutando:" << path_app << argv;  // Para depuración

  qint64 pid = 0;
  bool started = QProcess::startDetached(path_app, argv, QDir::currentPath(), &pid);


  if(!started || pid == 0) {
	QMessageBox::critical(this, SW::Helper_t::appName(), tr("Error al crear la copia de seguridad.\n").arg(process.errorString()));
	return;
  }

  QMessageBox::information(this, SW::Helper_t::appName(), tr("La copia de seguridad fue creada en:\n%1").arg(filePath));

}

void MainForm::on_restoreDatabase(){

  const auto dbasePath{SW::Helper_t::AppLocalDataLocation()+"/xdatabase.db"};

  if(!helperdb_.isDataBase_empty()){

	QMessageBox msg{this};
	msg.setWindowTitle(SW::Helper_t::appName());
	msg.setIcon(QMessageBox::Warning);
	msg.setText(QStringLiteral("<span>"
							   "En éste momento hay una instancia de la base de datos en uso.<br/>"
							   "<em>Tenga en cuenta que al restaurar la base de datos con una cópia de seguridad,<br/>"
							   "se perderan todos los datos que tengan en éste momento, y seran reemplazados por los datos de la cópia.</em><br/><br/>"
							   "<cite><strong>Consejo:</strong></cite>"
							   "<ul><li>Tal vez antes de restaurar, una cópia de seguridad, quiera crear un backup, de la base de datos actual, para no perder los datos.</li></ul><br/>"
							   "</span>"));

	msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msg.button(QMessageBox::Yes)->setText("Restaurar la base de datos");
	msg.button(QMessageBox::No)->setText("Cancelar");
	if(msg.exec() == QMessageBox::No)
	  return;
  }

  const auto pathBackup{QFileDialog::getOpenFileName(this, "Abrir archivo de respaldo", SW::Helper_t::getLastOpenedDirectory(),
													 QStringLiteral("Archivo backup (*.bak)"))};
  if(pathBackup.isEmpty())
	return;

  auto db{QSqlDatabase::database("xxxConection")};

  if(db.isOpen())
	db.close();


  QStringList args{};
  QString cmd {".restore %1"};

  args << dbasePath << cmd.arg(pathBackup);

  const auto app{SW::Helper_t::app_pathLocation()+"/tools/sqlite-tools-win-x64-3450100/sqlite3.exe"};

  QProcess process{this};

  const QFileInfo fileInfo{pathBackup};
  SW::Helper_t::setLastOpenedDirectory(fileInfo.absolutePath());

  if(!process.startDetached(app, args)){
	QMessageBox::critical(this, SW::Helper_t::appName(), tr("Error en la ejecución.\n%1").arg(process.errorString()));
	return;

  }
  QMessageBox::information(this, SW::Helper_t::appName(), QStringLiteral("La base de datos, fue restaurada"));
  db.open();

  // ui->cboCategory->clear();
  loadListCategory(userId_);
  setUpTable(currentCategoryId());
  has_data();
  canCreateBackUp();
  canStartSession();



}

void MainForm::on_cancelAction(){

  midleWidget->clearInputs();
  ui->btnCancel->setDisabled(true);

  editAction(false);
  ui->btnAdd->setText(QStringLiteral("Agregar"));

}

void MainForm::on_showAllDescription(){

  auto row = ui->tvUrl->currentIndex().row();
  const auto desc = ui->tvUrl->model()->index(row,2).data().toString();
  const auto url = ui->tvUrl->model()->index(row,1).data().toString();

  QMessageBox msgDescription(this);

  msgDescription.setWindowTitle(qApp->applicationName()+" - Descripción completa de la URL");
  msgDescription.setIcon(QMessageBox::Information);
  msgDescription.setText(desc);
  msgDescription.setDetailedText(url);
  msgDescription.addButton(QStringLiteral("Cerrar descripción"), QMessageBox::AcceptRole);

  msgDescription.exec();

}

void MainForm::on_showPublicUrlDialog(){

  PublicUrlDialog publicDialog(currentScheme_, this);
  publicDialog.setWindowTitle("Direcciones url públicas");

  publicDialog.setShowGrid(ui->tvUrl->showGrid());

  publicDialog.exec();

}

void MainForm::on_moveUrl(){

  const auto currentRow_ = ui->tvUrl->currentIndex().row();
  const auto url_ = xxxModel_->index(currentRow_, 1).data().toString();
  const auto currentCategoryId_ =currentCategoryId();

  const auto urlid = xxxModel_->index(currentRow_, 0).data().toUInt();
  auto data_ = categoryList_;
  data_.remove(currentCategoryId_);

  CategoryDialog cDialog(data_, this);
  cDialog.setWindowTitle(QStringLiteral("Mover url a otra categoría"));

  if(cDialog.exec() == QDialog::Accepted){

	auto categoryid = cDialog.getCategoryId();
	if(helperdb_.urlExists(url_, categoryid)){

	  auto warningMsg = QString("<p>"
								"La url: <cite>"
								"<strong>%1</strong>"
								"</cite>"
								"</p> ya esta registrada, en la categoría a la que desea mover!!").arg(url_);

	  QMessageBox::warning(this, SW::Helper_t::appName(), warningMsg);
	  return;

	}
	// qInfo() <<categoryid;

	if(!helperdb_.moveUrlToOtherCategory(categoryid, urlid)){
	  QMessageBox::critical(this, SW::Helper_t::appName(), QStringLiteral("Error al intentar actualizar.\n"));
	  return;
	}

	setUpTable(currentCategoryId());
	verifyContextMenu();
	hastvUrlData();
  }

}

void MainForm::on_firstTimeLoginDialog(){

  LogInDialog login(this, LogInDialog::FIRST_TIME);
  login.setToggledToButton(true);
  if(login.exec() == QDialog::Accepted){
	canStartSession();
	ui->firstTimeLogInBtn->setVisible(false);
  }

}

void MainForm::on_showSettingsDialog(){

  bool isFusionActive = (qApp->style()->objectName().compare(QStringLiteral("fusion"), Qt::CaseInsensitive) == 0);

  ConfigDialog settings(currentScheme_, isFusionActive, this);
  settings.setWindowTitle(SW::Helper_t::appName()+" - Configuración");

  // Apply: aplica y guarda sin cerrar el diálogo
  QObject::connect(&settings, &ConfigDialog::themeChanged, this, [this](Qt::ColorScheme scheme){
	currentScheme_ = scheme;
	applyPreferredTheme(currentScheme_);

  });

  QObject::connect(&settings, &ConfigDialog::styleChanged, this, &MainForm::on_styleChanged );

  // Aceptar: aplica solo si no se había aplicado ya con Apply
  if(settings.exec() == QDialog::Accepted){
	if(currentScheme_ != settings.selectedScheme()){
	  currentScheme_ = settings.selectedScheme();
	  applyPreferredTheme(currentScheme_);

	}
	writeSettings();
  }

}

void MainForm::on_showDescriptionDialog(const QModelIndex &index){

  const auto urlId = ui->tvUrl->model()->index(index.row(), 0).data().toUInt();

  // Traer directamente de la base de datos
  QSqlQuery query(db_);
  query.prepare("SELECT desc FROM urls WHERE url_id = ?");
  query.addBindValue(urlId);

  QString desc{};
  if(query.exec() && query.next()){
	desc = SW::Helper_t::decrypt(query.value(0).toString());
  }

  QDialog dlg(this);
  dlg.setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
  dlg.setWindowTitle(SW::Helper_t::appName()+" - Descripción");
  dlg.resize(500, 300);

  auto *layout = new QVBoxLayout(&dlg);

  auto *textView = new QTextEdit(&dlg);
  textView->setReadOnly(true);
  textView->setHtml(desc);

  auto *btnLayout = new QHBoxLayout();
  auto *btnClose = new QPushButton("Cerrar", &dlg);

  btnLayout->addStretch();
  btnLayout->addWidget(btnClose);
  QObject::connect(btnClose, &QPushButton::clicked, &dlg, &QDialog::accept);

  layout->addWidget(textView);
  layout->addLayout(btnLayout);

  dlg.exec();

  xxxModel_->select();
}

void MainForm::on_showChangePasswordDialog(){

  ChangePwdDialog chnDialog(SW::Helper_t::current_user_, this);
  chnDialog.exec();

}



void MainForm::setUpShowMenuAction(){

  ui->showHideAction->setCheckable(true);
  ui->showHideDatabaseAction->setCheckable(true);
  ui->actionPreferencias->setCheckable(true);

  QObject::connect(ui->logIntoolBar, &QToolBar::visibilityChanged, ui->showHideAction, &QAction::setChecked);
  QObject::connect(ui->dataBasetoolBar, &QToolBar::visibilityChanged, ui->showHideDatabaseAction, &QAction::setChecked);
  QObject::connect(ui->preferenceToolBar, &QToolBar::visibilityChanged, ui->actionPreferencias, &QAction::setChecked);

  auto valueExists = SW::Helper_t::nativeRegistryKeyExists("state");

  if(!valueExists){
	ui->showHideAction->setChecked(true);
	ui->showHideDatabaseAction->setChecked(true);
	ui->actionPreferencias->setChecked(true);
  }

}

void MainForm::setUpStatusBar(){

  lblIcon_ = new QLabel(this);
  ui->statusbar->addWidget(lblIcon_);
  lblIcon_->setPixmap(QPixmap(":/img/user-public.png").scaled(16,16, Qt::KeepAspectRatio, Qt::SmoothTransformation));

  lblState_ = new QLabel(this);
  ui->statusbar->addWidget(lblState_);
  auto user = SW::Helper_t::currentUser_.value(SW::User::U_public);

  lblState_->setText(QString("<p style=\"color:%1\">%2</p>").arg(getEnfasisColor().name(), user));


  lblInfo_ = new QLabel(this);

  updateLblInfo();
  lblInfo_->setTextFormat(Qt::RichText);
  lblInfo_->setTextInteractionFlags(Qt::TextBrowserInteraction);
  lblInfo_->setCursor(Qt::PointingHandCursor);
  ui->statusbar->addPermanentWidget(lblInfo_);

  /**
   * @brief QObject::connect
   * connect to lblInfo, an show abaout dialog
   */
  QObject::connect(lblInfo_, &QLabel::linkActivated, this, &MainForm::on_showAboutDialog);

}

void MainForm::updateLblInfo() noexcept{
  const auto linkColor = qApp->palette().color(QPalette::Active, QPalette::Link);
  lblInfo_->setText(QString("<a href='about dialog' style='color:%1;'>"
							"<span>SWSystem's - Lincoln Ingaroca</span>"
							"</a>").arg(linkColor.name()));
}

void MainForm::applyIcons(Qt::ColorScheme scheme) noexcept{

  const auto iconColor = SW::Helper_t::currentIconColor(scheme);

  // --- Toolbar: login/logout ---
  ui->btnLogIn->setIcon(SW::Helper_t::svgIcon(":/img/log-in.svg", iconColor));
  ui->btnLogOut->setIcon(SW::Helper_t::svgIcon(":/img/log-out.svg", iconColor));
  ui->btnResetPassword->setIcon(SW::Helper_t::svgIcon(":/img/restore-password.svg", iconColor));
  ui->firstTimeLogInBtn->setIcon(SW::Helper_t::svgIcon(":/img/user-cog.svg", iconColor));
  ui->actionActualizar_password->setIcon(SW::Helper_t::svgIcon(":/img/key-round.svg", iconColor));
  ui->actionVer_url_s_publicas->setIcon(SW::Helper_t::svgIcon(":/img/public-url.svg", iconColor));

  // --- Toolbar: base de datos ---
  ui->btnBackUp->setIcon(SW::Helper_t::svgIcon(":/img/database-backup.svg", iconColor));
  ui->btnRestore->setIcon(SW::Helper_t::svgIcon(":/img/database-zap.svg", iconColor));

  // --- Toolbar: preferencias ---
  ui->btnSettings->setIcon(SW::Helper_t::svgIcon(":/img/settings.svg", iconColor));

  ui->btnNewCategory->setIcon(SW::Helper_t::svgIcon(":/img/category-new.svg", iconColor));
  ui->btnEditCategory->setIcon(SW::Helper_t::svgIcon(":/img/category-edit.svg", iconColor));
  ui->btnDeleteCategory->setIcon(SW::Helper_t::svgIcon(":/img/category-delete.svg", iconColor));

  // --- Context menu (también cambian) ---
  if (openUrl_)      openUrl_->setIcon(SW::Helper_t::svgIcon(":/img/link-open.svg", iconColor));
  if (editUrl_)      editUrl_->setIcon(SW::Helper_t::svgIcon(":/img/link-edit.svg", iconColor));
  if (quitUrl_)      quitUrl_->setIcon(SW::Helper_t::svgIcon(":/img/link-delete.svg", iconColor));
  if (showPublicUrl_) showPublicUrl_->setIcon(SW::Helper_t::svgIcon(":/img/public-url.svg", iconColor));
  // if (moveUrl_)      moveUrl_->setIcon(SW::Helper_t::svgIcon(":/img/move-right.svg", iconColor));
  if (delCategory_)  delCategory_->setIcon(SW::Helper_t::svgIcon(":/img/category-delete.svg", iconColor));

  midleWidget->applyIcons(iconColor);


}

void MainForm::initFrm() noexcept{

  midleWidget =new MidleWidget(this);
  ui->insertLayout->addWidget(midleWidget);

  midleWidget->setPlacesHolders();

  ui->btnNewCategory->setToolTip(QStringLiteral("New Category!"));
  ui->btnEditCategory->setToolTip(QStringLiteral("Edit Category Data!"));
  //btnAdd disabled
  ui->btnAdd->setDisabled(true);
  ui->btnLogIn->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
  ui->btnLogOut->setDisabled(true);
  ui->btnLogOut->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

  ui->btnCancel->setDisabled(true);

  //set shortcuts, to button box url
  ui->btnAdd->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_A));
  ui->btnEdit->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_E));
  ui->btnQuit->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Q));
  ui->btnopen->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_O));
  ui->btnCancel->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_C));

  midleWidget->clearInputs();

  ui->actionActualizar_password->setVisible(false);

  QTimer::singleShot(0, this, [this](){
	ui->toolBar->setVisible(false);
	ui->actionVer_url_s_publicas->setVisible(false);
  });

  ui->btnResetPassword->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_P));

  ui->firstTimeLogInBtn->setToolTip("<p>Crear un usuario: <br>"
									"<cite>\"Este boton se muestra solo por una vez; "
									"esto es por la razón de que, al abrir la aplicación por primera vez, no existen usuarios,"
									" aparte del usario por defecto\"</cite></p>");




}

void MainForm::setUpTable(uint32_t categoryId) noexcept{

  xxxModel_ = new SWTableModel(this, db_);
  xxxModel_->setTable("urls");
  xxxModel_->setFilter(QString("categoryid=%1").arg(categoryId));
  xxxModel_->select();

  ui->tvUrl->setModel(xxxModel_);
  setUpTableHeaders();
  ui->tvUrl->setMouseTracking(true);

  QSqlQuery query(xxxModel_->query().lastQuery(), db_);


  if(query.exec()){
	while(query.next()){
	  urlList_.insert(query.value(0).toUInt(),query.value(1).toString());
	}
  }

}

void MainForm::setUpTableHeaders() const noexcept{

  ui->tvUrl->hideColumn(0);
  ui->tvUrl->hideColumn(3);
  ui->tvUrl->model()->setHeaderData(1,Qt::Horizontal, "Dirección URL");
  ui->tvUrl->model()->setHeaderData(2,Qt::Horizontal, "Descripción");
  ui->tvUrl->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tvUrl->setItemDelegate(new SWItemDelegate(ui->tvUrl));
  ui->tvUrl->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui->tvUrl->verticalHeader()->setDefaultSectionSize(20);
  ui->tvUrl->setAlternatingRowColors(true);

}

void MainForm::canRestoreDataBase() const noexcept{
  ui->btnRestore->setVisible(static_cast<bool>(SW::Helper_t::sessionStatus_));

}

void MainForm::canCreateBackUp() const noexcept{
  ui->btnBackUp->setVisible(hasValidTableData());

}

void MainForm::canStartSession() noexcept{
  ui->btnLogIn->setEnabled(helperdb_.userExists());
  ui->btnResetPassword->setEnabled(helperdb_.userExists());
  ui->firstTimeLogInBtn->setVisible(!helperdb_.userExists());

}

void MainForm::setUpCboCategoryContextMenu() noexcept{

  const QIcon icon(QStringLiteral(":/img/118277.png"));
  ui->cboCategory->setContextMenuPolicy(Qt::ActionsContextMenu);
  delCategory_ = new QAction(icon, QStringLiteral("Forzar eliminación de categoría"),this);
  ui->cboCategory->addAction(delCategory_);

}

void MainForm::setUptvUrlContextMenu() noexcept{

  openUrl_ = new QAction(QStringLiteral("Abrir url en el navegador"), this);
  editUrl_ = new QAction(QStringLiteral("Editar url"), this);
  quitUrl_ = new QAction(QStringLiteral("Quitar url"), this);

  showDescDetail_ = new QAction(QStringLiteral("Ver descripción de URL completa"), this);

  showPublicUrl_ = new QAction(QStringLiteral("Ver url's públicas"));

  moveUrl_ = new QAction(QStringLiteral("Mover url, a otra categoría"), this);

  const auto exportToExcelFileIcon = QIcon(QStringLiteral(":/img/excelDocument.png"));
  exportToExcelFile_ = new QAction(exportToExcelFileIcon, QStringLiteral("Exportar datos a excel"), this);

  checkStatusContextMenu();

}

void MainForm::on_showTableContextMenu(const QPoint& p){

  QMenu tableMenu(this);

  auto index = ui->tvUrl->indexAt(p);

  if(index.isValid()){

	tableMenu.addAction(openUrl_);
	tableMenu.addAction(editUrl_);
	tableMenu.addAction(quitUrl_);
	tableMenu.addSeparator();
	tableMenu.addAction(showDescDetail_);
	tableMenu.addAction(showPublicUrl_);
	tableMenu.addSeparator();
	tableMenu.addAction(moveUrl_);
	tableMenu.addSeparator();
	tableMenu.addAction(exportToExcelFile_);

  }

  tableMenu.exec(ui->tvUrl->mapToGlobal(p));

}

void MainForm::on_styleChanged(bool style){

  if (style) {
	qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

  } else {
	qApp->setStyle(QStyleFactory::create(defaultStyleName_));

  }

}

void MainForm::verifyContextMenu() noexcept{

  const auto categoryId = currentCategoryId();

  auto [res, errMessage] = helperdb_.verifyDeleteCategory(categoryId);
  //      qDebug()<<count;
  (res) ? delCategory_->setDisabled(true) : delCategory_->setEnabled(true);

}

void MainForm::openUrl() noexcept{

  auto currentRow = ui->tvUrl->currentIndex().row();
  const auto url = ui->tvUrl->model()->index(currentRow, 1).data().toString();
  if(!SW::Helper_t::open_Url(QUrl(url))){
	QMessageBox::critical(this, SW::Helper_t::appName(), QStringLiteral("Fallo al intentar abrir dirección url!\n"));
	return;
  }

}

void MainForm::readSettings() noexcept{

  QSettings settings(qApp->organizationName(), SW::Helper_t::appName());

  restoreGeometry(settings.value("position", QByteArray()).toByteArray());
  restoreState(settings.value("state", QByteArray()).toByteArray());

  settings.beginGroup("TableView");
  auto headerState = settings.value("columnLayout", QByteArray()).toByteArray();
  if(!headerState.isEmpty()){
	ui->tvUrl->horizontalHeader()->restoreState(headerState);
  }

  const bool showGrid = settings.value("showGrid", true).toBool(); // true por defecto
  ui->showGridAction->setChecked(showGrid);
  ui->tvUrl->setShowGrid(showGrid);

  settings.endGroup();

  settings.beginGroup(QStringLiteral("Editor"));

  const auto fontFamily = settings.value(QStringLiteral("fontFamily"), "Arial").toString();
  const auto fontSize = settings.value(QStringLiteral("fontSize"), 10).toInt();
  const auto colorStr = settings.value(QStringLiteral("textColor"), "").toString();

  QColor textColor{};

  if (!colorStr.isEmpty() && QColor(colorStr).isValid()) {
	// Ya existe un valor guardado, usarlo
	textColor = QColor(colorStr);
  } else {
	// Primera vez: tomar el color de texto de la paleta activa
	// igual que hace ConfigDialog con QPalette::ButtonText
	textColor = qApp->palette().color(QPalette::Text);
  }
  settings.endGroup();

  midleWidget->restoreFont(fontFamily, fontSize, textColor);

  auto ret = SW::Helper_t::nativeRegistryKeyExists("category name");

  QString categoryName{};
  if(ret && SW::Helper_t::sessionStatus_ == SW::SessionStatus::Session_closed){

	categoryName = settings.value("category name", QString()).toString();

	if(!categoryName.isEmpty() && ui->cboCategory->count() > 1){

	  auto foundIndex = ui->cboCategory->findText(categoryName);

	  if(foundIndex != -1){
		{

		  QSignalBlocker signalBlocker(ui->cboCategory);
		  ui->cboCategory->setCurrentIndex(foundIndex);
		}
		on_categorySelectedChanged(foundIndex);
	  }

	}
  }

  settings.beginGroup(QStringLiteral("Theme"));
  const auto theme = settings.value(QStringLiteral("theme Value"), 0).toInt();
  currentScheme_ = static_cast<Qt::ColorScheme>(theme);

  // LEER SI FUSION ESTABA ACTIVO (por defecto falso)
  bool useFusion = settings.value(QStringLiteral("useFusionStyle"), false).toBool();
  on_styleChanged(useFusion);

  settings.endGroup();

  applyPreferredTheme(static_cast<Qt::ColorScheme>(theme));

}

void MainForm::setCboCategoryToolTip() noexcept{

  const auto id = currentCategoryId();

  const auto categoryData = helperdb_.dataCategory(id);
  const auto desc=categoryData.value(1);
  //  QString desc{};
  if(desc.isEmpty()){
	ui->cboCategory->setToolTip(QStringLiteral("<p><cite><strong>Descripción de la categoría:</strong><br><br>"
											   "Esta categoría no cuenta con una descripción!</cite></p>"));
	return;
  }

  ui->cboCategory->setToolTip(QString("<p>"
									  "<cite><strong>Descripción de la categoría:</strong>"
									  "<br><br>%1</cite></p>").arg(desc));


}



bool MainForm::hasValidTableData() const noexcept{

  const auto tables = db_.tables(QSql::Tables);
  const QStringList excludedTables{"users", "sqlite_sequence"};

  return std::any_of(tables.cbegin(), tables.cend(),
					 [&excludedTables, this](const QString& tableName) -> bool {
					   if (excludedTables.contains(tableName)) {
						 return false;
					   }

					   QSqlQuery query(db_);
					   return query.exec(QString("SELECT 1 FROM %1 LIMIT 1").arg(tableName)) &&
							  query.next();
					 });

}

bool MainForm::validateSelectedRow() noexcept{

  if(!ui->tvUrl->selectionModel()->hasSelection()){
	QMessageBox::warning(this, SW::Helper_t::appName(), QStringLiteral("Seleccione una fila!\n"));
	return false;
  }
  return true;

}

bool MainForm::deleteAll() noexcept{

  const auto categoryId = currentCategoryId();

  if(helperdb_.deleteUrls(SW::DeleteUrlMode::ByCategory, categoryId)){
	if(helperdb_.deleteCategory(categoryId))
	  return true;
  }
  return false;

}

QColor MainForm::getEnfasisColor() const{

  QColor colorEnfasis{};

#if(QT_VERSION >= QT_VERSION_CHECK(6, 6, 0))
  colorEnfasis = qApp->palette().color(QPalette::Active, QPalette::Accent);
#else
  colorEnfasis = qApp->palette().color(QPalette::Active, QPalette::Highlight);
#endif

  return colorEnfasis;

}

void MainForm::editAction(bool op) noexcept{

  ui->btnEdit->setDisabled(op);
  ui->btnQuit->setDisabled(op);
  ui->btnopen->setDisabled(op);
  ui->tvUrl->setDisabled(op);

  // contextMenu_->setDisabled(op);

  ui->btnCancel->setEnabled(op);

}

void MainForm::writeSettings() const noexcept{

  QSettings settings(qApp->organizationName(), SW::Helper_t::appName());

  settings.setValue(QStringLiteral("position"), saveGeometry());
  settings.setValue(QStringLiteral("state"), saveState());

  settings.beginGroup("TableView");
  settings.setValue("columnLayout", ui->tvUrl->horizontalHeader()->saveState());
  settings.setValue("showGrid", ui->showGridAction->isChecked());
  settings.endGroup();

  if(ui->cboCategory->count() > 1 && SW::Helper_t::sessionStatus_ == SW::SessionStatus::Session_closed){
	settings.setValue(QStringLiteral("category name"), ui->cboCategory->currentText());
  }

  settings.beginGroup(QStringLiteral("Theme"));

  // Ahora usa currentScheme_ directamente, sin cboTheme
  settings.setValue(QStringLiteral("theme name"), themeType_.value(currentScheme_));
  settings.setValue(QStringLiteral("theme Value"), static_cast<uint32_t>(currentScheme_));

  // GUARDAR EL ESTADO ACTUAL DEL ESTILO
  bool isFusion = (qApp->style()->objectName().compare(QStringLiteral("fusion"), Qt::CaseInsensitive) == 0);
  settings.setValue(QStringLiteral("useFusionStyle"), isFusion);


  settings.endGroup();

  settings.beginGroup(QStringLiteral("Editor"));

  settings.setValue(QStringLiteral("fontFamily"), midleWidget->currentFont());
  settings.setValue(QStringLiteral("fontSize"), midleWidget->currentFontSize());
  settings.setValue(QStringLiteral("textColor"), midleWidget->textColor());
  settings.endGroup();

}



/**
 * @brief MainForm::showAboutDialog show abou dialog
 */
void MainForm::on_showAboutDialog(){

  AcercaDeDialog acercaDe(currentScheme_, this);
  acercaDe.setWindowTitle(SW::Helper_t::appName()+" - Acerca de");
  acercaDe.exec();

}

void MainForm::closeEvent(QCloseEvent *event){

  if(SW::Helper_t::sessionStatus_ != SW::SessionStatus::Session_closed){
	QMessageBox::warning(this, SW::Helper_t::appName(),
						 QStringLiteral("<cite>Hay una sesión activa en este momento.<br>"
										"Necesita cerrar sesión primero antes de salir, "
										"haciendo click en el boton:<br>"
										"<cite><strong style='background:#FFFF00;color:#FF5500;'>Cerrar sesión</strong></cite><br>"
										"O presionando la combinación de teclas Ctrl+Q.</cite>"));
	event->ignore();
	return;
  }

  writeSettings();
  QMainWindow::closeEvent(event);
  // event->accept();
}


void MainForm::showEvent(QShowEvent *event){

  QMainWindow::showEvent(event);
  auto headerState = SW::Helper_t::nativeRegistryKeyExists("TableView/columnLayout");

  if(!headerState){
	auto availableWidth = ui->tvUrl->viewport()->width();
	auto tableWidth = availableWidth/2;
	ui->tvUrl->setColumnWidth(1, tableWidth);
	ui->tvUrl->setColumnWidth(2, tableWidth);
  }


}

void MainForm::changeEvent(QEvent *event){

  if (event->type() == QEvent::PaletteChange || event->type() == QEvent::ApplicationPaletteChange) {
	verifyUserState();
	updateLblInfo();
  }

  QMainWindow::changeEvent(event);
}