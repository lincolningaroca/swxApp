#include "publicurldialog.hpp"
#include "ui_publicurldialog.h"

#include "helperdatabase/helperdb.hpp"
#include "maintenanceurldialog.hpp"
#include "swwidgets/switemdelegate.hpp"
#include "swwidgets/swtablemodel.hpp"

#include <QAction>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QSqlTableModel>

PublicUrlDialog::PublicUrlDialog(Qt::ColorScheme colorScheme, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PublicUrlDialog),
  colorScheme_(colorScheme),
  db_{QSqlDatabase::database(QStringLiteral("xxxConection"))}{

  ui->setupUi(this);

  setMaximumSize(QSize(950,500));
  loadDataComboBox();
  on_loadDataTableView();

  setupContextMenu();

  applyIcons(colorScheme);

  ui->urlTableView->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->urlTableView, &QTableView::customContextMenuRequested, this, &PublicUrlDialog::on_showContextMenu);


  readSettings();


  QObject::connect(ui->categoryComboBox, &QComboBox::currentIndexChanged, this, &PublicUrlDialog::on_categorySelectedChanged);


  QObject::connect(ui->newToolButton, &QToolButton::clicked, this, [this](){on_showMaintenanceDialog(SW::OpenMode::New);});
  QObject::connect(ui->editToolButton, &QToolButton::clicked, this, [this](){on_showMaintenanceDialog(SW::OpenMode::Edit);});
  QObject::connect(ui->quitarToolButton, &QToolButton::clicked, this, PublicUrlDialog::on_deleteUrl);
  QObject::connect(ui->openPushButton, &QToolButton::clicked, this, &PublicUrlDialog::on_openUrl);


}

PublicUrlDialog::~PublicUrlDialog(){
  delete ui;
}

uint32_t PublicUrlDialog::currentCategoryId() const noexcept {
  return ui->categoryComboBox->currentData().isValid() ? ui->categoryComboBox->currentData().toUInt() : 1;
}

void PublicUrlDialog::loadDataComboBox(){

  SW::HelperDataBase_t helperDb;

  QSignalBlocker blocker(ui->categoryComboBox);
  ui->categoryComboBox->clear();

  auto userId_ = helperDb.getUser_id(SW::Helper_t::defaultUser, SW::User::U_public);
  data_ = helperDb.loadList_Category(userId_);

  auto it = data_.constBegin();
  while (it != data_.constEnd()) {
	ui->categoryComboBox->addItem(it.value(), it.key());
	++it;
  }

}

void PublicUrlDialog::on_categorySelectedChanged(int index){
  Q_UNUSED(index);
  on_loadDataTableView();
}

void PublicUrlDialog::on_deleteUrl(){

  if(!ui->urlTableView->selectionModel()->hasSelection()){
	QMessageBox::warning(this, qApp->applicationName(), "Seleccione una fila.");
	return;
  }

  auto currentRow = ui->urlTableView->currentIndex().row();

  const auto url = ui->urlTableView->model()->index(currentRow, 1).data().toString();

  QMessageBox msgBox(this);
  msgBox.setText(QString("<span>Confirma que desea eliminar esta dirección:<br>"
						 " <cite style='color:#ff0800;'><strong>%1</strong></cite></span>").arg(url));
  msgBox.setIcon(QMessageBox::Question);
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.button(QMessageBox::Yes)->setText("Eliminar");
  msgBox.button(QMessageBox::No)->setText("Cancelar");

  if(msgBox.exec() == QMessageBox::Yes){
	const auto urlId=ui->urlTableView->model()->index(currentRow, 0).data().toInt();
	if(helperdb_.deleteUrls(SW::DeleteUrlMode::ByUrlId, 0, urlId)){

	  on_loadDataTableView();
	}

  }

}


void PublicUrlDialog::on_showMaintenanceDialog(SW::OpenMode mode){

  QList<QVariant> dataUrl{};
  if(mode == SW::OpenMode::Edit){

	if(!ui->urlTableView->selectionModel()->hasSelection()){
	  QMessageBox::warning(this, qApp->applicationName(), "Seleccione una fila.");
	  return;
	}

	auto currentIndex = ui->urlTableView->currentIndex();
	auto id = ui->urlTableView->model()->index(currentIndex.row(), 0).data().toInt();

	// Leer directo de BD para evitar ambigüedad con el modelo
	QSqlQuery query(db_);
	query.prepare("SELECT url_id, url, desc FROM urls WHERE url_id = ?");
	query.addBindValue(id);

	if(!query.exec() || !query.next()){
	  QMessageBox::critical(this, qApp->applicationName(), "Error al leer los datos.");
	  return;
	}

	dataUrl.append(query.value(0).toInt());
	dataUrl.append(SW::Helper_t::decrypt(query.value(1).toString())); // url
	dataUrl.append(SW::Helper_t::decrypt(query.value(2).toString())); // desc
  }

  MaintenanceUrlDialog maintenanceDialog(colorScheme_, mode, dataUrl, currentCategoryId(), this);
  if(maintenanceDialog.exec() == QDialog::Accepted){
	on_loadDataTableView();
  }
}


void PublicUrlDialog::on_loadDataTableView(){

  const auto categoryId_ = currentCategoryId();

  SWTableModel* xxxModel_ = new SWTableModel(this, db_);
  xxxModel_->setTable(QStringLiteral("urls"));
  xxxModel_->setFilter(QString("categoryid=%1").arg(categoryId_));

  xxxModel_->select();

  ui->urlTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->urlTableView->setModel(xxxModel_);

  //setup headers to table view

  ui->urlTableView->hideColumn(0);
  ui->urlTableView->hideColumn(3);

  ui->urlTableView->model()->setHeaderData(1,Qt::Horizontal, "Dirección URL");
  ui->urlTableView->model()->setHeaderData(2,Qt::Horizontal, "Descripción");
  ui->urlTableView->setItemDelegate(new SWItemDelegate(ui->urlTableView));
  ui->urlTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui->urlTableView->verticalHeader()->setDefaultSectionSize(20);
  ui->urlTableView->setAlternatingRowColors(true);

  ui->urlTableView->setMouseTracking(true);

}

void PublicUrlDialog::on_showContextMenu(const QPoint &pos){

  auto index = ui->urlTableView->indexAt(pos);

  QMenu mainMenu(this);

  mainMenu.addAction(newUrl_);

  if(index.isValid()){

	mainMenu.addAction(editUrl_);
	mainMenu.addAction(deleteUrl_);
	mainMenu.addSeparator();
	mainMenu.addAction(openUrl_);
  }

  mainMenu.exec(ui->urlTableView->mapToGlobal(pos));

}

void PublicUrlDialog::writeSettings(){

  QSettings settings(qApp->organizationName(), SW::Helper_t::appName());
  settings.beginGroup("Public_url_dialog");
  settings.setValue("form_geometry", this->saveGeometry());
  settings.setValue("Header_state", ui->urlTableView->horizontalHeader()->saveState());
  settings.endGroup();

}

void PublicUrlDialog::readSettings(){

  QSettings settings(qApp->organizationName(), SW::Helper_t::appName());
  settings.beginGroup("Public_url_dialog");
  const auto formGeometry = settings.value("form_geometry", QByteArray()).toByteArray();
  const auto headerState = settings.value("Header_state", QByteArray()).toByteArray();
  settings.endGroup();

  this->restoreGeometry(formGeometry);
  ui->urlTableView->horizontalHeader()->restoreState(headerState);

}

void PublicUrlDialog::setupContextMenu(){

  newUrl_ = new QAction("Agregar nueva url", this);
  editUrl_ = new QAction("Edidar datos de la url", this);
  deleteUrl_ = new QAction("Eliminar url", this);
  openUrl_ = new QAction("Abrir dirección en el navegador", this);


  connect(newUrl_, &QAction::triggered, this, [this](){on_showMaintenanceDialog(SW::OpenMode::New);});
  connect(editUrl_, &QAction::triggered, this, [this](){on_showMaintenanceDialog(SW::OpenMode::Edit);});
  connect(deleteUrl_, &QAction::triggered, this, &PublicUrlDialog::on_deleteUrl);
  connect(openUrl_, &QAction::triggered, this, &PublicUrlDialog::on_openUrl);


}

void PublicUrlDialog::on_openUrl(){

  if(!ui->urlTableView->selectionModel()->hasSelection()){
	QMessageBox::warning(this, SW::Helper_t::appName(), QStringLiteral("Seleccione una fila!\n"));
	return;
  }


  const auto row_ = ui->urlTableView->currentIndex().row();
  const auto url_ = ui->urlTableView->model()->index(row_, 1).data().toString();

  if(!QDesktopServices::openUrl(QUrl(url_))){
	QMessageBox::critical(this, SW::Helper_t::appName(), QStringLiteral("Error al abrir la dirección url.\n"));
	return;
  }

}

void PublicUrlDialog::closeEvent(QCloseEvent *event){

  writeSettings();
  QDialog::closeEvent(event);
}

void PublicUrlDialog::showEvent(QShowEvent *event){

  QDialog::showEvent(event);
  auto headerState = SW::Helper_t::nativeRegistryKeyExists("Public_url_dialog/Header_state");

  if(!headerState){
	int availableWidth = ui->urlTableView->viewport()->width();
	auto headerWidth = availableWidth/2;
	ui->urlTableView->setColumnWidth(1, headerWidth);
	ui->urlTableView->setColumnWidth(2, headerWidth);
  }

}

void PublicUrlDialog::applyIcons(Qt::ColorScheme scheme) noexcept {

  const auto iconColor = SW::Helper_t::currentIconColor(scheme);

  if(newUrl_) newUrl_->setIcon(SW::Helper_t::svgIcon(":/img/link-new.svg", iconColor));
  if(editUrl_) editUrl_->setIcon(SW::Helper_t::svgIcon(":/img/link-edit.svg", iconColor));
  if(deleteUrl_) deleteUrl_->setIcon(SW::Helper_t::svgIcon(":/img/link-delete.svg", iconColor));
  if(openUrl_) openUrl_->setIcon(SW::Helper_t::svgIcon(":/img/link-open.svg", iconColor));

  ui->newToolButton->setIcon(SW::Helper_t::svgIcon(":/img/link-new.svg", iconColor));
  ui->editToolButton->setIcon(SW::Helper_t::svgIcon(":/img/link-edit.svg", iconColor));
  ui->quitarToolButton->setIcon(SW::Helper_t::svgIcon(":/img/link-delete.svg", iconColor));
  ui->openPushButton->setIcon(SW::Helper_t::svgIcon(":/img/link-open.svg", iconColor));

}
