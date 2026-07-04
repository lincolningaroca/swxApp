#pragma once

#include "util/helper.hpp"

#include <QDialog>

namespace Ui { class MaintenanceUrlDialog; }

class MaintenanceUrlDialog : public QDialog
{
  Q_OBJECT

public:
  explicit MaintenanceUrlDialog(Qt::ColorScheme colorScheme, SW::OpenMode mode, QWidget *parent = nullptr);
  ~MaintenanceUrlDialog();

private:
  Ui::MaintenanceUrlDialog *ui;
};
