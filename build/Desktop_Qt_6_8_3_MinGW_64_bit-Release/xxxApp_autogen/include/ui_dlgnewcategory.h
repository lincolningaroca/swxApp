/********************************************************************************
** Form generated from reading UI file 'dlgnewcategory.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGNEWCATEGORY_H
#define UI_DLGNEWCATEGORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dlgNewCategory
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLineEdit *txtCategory;
    QPlainTextEdit *pteDesc;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *dlgNewCategory)
    {
        if (dlgNewCategory->objectName().isEmpty())
            dlgNewCategory->setObjectName("dlgNewCategory");
        dlgNewCategory->resize(381, 194);
        verticalLayout_2 = new QVBoxLayout(dlgNewCategory);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        groupBox = new QGroupBox(dlgNewCategory);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        txtCategory = new QLineEdit(groupBox);
        txtCategory->setObjectName("txtCategory");

        verticalLayout->addWidget(txtCategory);

        pteDesc = new QPlainTextEdit(groupBox);
        pteDesc->setObjectName("pteDesc");

        verticalLayout->addWidget(pteDesc);


        verticalLayout_2->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(dlgNewCategory);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(dlgNewCategory);

        QMetaObject::connectSlotsByName(dlgNewCategory);
    } // setupUi

    void retranslateUi(QDialog *dlgNewCategory)
    {
        dlgNewCategory->setWindowTitle(QCoreApplication::translate("dlgNewCategory", "Dialog", nullptr));
        groupBox->setTitle(QString());
        txtCategory->setPlaceholderText(QCoreApplication::translate("dlgNewCategory", "Nombre de categor\303\255a", nullptr));
        pteDesc->setPlaceholderText(QCoreApplication::translate("dlgNewCategory", "Descripci\303\263n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgNewCategory: public Ui_dlgNewCategory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGNEWCATEGORY_H
