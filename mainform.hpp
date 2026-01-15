#pragma once

#include <QMainWindow>
#include <QSqlDatabase>

#include "util/helper.hpp"
#include "helperdatabase/helperdb.hpp"

class QLabel;
class QAction;
class QMenu;
struct SWTableModel;
class SWLabel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainForm; }
QT_END_NAMESPACE

class MainForm : public QMainWindow
{
  Q_OBJECT

public:
  MainForm(QWidget *parent = nullptr);
  ~MainForm();

private:
  Ui::MainForm *ui;

  //metodos privados de la aplicacion
private:

  int loadSchemePreference();

  void loadThemeComboBox() noexcept;
  void loadListCategory(uint32_t user_id) noexcept;
  void applyPreferredTheme(int pref);
  void has_data() noexcept;
  void hastvUrlData() noexcept;
  void checkStatusContextMenu();
  void canRestoreDataBase() const noexcept;
  void verifyAppColorScheme();
  void setLabelInfo(Qt::ColorScheme color, const QString& userName=SW::Helper_t::currentUser_.value(SW::User::U_public)) noexcept;
  void initFrm() noexcept;
  void setUpTable(uint32_t categoryId = 1) noexcept;
  void setUpTableHeaders() const noexcept;
  void canCreateBackUp() const noexcept;
  void canStartSession() noexcept;
  void setUpCboCategoryContextMenu() noexcept;
  void setUptvUrlContextMenu() noexcept;
  void verifyContextMenu() noexcept;
  void openUrl() noexcept;
  void readSettings() noexcept;
  void loadLblSchemePreference();
  void setCboCategoryToolTip() noexcept;
  void checkStatusSessionColor(const QString& text);
  void editAction(bool op) noexcept;
  void writeSettings() const noexcept;
  void categorySelectedChanged(const QString& text);
  void setUpShowMenuAction();


  bool hasValidTableData() const noexcept;
  bool validateSelectedRow() noexcept;
  bool deleteAll() noexcept;




  //variables y estructuras privadas de la aplicacion

  const QSqlDatabase db_{};

  QAction* delCategory_{ nullptr };
  QAction* openUrl_{ nullptr };
  QAction* editUrl_{ nullptr };
  QAction* quitUrl_{ nullptr };
  QAction* showDescDetail_{ nullptr };
  QAction* showPublicUrl_{ nullptr };
  QAction* moveUrl_{ nullptr };
  QAction* exportToExcelFile_{nullptr};

  QMenu* contextMenu_{nullptr};
  QMenu* contextMenu{nullptr};

  const QHash<Qt::ColorScheme, QString> themeType_{
    {Qt::ColorScheme::Unknown, "Predeterminado del sistema"},
    {Qt::ColorScheme::Light, "Modo Claro"},
    {Qt::ColorScheme::Dark, "Modo Oscuro"}
  };

  QHash<uint32_t, QString> categoryList_{};
  QHash<uint32_t, QString> urlList_{};
  SW::HelperDataBase_t helperdb_{};
  inline static uint32_t userId_{0};
  SWTableModel* xxxModel_{ nullptr };

  QLabel *lblIcon_{nullptr};
  QLabel *lblState_{nullptr};
  SWLabel *lblInfo_{nullptr};



private slots:

  void on_showAboutDialog();
  void on_showNewCategoryDialog();
  void on_loadLoginForm();
  void on_showResetPasswordDialog();
  void on_exportToExcel();
  void on_deleteCategory();
  void on_addNewUrl();
  void on_editCategory();
  void on_quitUrl();
  void on_btnEdit();
  void on_themeSelectedChanged(int index);
  void on_categorySelectedChanged(const QString& text);
  void on_callLogout();
  void on_makeBackup();
  void on_restoreDatabase();
  void on_cancelAction();
  void on_showAllDescription();
  void on_showPublicUrlDialog();
  void on_moveUrl();
  void on_firstTimeLoginDialog();



  // QWidget interface
protected:
  virtual void closeEvent(QCloseEvent *event) override;
  virtual void showEvent(QShowEvent *event) override;

  // QObject interface
public:
  virtual bool eventFilter(QObject *watched, QEvent *event) override;
};
