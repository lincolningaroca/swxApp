#include "configdialog.hpp"
#include "ui_configdialog.h"

#include <QCloseEvent>
#include <QSettings>

ConfigDialog::ConfigDialog(Qt::ColorScheme currentScheme, QWidget *parent)
  : QDialog(parent), ui(new Ui::ConfigDialog),
  selectedScheme_(currentScheme),
  originalScheme_(currentScheme)
{
  ui->setupUi(this);

  setWindowTitle(QStringLiteral("Configuración"));
  setFixedSize(480, 380);

  initDialog();
  setCurrentTheme(selectedScheme_);

  restoreLastSelection();

  // Navegación lateral
  QObject::connect(ui->listMenu, &QListWidget::currentRowChanged, this, &ConfigDialog::on_listMenu_currentRowChanged);

  // Botones de tema
  QObject::connect(ui->btnSystem, &QPushButton::clicked, this, &ConfigDialog::on_btnSystem_clicked);
  QObject::connect(ui->btnLight,  &QPushButton::clicked, this, &ConfigDialog::on_btnLight_clicked);
  QObject::connect(ui->btnDark,   &QPushButton::clicked, this, &ConfigDialog::on_btnDark_clicked);

  // Cuando MainForm aplica el tema (via Apply), refrescamos los botones del diálogo
  QObject::connect(this, &ConfigDialog::themeChanged, this, [this](Qt::ColorScheme scheme){
	setCurrentTheme(scheme);
  });

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

  // Leemos el color de texto real de la paleta en este momento,
  // ya que "palette(text)" en stylesheet no se re-evalua cuando el tema cambia en vivo
  const QString textColor = qApp->palette().color(QPalette::ButtonText).name();
  const QString normalStyle = QString(R"(
		QPushButton {
			border: 1px solid #555;
			border-radius: 6px;
			background-color: transparent;
			color: %1;
		}
	)").arg(textColor);

  ui->btnSystem->setStyleSheet(normalStyle);
  ui->btnLight->setStyleSheet(normalStyle);
  ui->btnDark->setStyleSheet(normalStyle);

  switch(scheme){
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

void ConfigDialog::saveLastSelection(){

  QSettings settings(qApp->organizationName(), qApp->applicationName());

  auto *currentItem = ui->listMenu->currentItem();

  if(currentItem)
	settings.setValue("configDialogLastSelection", currentItem->text());

}

void ConfigDialog::restoreLastSelection(){

  QSettings settings(qApp->organizationName(), qApp->applicationName());
  auto lastText = settings.value("configDialogLastSelection", "").toString();
  if(!lastText.isEmpty()){

	QList<QListWidgetItem *> items = ui->listMenu->findItems(lastText, Qt::MatchExactly);

	if(!items.isEmpty()){

	  ui->listMenu->setCurrentItem(items.first());
	  ui->listMenu->scrollToItem(items.first());
	}
  }

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
  saveLastSelection();
  accept();

}

void ConfigDialog::on_btnApply_clicked(){

  applyThemeSelection();
  // No cierra el diálogo

}

void ConfigDialog::on_btnCancel_clicked(){

  emit themeChanged(originalScheme_);
  reject();

}

// ── Slots de navegación ──────────────────────────────────────────────────────
void ConfigDialog::on_listMenu_currentRowChanged(int row){

  if(row != -1)
	ui->stackedWidget->setCurrentIndex(row);

}

void ConfigDialog::closeEvent(QCloseEvent *event){

  saveLastSelection();
  emit themeChanged(originalScheme_);
  event->accept();

}