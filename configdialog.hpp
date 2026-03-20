#pragma once

#include <QDialog>

namespace Ui { class ConfigDialog; }

class ConfigDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ConfigDialog(Qt::ColorScheme currentScheme, QWidget *parent = nullptr);
  ~ConfigDialog();

  // Retorna el esquema seleccionado por el usuario
  Qt::ColorScheme selectedScheme() const noexcept;

private:
  Ui::ConfigDialog *ui;

  Qt::ColorScheme selectedScheme_{Qt::ColorScheme::Unknown};

  void initDialog() noexcept;
  void setCurrentTheme(Qt::ColorScheme scheme) noexcept;
  void applyThemeSelection() noexcept;

private slots:
  void on_btnSystem_clicked();
  void on_btnLight_clicked();
  void on_btnDark_clicked();
  void on_btnOk_clicked();
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
  void on_listMenu_currentRowChanged(int row);

signals:
  void themeChanged(Qt::ColorScheme scheme);




};
