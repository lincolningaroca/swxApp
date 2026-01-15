#include "categorydialog.hpp"
#include "ui_categorydialog.h"

CategoryDialog::CategoryDialog(const QHash<uint32_t, QString> &categoryList, QWidget *parent) :
  QDialog(parent), ui(new Ui::CategoryDialog), data_{categoryList}{
  ui->setupUi(this);

  setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
  ui->categoryComboBox->addItems(data_.values());
  ui->cancelPushButton->setDefault(true);

  QObject::connect(ui->cancelPushButton, &QPushButton::clicked, this, [this](){ reject();});
  QObject::connect(ui->aceptPushButton, &QPushButton::clicked, this, [this](){ accept();});
}

CategoryDialog::~CategoryDialog(){
  delete ui;
}

uint32_t CategoryDialog::getCategoryId() const noexcept{
  return data_.key(ui->categoryComboBox->currentText());

}
