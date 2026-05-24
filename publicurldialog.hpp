#pragma once

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

  QHash<uint32_t, QString> data_{};
  const QSqlDatabase db_{};

  QAction *openUrl_{nullptr};

  void loadDataComboBox();
  void writeSettings();
  void readSettings();

  void setupContextMenu();

  void applyIcons(Qt::ColorScheme scheme) noexcept;

private slots:
  void on_openUrl();
  void on_loadDataTableView();

  void on_showContextMenu(const QPoint& pos);

  // QWidget interface
protected:
  virtual void closeEvent(QCloseEvent *event) override;
  virtual void showEvent(QShowEvent *event) override;
};

