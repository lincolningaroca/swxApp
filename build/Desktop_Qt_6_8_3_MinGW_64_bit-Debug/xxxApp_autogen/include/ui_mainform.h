/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QAction *btnLogIn;
    QAction *btnLogOut;
    QAction *btnResetPassword;
    QAction *firstTimeLogInBtn;
    QAction *btnRestore;
    QAction *btnBackUp;
    QAction *actionAcerca_del_autor;
    QAction *showHideAction;
    QAction *showHideDatabaseAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QComboBox *cboCategory;
    QToolButton *btnNewCategory;
    QToolButton *btnEditCategory;
    QToolButton *btnDeleteCategory;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QComboBox *cboTheme;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *txtUrl;
    QTextEdit *pteDesc;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnQuit;
    QPushButton *btnopen;
    QPushButton *btnCancel;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QTableView *tvUrl;
    QMenuBar *menubar;
    QMenu *menuAyuda;
    QMenu *menuVer;
    QStatusBar *statusbar;
    QToolBar *logIntoolBar;
    QToolBar *dataBasetoolBar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName("MainForm");
        MainForm->resize(730, 561);
        btnLogIn = new QAction(MainForm);
        btnLogIn->setObjectName("btnLogIn");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/login.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnLogIn->setIcon(icon);
        btnLogIn->setMenuRole(QAction::MenuRole::NoRole);
        btnLogOut = new QAction(MainForm);
        btnLogOut->setObjectName("btnLogOut");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/logout.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnLogOut->setIcon(icon1);
        btnLogOut->setMenuRole(QAction::MenuRole::NoRole);
        btnResetPassword = new QAction(MainForm);
        btnResetPassword->setObjectName("btnResetPassword");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/Change_password-256.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnResetPassword->setIcon(icon2);
        btnResetPassword->setMenuRole(QAction::MenuRole::NoRole);
        firstTimeLogInBtn = new QAction(MainForm);
        firstTimeLogInBtn->setObjectName("firstTimeLogInBtn");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/Add_User.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        firstTimeLogInBtn->setIcon(icon3);
        firstTimeLogInBtn->setMenuRole(QAction::MenuRole::NoRole);
        btnRestore = new QAction(MainForm);
        btnRestore->setObjectName("btnRestore");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/server-database-restore-64.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnRestore->setIcon(icon4);
        btnRestore->setMenuRole(QAction::MenuRole::NoRole);
        btnBackUp = new QAction(MainForm);
        btnBackUp->setObjectName("btnBackUp");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/backup.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnBackUp->setIcon(icon5);
        btnBackUp->setMenuRole(QAction::MenuRole::NoRole);
        actionAcerca_del_autor = new QAction(MainForm);
        actionAcerca_del_autor->setObjectName("actionAcerca_del_autor");
        showHideAction = new QAction(MainForm);
        showHideAction->setObjectName("showHideAction");
        showHideDatabaseAction = new QAction(MainForm);
        showHideDatabaseAction->setObjectName("showHideDatabaseAction");
        centralwidget = new QWidget(MainForm);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        cboCategory = new QComboBox(groupBox);
        cboCategory->setObjectName("cboCategory");
        cboCategory->setMinimumSize(QSize(350, 0));
        cboCategory->setSizeIncrement(QSize(350, 0));

        horizontalLayout->addWidget(cboCategory);

        btnNewCategory = new QToolButton(groupBox);
        btnNewCategory->setObjectName("btnNewCategory");
        btnNewCategory->setMinimumSize(QSize(0, 24));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/img/2835260_control_more_options_menu select_list view_menu.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnNewCategory->setIcon(icon6);
        btnNewCategory->setAutoRaise(true);

        horizontalLayout->addWidget(btnNewCategory);

        btnEditCategory = new QToolButton(groupBox);
        btnEditCategory->setObjectName("btnEditCategory");
        btnEditCategory->setMinimumSize(QSize(0, 24));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/img/2835252_rewind_undo_loop_redo_arrow.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnEditCategory->setIcon(icon7);
        btnEditCategory->setAutoRaise(true);

        horizontalLayout->addWidget(btnEditCategory);

        btnDeleteCategory = new QToolButton(groupBox);
        btnDeleteCategory->setObjectName("btnDeleteCategory");
        btnDeleteCategory->setMinimumSize(QSize(0, 24));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/img/118277.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDeleteCategory->setIcon(icon8);
        btnDeleteCategory->setAutoRaise(true);

        horizontalLayout->addWidget(btnDeleteCategory);


        horizontalLayout_2->addWidget(groupBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName("verticalLayout");
        cboTheme = new QComboBox(groupBox_4);
        cboTheme->setObjectName("cboTheme");
        cboTheme->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(cboTheme);


        horizontalLayout_2->addWidget(groupBox_4);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        txtUrl = new QLineEdit(groupBox_2);
        txtUrl->setObjectName("txtUrl");

        verticalLayout_4->addWidget(txtUrl);

        pteDesc = new QTextEdit(groupBox_2);
        pteDesc->setObjectName("pteDesc");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pteDesc->sizePolicy().hasHeightForWidth());
        pteDesc->setSizePolicy(sizePolicy1);
        pteDesc->setMinimumSize(QSize(0, 100));
        pteDesc->setMaximumSize(QSize(16777215, 100));
        pteDesc->setSizeIncrement(QSize(0, 100));

        verticalLayout_4->addWidget(pteDesc);


        horizontalLayout_3->addWidget(groupBox_2);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName("groupBox_5");
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox_5);
        verticalLayout_2->setObjectName("verticalLayout_2");
        btnAdd = new QPushButton(groupBox_5);
        btnAdd->setObjectName("btnAdd");

        verticalLayout_2->addWidget(btnAdd);

        btnEdit = new QPushButton(groupBox_5);
        btnEdit->setObjectName("btnEdit");

        verticalLayout_2->addWidget(btnEdit);

        btnQuit = new QPushButton(groupBox_5);
        btnQuit->setObjectName("btnQuit");

        verticalLayout_2->addWidget(btnQuit);

        btnopen = new QPushButton(groupBox_5);
        btnopen->setObjectName("btnopen");

        verticalLayout_2->addWidget(btnopen);

        btnCancel = new QPushButton(groupBox_5);
        btnCancel->setObjectName("btnCancel");

        verticalLayout_2->addWidget(btnCancel);


        horizontalLayout_3->addWidget(groupBox_5);


        verticalLayout_5->addLayout(horizontalLayout_3);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tvUrl = new QTableView(groupBox_3);
        tvUrl->setObjectName("tvUrl");

        verticalLayout_3->addWidget(tvUrl);


        verticalLayout_5->addWidget(groupBox_3);

        MainForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainForm);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 730, 21));
        menuAyuda = new QMenu(menubar);
        menuAyuda->setObjectName("menuAyuda");
        menuVer = new QMenu(menubar);
        menuVer->setObjectName("menuVer");
        MainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MainForm);
        statusbar->setObjectName("statusbar");
        MainForm->setStatusBar(statusbar);
        logIntoolBar = new QToolBar(MainForm);
        logIntoolBar->setObjectName("logIntoolBar");
        MainForm->addToolBar(Qt::ToolBarArea::TopToolBarArea, logIntoolBar);
        dataBasetoolBar = new QToolBar(MainForm);
        dataBasetoolBar->setObjectName("dataBasetoolBar");
        MainForm->addToolBar(Qt::ToolBarArea::TopToolBarArea, dataBasetoolBar);

        menubar->addAction(menuVer->menuAction());
        menubar->addAction(menuAyuda->menuAction());
        menuAyuda->addAction(actionAcerca_del_autor);
        menuVer->addAction(showHideAction);
        menuVer->addAction(showHideDatabaseAction);
        logIntoolBar->addAction(btnLogIn);
        logIntoolBar->addAction(btnLogOut);
        logIntoolBar->addAction(btnResetPassword);
        logIntoolBar->addAction(firstTimeLogInBtn);
        logIntoolBar->addSeparator();
        dataBasetoolBar->addAction(btnRestore);
        dataBasetoolBar->addAction(btnBackUp);

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "MainForm", nullptr));
        btnLogIn->setText(QCoreApplication::translate("MainForm", "Login", nullptr));
#if QT_CONFIG(tooltip)
        btnLogIn->setToolTip(QCoreApplication::translate("MainForm", "Iniciar sesi\303\263n(Ctrl+L)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        btnLogIn->setShortcut(QCoreApplication::translate("MainForm", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        btnLogOut->setText(QCoreApplication::translate("MainForm", "logout", nullptr));
#if QT_CONFIG(shortcut)
        btnLogOut->setShortcut(QCoreApplication::translate("MainForm", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        btnResetPassword->setText(QCoreApplication::translate("MainForm", "resetpassword", nullptr));
#if QT_CONFIG(tooltip)
        btnResetPassword->setToolTip(QCoreApplication::translate("MainForm", "Reestablecer clave o password(Ctrl+Shift+P)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        btnResetPassword->setShortcut(QCoreApplication::translate("MainForm", "Ctrl+Shift+P", nullptr));
#endif // QT_CONFIG(shortcut)
        firstTimeLogInBtn->setText(QCoreApplication::translate("MainForm", "firtlogin", nullptr));
        btnRestore->setText(QCoreApplication::translate("MainForm", "restore", nullptr));
        btnBackUp->setText(QCoreApplication::translate("MainForm", "backup", nullptr));
        actionAcerca_del_autor->setText(QCoreApplication::translate("MainForm", "Acerca de", nullptr));
        showHideAction->setText(QCoreApplication::translate("MainForm", "Ver / ocultar login tool bar", nullptr));
        showHideDatabaseAction->setText(QCoreApplication::translate("MainForm", "Ver / ocultar database tool bar", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainForm", "Categor\303\255a", nullptr));
        btnNewCategory->setText(QCoreApplication::translate("MainForm", "...", nullptr));
        btnEditCategory->setText(QCoreApplication::translate("MainForm", "...", nullptr));
        btnDeleteCategory->setText(QCoreApplication::translate("MainForm", "...", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainForm", "Tema de la aplicaci\303\263n", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainForm", "Datos de la direcci\303\263n url", nullptr));
        groupBox_5->setTitle(QString());
        btnAdd->setText(QCoreApplication::translate("MainForm", "Agregar", nullptr));
        btnEdit->setText(QCoreApplication::translate("MainForm", "Editar", nullptr));
        btnQuit->setText(QCoreApplication::translate("MainForm", "Quitar", nullptr));
        btnopen->setText(QCoreApplication::translate("MainForm", "Abrir en el navegador", nullptr));
        btnCancel->setText(QCoreApplication::translate("MainForm", "Cancelar", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainForm", "Lista de direcciones url", nullptr));
        menuAyuda->setTitle(QCoreApplication::translate("MainForm", "Ayuda", nullptr));
        menuVer->setTitle(QCoreApplication::translate("MainForm", "Ver", nullptr));
        logIntoolBar->setWindowTitle(QCoreApplication::translate("MainForm", "toolBar", nullptr));
        dataBasetoolBar->setWindowTitle(QCoreApplication::translate("MainForm", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
