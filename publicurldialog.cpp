#include "publicurldialog.hpp"
#include "ui_publicurldialog.h"

#include <QSqlTableModel>
#include <QDesktopServices>
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>

#include "helperdatabase/helperdb.hpp"
#include "util/helper.hpp"
#include "swwidgets/swtablemodel.hpp"
#include "swwidgets/switemdelegate.hpp"

PublicUrlDialog::PublicUrlDialog(Qt::ColorScheme colorScheme, QWidget *parent) :
  QDialog(parent), ui(new Ui::PublicUrlDialog),
  db_{QSqlDatabase::database(QStringLiteral("xxxConection"))}{
  ui->setupUi(this);
  setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

  loadDataComboBox();
  loadDataTableView();

  readSettings();


  if(colorScheme == Qt::ColorScheme::Dark){

    SW::Helper_t::applyManjaroDarkColor(ui->urlTableView);
  }
  if(colorScheme == Qt::ColorScheme::Unknown){

    auto colorSch = SW::Helper_t::detectSystemColorScheme();
    if(colorSch == Qt::ColorScheme::Dark)
      SW::Helper_t::applyManjaroDarkColor(ui->urlTableView);
  }

  QObject::connect(ui->categoryComboBox, &QComboBox::currentTextChanged, this, &PublicUrlDialog::loadDataTableView);


  QObject::connect(ui->openPushButton, &QPushButton::clicked, this, [this](){

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
    });
}

PublicUrlDialog::~PublicUrlDialog(){
  delete ui;
}

void PublicUrlDialog::loadDataComboBox(){

  SW::HelperDataBase_t helperDb;

  auto userId_ = helperDb.getUser_id(SW::Helper_t::defaultUser, SW::User::U_public);
  data_ = helperDb.loadList_Category(userId_);

  ui->categoryComboBox->addItems(data_.values());

}

void PublicUrlDialog::loadDataTableView(){

  const auto categoryId_ = data_.key(ui->categoryComboBox->currentText());
  SWTableModel* xxxModel_ = new SWTableModel(this, db_);
  xxxModel_->setTable(QStringLiteral("urls"));
  xxxModel_->setFilter(QString("categoryid=%1").arg(categoryId_));

  xxxModel_->select();

  ui->urlTableView->setModel(xxxModel_);

  //setup headers to table view

  ui->urlTableView->hideColumn(0);
  ui->urlTableView->hideColumn(3);

  ui->urlTableView->model()->setHeaderData(1,Qt::Horizontal, "Dirección URL");
  ui->urlTableView->model()->setHeaderData(2,Qt::Horizontal, "Descripción");
  ui->urlTableView->setItemDelegate(new SWItemDelegate(ui->urlTableView));
  ui->urlTableView->resizeRowsToContents();
  ui->urlTableView->setAlternatingRowColors(true);

  ui->urlTableView->setMouseTracking(true);

}

void PublicUrlDialog::writeSettings(){

  QSettings settings(qApp->organizationName(), SW::Helper_t::appName());
  settings.beginGroup("Public_url_dialog");
  settings.setValue("Header_state", ui->urlTableView->horizontalHeader()->saveState());
  settings.endGroup();

}

void PublicUrlDialog::readSettings(){

  QSettings settings(qApp->organizationName(), SW::Helper_t::appName());
  settings.beginGroup("Public_url_dialog");
  const auto headerState = settings.value("Header_state", QByteArray()).toByteArray();
  settings.endGroup();

  ui->urlTableView->horizontalHeader()->restoreState(headerState);

}

void PublicUrlDialog::closeEvent(QCloseEvent *event){

  writeSettings();
  QDialog::closeEvent(event);
}

void PublicUrlDialog::showEvent(QShowEvent *event){

  auto headerState = SW::Helper_t::nativeRegistryKeyExists("Public_url_dialog/Header_state");

  if(!headerState){
    int availableWidth = ui->urlTableView->viewport()->width();
    auto headerWidth = availableWidth/2;
    ui->urlTableView->setColumnWidth(1, headerWidth);
    ui->urlTableView->setColumnWidth(2, headerWidth);
  }
  QDialog::showEvent(event);
}
