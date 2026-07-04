#pragma once

#include "util/helper.hpp"

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class PublicUrlDialog;
}

class QAction;

class PublicUrlDialog : public QDialog{
  Q_OBJECT

public:
  explicit PublicUrlDialog(Qt::ColorScheme colorScheme, QWidget *parent = nullptr);
  ~PublicUrlDialog();

private:
  Ui::PublicUrlDialog *ui;

  Qt::ColorScheme colorScheme_{};

  QHash<uint32_t, QString> data_{};
  const QSqlDatabase db_{};

  QAction *openUrl_{nullptr};

  void loadDataComboBox();
  void writeSettings();
  void readSettings();

  void setupContextMenu();

  void applyIcons(Qt::ColorScheme scheme) noexcept;

  uint32_t currentCategoryId() const noexcept;


private slots:
  void on_openUrl();
  void on_loadDataTableView();

  void on_showContextMenu(const QPoint& pos);

  void on_categorySelectedChanged(int index);

  void on_showMaintenanceDialog(SW::OpenMode mode);


  // QWidget interface
protected:
  virtual void closeEvent(QCloseEvent *event) override;
  virtual void showEvent(QShowEvent *event) override;
};

