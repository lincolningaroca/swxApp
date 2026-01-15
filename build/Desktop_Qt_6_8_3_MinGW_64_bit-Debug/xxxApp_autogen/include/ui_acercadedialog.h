/********************************************************************************
** Form generated from reading UI file 'acercadedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACERCADEDIALOG_H
#define UI_ACERCADEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AcercaDeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *acercaDeTab;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *tbAcercaDe;
    QWidget *licenciaTab;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *tbLicencia;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblLicencia;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblAcercaQt;
    QWidget *companyTab;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblLogo;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCerrar;

    void setupUi(QDialog *AcercaDeDialog)
    {
        if (AcercaDeDialog->objectName().isEmpty())
            AcercaDeDialog->setObjectName("AcercaDeDialog");
        AcercaDeDialog->resize(651, 470);
        verticalLayout = new QVBoxLayout(AcercaDeDialog);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(AcercaDeDialog);
        tabWidget->setObjectName("tabWidget");
        acercaDeTab = new QWidget();
        acercaDeTab->setObjectName("acercaDeTab");
        verticalLayout_2 = new QVBoxLayout(acercaDeTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tbAcercaDe = new QTextBrowser(acercaDeTab);
        tbAcercaDe->setObjectName("tbAcercaDe");

        verticalLayout_2->addWidget(tbAcercaDe);

        tabWidget->addTab(acercaDeTab, QString());
        licenciaTab = new QWidget();
        licenciaTab->setObjectName("licenciaTab");
        verticalLayout_3 = new QVBoxLayout(licenciaTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tbLicencia = new QTextBrowser(licenciaTab);
        tbLicencia->setObjectName("tbLicencia");

        verticalLayout_3->addWidget(tbLicencia);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lblLicencia = new QLabel(licenciaTab);
        lblLicencia->setObjectName("lblLicencia");

        horizontalLayout_2->addWidget(lblLicencia);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        lblAcercaQt = new QLabel(licenciaTab);
        lblAcercaQt->setObjectName("lblAcercaQt");

        horizontalLayout_2->addWidget(lblAcercaQt);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tabWidget->addTab(licenciaTab, QString());
        companyTab = new QWidget();
        companyTab->setObjectName("companyTab");
        verticalLayout_4 = new QVBoxLayout(companyTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        lblLogo = new QLabel(companyTab);
        lblLogo->setObjectName("lblLogo");
        lblLogo->setScaledContents(true);

        verticalLayout_4->addWidget(lblLogo);

        tabWidget->addTab(companyTab, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnCerrar = new QPushButton(AcercaDeDialog);
        btnCerrar->setObjectName("btnCerrar");

        horizontalLayout->addWidget(btnCerrar);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AcercaDeDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AcercaDeDialog);
    } // setupUi

    void retranslateUi(QDialog *AcercaDeDialog)
    {
        AcercaDeDialog->setWindowTitle(QCoreApplication::translate("AcercaDeDialog", "Dialog", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(acercaDeTab), QCoreApplication::translate("AcercaDeDialog", "Acerca de", nullptr));
        lblLicencia->setText(QCoreApplication::translate("AcercaDeDialog", "Ver licencia", nullptr));
        lblAcercaQt->setText(QCoreApplication::translate("AcercaDeDialog", "Acerca de Qt", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(licenciaTab), QCoreApplication::translate("AcercaDeDialog", "Licencia", nullptr));
        lblLogo->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(companyTab), QCoreApplication::translate("AcercaDeDialog", "SWSystem's", nullptr));
        btnCerrar->setText(QCoreApplication::translate("AcercaDeDialog", "Cerrar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AcercaDeDialog: public Ui_AcercaDeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACERCADEDIALOG_H
