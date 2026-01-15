/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogInDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *txtUser;
    QLineEdit *txtPassword;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbLogIn;
    QPushButton *pbCancel;
    QFrame *line_2;
    QToolButton *btnOtherOptions;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *txtNewUser;
    QCheckBox *chkGenPassword;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *txtNewPassword;
    QCheckBox *checkBox_2;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *txtRePassword;
    QCheckBox *checkBox_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *cboRestoreType;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *txtfirstValue;
    QCheckBox *checkBox_4;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *txtConfirmValue;
    QCheckBox *checkBox_5;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnGenPassword;
    QPushButton *btnResetPassword;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnCreateUser;

    void setupUi(QDialog *LogInDialog)
    {
        if (LogInDialog->objectName().isEmpty())
            LogInDialog->setObjectName("LogInDialog");
        LogInDialog->resize(426, 444);
        gridLayout = new QGridLayout(LogInDialog);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(5);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        groupBox = new QGroupBox(LogInDialog);
        groupBox->setObjectName("groupBox");
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(4, 4, 4, 4);
        txtUser = new QLineEdit(groupBox);
        txtUser->setObjectName("txtUser");

        verticalLayout_3->addWidget(txtUser);

        txtPassword = new QLineEdit(groupBox);
        txtPassword->setObjectName("txtPassword");

        verticalLayout_3->addWidget(txtPassword);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(164, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbLogIn = new QPushButton(groupBox);
        pbLogIn->setObjectName("pbLogIn");

        horizontalLayout->addWidget(pbLogIn);

        pbCancel = new QPushButton(groupBox);
        pbCancel->setObjectName("pbCancel");

        horizontalLayout->addWidget(pbCancel);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_2);

        btnOtherOptions = new QToolButton(groupBox);
        btnOtherOptions->setObjectName("btnOtherOptions");
        btnOtherOptions->setMinimumSize(QSize(0, 24));

        horizontalLayout->addWidget(btnOtherOptions);


        verticalLayout_3->addLayout(horizontalLayout);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        widget = new QWidget(LogInDialog);
        widget->setObjectName("widget");
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(4, 4, 4, 4);
        txtNewUser = new QLineEdit(groupBox_2);
        txtNewUser->setObjectName("txtNewUser");

        verticalLayout_2->addWidget(txtNewUser);

        chkGenPassword = new QCheckBox(groupBox_2);
        chkGenPassword->setObjectName("chkGenPassword");

        verticalLayout_2->addWidget(chkGenPassword);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        txtNewPassword = new QLineEdit(groupBox_2);
        txtNewPassword->setObjectName("txtNewPassword");

        horizontalLayout_8->addWidget(txtNewPassword);

        checkBox_2 = new QCheckBox(groupBox_2);
        checkBox_2->setObjectName("checkBox_2");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        checkBox_2->setIcon(icon);

        horizontalLayout_8->addWidget(checkBox_2);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        txtRePassword = new QLineEdit(groupBox_2);
        txtRePassword->setObjectName("txtRePassword");

        horizontalLayout_7->addWidget(txtRePassword);

        checkBox_3 = new QCheckBox(groupBox_2);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setIcon(icon);

        horizontalLayout_7->addWidget(checkBox_3);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        cboRestoreType = new QComboBox(groupBox_2);
        cboRestoreType->setObjectName("cboRestoreType");

        horizontalLayout_3->addWidget(cboRestoreType);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        txtfirstValue = new QLineEdit(groupBox_2);
        txtfirstValue->setObjectName("txtfirstValue");

        horizontalLayout_6->addWidget(txtfirstValue);

        checkBox_4 = new QCheckBox(groupBox_2);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setIcon(icon);

        horizontalLayout_6->addWidget(checkBox_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        txtConfirmValue = new QLineEdit(groupBox_2);
        txtConfirmValue->setObjectName("txtConfirmValue");

        horizontalLayout_5->addWidget(txtConfirmValue);

        checkBox_5 = new QCheckBox(groupBox_2);
        checkBox_5->setObjectName("checkBox_5");
        checkBox_5->setIcon(icon);

        horizontalLayout_5->addWidget(checkBox_5);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName("checkBox");
        checkBox->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_4->addWidget(checkBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btnGenPassword = new QPushButton(groupBox_2);
        btnGenPassword->setObjectName("btnGenPassword");

        horizontalLayout_2->addWidget(btnGenPassword);

        btnResetPassword = new QPushButton(groupBox_2);
        btnResetPassword->setObjectName("btnResetPassword");

        horizontalLayout_2->addWidget(btnResetPassword);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnCreateUser = new QPushButton(groupBox_2);
        btnCreateUser->setObjectName("btnCreateUser");

        horizontalLayout_2->addWidget(btnCreateUser);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_4->addWidget(groupBox_2);


        gridLayout->addWidget(widget, 1, 0, 1, 1);


        retranslateUi(LogInDialog);

        QMetaObject::connectSlotsByName(LogInDialog);
    } // setupUi

    void retranslateUi(QDialog *LogInDialog)
    {
        LogInDialog->setWindowTitle(QCoreApplication::translate("LogInDialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("LogInDialog", "Datos de inicio de sesi\303\263n", nullptr));
        pbLogIn->setText(QCoreApplication::translate("LogInDialog", "Ingresar", nullptr));
        pbCancel->setText(QCoreApplication::translate("LogInDialog", "Salir", nullptr));
        btnOtherOptions->setText(QCoreApplication::translate("LogInDialog", "...", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("LogInDialog", "Nuevo usuario", nullptr));
        chkGenPassword->setText(QCoreApplication::translate("LogInDialog", "Generar password", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_2->setToolTip(QCoreApplication::translate("LogInDialog", "Mostrar los caracteres", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_2->setText(QString());
        txtRePassword->setPlaceholderText(QString());
#if QT_CONFIG(tooltip)
        checkBox_3->setToolTip(QCoreApplication::translate("LogInDialog", "Mostrar los caracteres", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_3->setText(QString());
        label->setText(QCoreApplication::translate("LogInDialog", "M\303\251todo de recuperaci\303\263n:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_4->setToolTip(QCoreApplication::translate("LogInDialog", "Mostrar los caracteres", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_4->setText(QString());
#if QT_CONFIG(tooltip)
        checkBox_5->setToolTip(QCoreApplication::translate("LogInDialog", "Mostrar los caracteres", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_5->setText(QString());
        checkBox->setText(QCoreApplication::translate("LogInDialog", "Perfil de usuario - (USER)", nullptr));
        btnGenPassword->setText(QCoreApplication::translate("LogInDialog", "Generar password", nullptr));
#if QT_CONFIG(tooltip)
        btnResetPassword->setToolTip(QCoreApplication::translate("LogInDialog", "(Ctrl +Shift + P)", nullptr));
#endif // QT_CONFIG(tooltip)
        btnResetPassword->setText(QCoreApplication::translate("LogInDialog", "Reset password", nullptr));
#if QT_CONFIG(shortcut)
        btnResetPassword->setShortcut(QCoreApplication::translate("LogInDialog", "Ctrl+Shift+P", nullptr));
#endif // QT_CONFIG(shortcut)
        btnCreateUser->setText(QCoreApplication::translate("LogInDialog", "Crear usuario", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogInDialog: public Ui_LogInDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
