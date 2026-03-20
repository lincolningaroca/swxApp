#include "configdialog.hpp"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(Qt::ColorScheme currentScheme, QWidget *parent)
  : QDialog(parent), ui(new Ui::ConfigDialog), selectedScheme_(currentScheme)
{
  ui->setupUi(this);

  setWindowTitle(QStringLiteral("Configuración"));
  setFixedSize(480, 380);

  initDialog();
  setCurrentTheme(selectedScheme_);
  // Navegación lateral
  QObject::connect(ui->listMenu, &QListWidget::currentRowChanged,
                   this, &ConfigDialog::on_listMenu_currentRowChanged);

  // Botones de tema
  QObject::connect(ui->btnSystem, &QPushButton::clicked, this, &ConfigDialog::on_btnSystem_clicked);
  QObject::connect(ui->btnLight,  &QPushButton::clicked, this, &ConfigDialog::on_btnLight_clicked);
  QObject::connect(ui->btnDark,   &QPushButton::clicked, this, &ConfigDialog::on_btnDark_clicked);

  // Botones de diálogo
  QObject::connect(ui->btnOk,     &QPushButton::clicked, this, &ConfigDialog::on_btnOk_clicked);
  QObject::connect(ui->btnApply,  &QPushButton::clicked, this, &ConfigDialog::on_btnApply_clicked);
  QObject::connect(ui->btnCancel, &QPushButton::clicked, this, &ConfigDialog::on_btnCancel_clicked);
}

ConfigDialog::~ConfigDialog()
{
  delete ui;
}

Qt::ColorScheme ConfigDialog::selectedScheme() const noexcept{

  return selectedScheme_;
}

void ConfigDialog::initDialog() noexcept{

  ui->listMenu->setIconSize(QSize(24, 24));
  ui->listMenu->setSpacing(2);

  auto *itemApariencia = new QListWidgetItem(QIcon(":/img/palette.png"), "  Apariencia");
  itemApariencia->setSizeHint(QSize(130, 40));
  ui->listMenu->addItem(itemApariencia);

  // auto *itemGeneral = new QListWidgetItem(QIcon(":/img/flat_seo-47-64.png"), "  General");
  // itemGeneral->setSizeHint(QSize(130, 40));
  // ui->listMenu->addItem(itemGeneral);

  // auto *itemAcerca = new QListWidgetItem(QIcon(":/img/7278151.png"), "  Acerca de");
  // itemAcerca->setSizeHint(QSize(130, 40));
  // ui->listMenu->addItem(itemAcerca);

  // ui->listMenu->setCurrentRow(0);
}

void ConfigDialog::setCurrentTheme(Qt::ColorScheme scheme) noexcept{

  const QString selectedStyle = R"(
        QPushButton {
            border: 2px solid #4A90D9;
            border-radius: 6px;
            background-color: #2D5A8E;
            color: white;
            font-weight: bold;
        }
    )";

  const QString normalStyle = R"(
        QPushButton {
            border: 1px solid #555;
            border-radius: 6px;
            background-color: transparent;
            color: palette(text);
        }
    )";

  ui->btnSystem->setStyleSheet(normalStyle);
  ui->btnLight->setStyleSheet(normalStyle);
  ui->btnDark->setStyleSheet(normalStyle);

  switch(selectedScheme_){
    case Qt::ColorScheme::Unknown:
      ui->btnSystem->setStyleSheet(selectedStyle);
      break;
    case Qt::ColorScheme::Light:
      ui->btnLight->setStyleSheet(selectedStyle);
      break;
    case Qt::ColorScheme::Dark:
      ui->btnDark->setStyleSheet(selectedStyle);
      break;
  }
}

void ConfigDialog::applyThemeSelection() noexcept{

  emit themeChanged(selectedScheme_);

}

// ── Slots de selección de tema ───────────────────────────────────────────────

void ConfigDialog::on_btnSystem_clicked(){

  selectedScheme_ = Qt::ColorScheme::Unknown;
  setCurrentTheme(selectedScheme_);

}

void ConfigDialog::on_btnLight_clicked(){

  selectedScheme_ = Qt::ColorScheme::Light;
  setCurrentTheme(selectedScheme_);

}

void ConfigDialog::on_btnDark_clicked(){

  selectedScheme_ = Qt::ColorScheme::Dark;
  setCurrentTheme(selectedScheme_);

}

// ── Slots de botones de diálogo ──────────────────────────────────────────────
void ConfigDialog::on_btnOk_clicked(){

  applyThemeSelection();
  accept();

}

void ConfigDialog::on_btnApply_clicked(){

  applyThemeSelection();
  // No cierra el diálogo

}

void ConfigDialog::on_btnCancel_clicked(){

  reject();

}

// ── Slots de navegación ──────────────────────────────────────────────────────
void ConfigDialog::on_listMenu_currentRowChanged(int row){

  ui->stackedWidget->setCurrentIndex(row);

}
