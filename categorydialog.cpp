#include "categorydialog.hpp"
#include "ui_categorydialog.h"

CategoryDialog::CategoryDialog(const QHash<uint32_t, QString> &categoryList, QWidget *parent) :
  QDialog(parent), ui(new Ui::CategoryDialog){
  ui->setupUi(this);

  setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

  loadCategoryComboBox(categoryList);

  ui->cancelPushButton->setDefault(true);

  QObject::connect(ui->cancelPushButton, &QPushButton::clicked, this, [this](){ reject();});
  QObject::connect(ui->aceptPushButton, &QPushButton::clicked, this, [this](){ accept();});
}

CategoryDialog::~CategoryDialog(){
  delete ui;
}

uint32_t CategoryDialog::getCategoryId() const noexcept{
  return ui->categoryComboBox->currentData().isValid() ? ui->categoryComboBox->currentData().toUInt() : 1;

}

void CategoryDialog::loadCategoryComboBox(const QHash<uint32_t, QString>& categoryList) noexcept {

  QSignalBlocker blocker(ui->categoryComboBox);
  ui->categoryComboBox->clear();

  auto it = categoryList.constBegin();
  while (it != categoryList.constEnd()) {
	ui->categoryComboBox->addItem(it.value(), it.key());
	++it;
  }
}
