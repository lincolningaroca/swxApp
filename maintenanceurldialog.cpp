#include "maintenanceurldialog.hpp"
#include "ui_maintenanceurldialog.h"

MaintenanceUrlDialog::MaintenanceUrlDialog(Qt::ColorScheme colorScheme, SW::OpenMode mode, QWidget *parent)
  : QDialog(parent), ui(new Ui::MaintenanceUrlDialog)
{
  ui->setupUi(this);

  const auto iconColor = SW::Helper_t::currentIconColor(colorScheme);

  if (ui->descTextEdit) {
	ui->descTextEdit->applyIcons(iconColor);
  }

  if(mode == SW::OpenMode::New){

	setWindowTitle("Agregar nueva url");
	ui->aceptpushButton->setText("Guardar datos");
  }else{

	setWindowTitle("Editar datos url");
	ui->aceptpushButton->setText("Guardar cambios");
  }
}

MaintenanceUrlDialog::~MaintenanceUrlDialog()
{
  delete ui;
}
