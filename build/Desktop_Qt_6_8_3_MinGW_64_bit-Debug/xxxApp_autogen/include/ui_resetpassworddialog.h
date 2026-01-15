/********************************************************************************
** Form generated from reading UI file 'resetpassworddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETPASSWORDDIALOG_H
#define UI_RESETPASSWORDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResetPasswordDialog
{
public:
    QVBoxLayout *verticalLayout_6;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLineEdit *txtUser;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnValidarUsuario;
    QWidget *page_2;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *txtPregunta;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *txtRespuesta;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnRespuesta;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_8;
    QLabel *label;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *txtPIN;
    QCheckBox *checkBox_2;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnClaveNumerica;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *txtNewPassword;
    QCheckBox *checkBox_3;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *txtRePassword;
    QCheckBox *checkBox_4;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnReset;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnAtras;

    void setupUi(QDialog *ResetPasswordDialog)
    {
        if (ResetPasswordDialog->objectName().isEmpty())
            ResetPasswordDialog->setObjectName("ResetPasswordDialog");
        ResetPasswordDialog->resize(464, 209);
        verticalLayout_6 = new QVBoxLayout(ResetPasswordDialog);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(5, 5, 5, 5);
        stackedWidget = new QStackedWidget(ResetPasswordDialog);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        txtUser = new QLineEdit(page);
        txtUser->setObjectName("txtUser");

        verticalLayout_3->addWidget(txtUser);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnValidarUsuario = new QPushButton(page);
        btnValidarUsuario->setObjectName("btnValidarUsuario");

        horizontalLayout->addWidget(btnValidarUsuario);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout = new QVBoxLayout(page_2);
        verticalLayout->setObjectName("verticalLayout");
        txtPregunta = new QPlainTextEdit(page_2);
        txtPregunta->setObjectName("txtPregunta");
        txtPregunta->setFrameShape(QFrame::Shape::NoFrame);
        txtPregunta->setFrameShadow(QFrame::Shadow::Plain);
        txtPregunta->setReadOnly(true);

        verticalLayout->addWidget(txtPregunta);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        txtRespuesta = new QLineEdit(page_2);
        txtRespuesta->setObjectName("txtRespuesta");

        horizontalLayout_6->addWidget(txtRespuesta);

        checkBox = new QCheckBox(page_2);
        checkBox->setObjectName("checkBox");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        checkBox->setIcon(icon);

        horizontalLayout_6->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnRespuesta = new QPushButton(page_2);
        btnRespuesta->setObjectName("btnRespuesta");

        horizontalLayout_2->addWidget(btnRespuesta);


        verticalLayout->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        verticalLayout_8 = new QVBoxLayout(page_3);
        verticalLayout_8->setObjectName("verticalLayout_8");
        label = new QLabel(page_3);
        label->setObjectName("label");

        verticalLayout_8->addWidget(label);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        txtPIN = new QLineEdit(page_3);
        txtPIN->setObjectName("txtPIN");

        horizontalLayout_7->addWidget(txtPIN);

        checkBox_2 = new QCheckBox(page_3);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setIcon(icon);

        horizontalLayout_7->addWidget(checkBox_2);


        verticalLayout_8->addLayout(horizontalLayout_7);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        btnClaveNumerica = new QPushButton(page_3);
        btnClaveNumerica->setObjectName("btnClaveNumerica");

        horizontalLayout_3->addWidget(btnClaveNumerica);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_8->addLayout(verticalLayout_4);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        verticalLayout_7 = new QVBoxLayout(page_4);
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        txtNewPassword = new QLineEdit(page_4);
        txtNewPassword->setObjectName("txtNewPassword");

        horizontalLayout_9->addWidget(txtNewPassword);

        checkBox_3 = new QCheckBox(page_4);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setIcon(icon);

        horizontalLayout_9->addWidget(checkBox_3);


        verticalLayout_7->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        txtRePassword = new QLineEdit(page_4);
        txtRePassword->setObjectName("txtRePassword");

        horizontalLayout_8->addWidget(txtRePassword);

        checkBox_4 = new QCheckBox(page_4);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setIcon(icon);

        horizontalLayout_8->addWidget(checkBox_4);


        verticalLayout_7->addLayout(horizontalLayout_8);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        btnReset = new QPushButton(page_4);
        btnReset->setObjectName("btnReset");

        horizontalLayout_4->addWidget(btnReset);


        verticalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_7->addLayout(verticalLayout_5);

        stackedWidget->addWidget(page_4);

        verticalLayout_6->addWidget(stackedWidget);

        line = new QFrame(ResetPasswordDialog);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_6->addWidget(line);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        btnAtras = new QPushButton(ResetPasswordDialog);
        btnAtras->setObjectName("btnAtras");

        horizontalLayout_5->addWidget(btnAtras);


        verticalLayout_6->addLayout(horizontalLayout_5);


        retranslateUi(ResetPasswordDialog);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ResetPasswordDialog);
    } // setupUi

    void retranslateUi(QDialog *ResetPasswordDialog)
    {
        ResetPasswordDialog->setWindowTitle(QCoreApplication::translate("ResetPasswordDialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("ResetPasswordDialog", "Nombre de usuario:", nullptr));
#if QT_CONFIG(tooltip)
        txtUser->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        txtUser->setPlaceholderText(QCoreApplication::translate("ResetPasswordDialog", "Ingrese su nombre de usuario", nullptr));
        btnValidarUsuario->setText(QCoreApplication::translate("ResetPasswordDialog", "Validar usuario", nullptr));
        txtRespuesta->setPlaceholderText(QCoreApplication::translate("ResetPasswordDialog", "Ingrese su respuesta aqui", nullptr));
#if QT_CONFIG(tooltip)
        checkBox->setToolTip(QCoreApplication::translate("ResetPasswordDialog", "Mostrar los caracteres", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox->setText(QString());
        btnRespuesta->setText(QCoreApplication::translate("ResetPasswordDialog", "Comprobar respuesta", nullptr));
        label->setText(QCoreApplication::translate("ResetPasswordDialog", "Ingrese PIN num\303\251rico:", nullptr));
        txtPIN->setPlaceholderText(QCoreApplication::translate("ResetPasswordDialog", "Ingrese un n\303\272mero de 4 d\303\255gitos", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_2->setToolTip(QCoreApplication::translate("ResetPasswordDialog", "Mostrar los caracteres.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_2->setText(QString());
        btnClaveNumerica->setText(QCoreApplication::translate("ResetPasswordDialog", "Comprobar N\303\272mero", nullptr));
        txtNewPassword->setPlaceholderText(QCoreApplication::translate("ResetPasswordDialog", "Ingrese su nuevo password o clave", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_3->setToolTip(QCoreApplication::translate("ResetPasswordDialog", "Mostrar los caracteres.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_3->setText(QString());
        txtRePassword->setPlaceholderText(QCoreApplication::translate("ResetPasswordDialog", "Vuelva a ingresar su nuevo Password o clave", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_4->setToolTip(QCoreApplication::translate("ResetPasswordDialog", "Mostrar los caracteres.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_4->setText(QString());
        btnReset->setText(QCoreApplication::translate("ResetPasswordDialog", "Cambiar password", nullptr));
        btnAtras->setText(QCoreApplication::translate("ResetPasswordDialog", "Volver atras", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResetPasswordDialog: public Ui_ResetPasswordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETPASSWORDDIALOG_H
