/********************************************************************************
** Form generated from reading UI file 'categorydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATEGORYDIALOG_H
#define UI_CATEGORYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CategoryDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *categoryComboBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *aceptPushButton;
    QPushButton *cancelPushButton;

    void setupUi(QDialog *CategoryDialog)
    {
        if (CategoryDialog->objectName().isEmpty())
            CategoryDialog->setObjectName("CategoryDialog");
        CategoryDialog->resize(392, 123);
        verticalLayout_2 = new QVBoxLayout(CategoryDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(CategoryDialog);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        categoryComboBox = new QComboBox(groupBox);
        categoryComboBox->setObjectName("categoryComboBox");

        verticalLayout->addWidget(categoryComboBox);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        aceptPushButton = new QPushButton(CategoryDialog);
        aceptPushButton->setObjectName("aceptPushButton");

        horizontalLayout->addWidget(aceptPushButton);

        cancelPushButton = new QPushButton(CategoryDialog);
        cancelPushButton->setObjectName("cancelPushButton");

        horizontalLayout->addWidget(cancelPushButton);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(CategoryDialog);

        QMetaObject::connectSlotsByName(CategoryDialog);
    } // setupUi

    void retranslateUi(QDialog *CategoryDialog)
    {
        CategoryDialog->setWindowTitle(QCoreApplication::translate("CategoryDialog", "Dialog", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("CategoryDialog", "Seleccione una categor\303\255a, a donde sera movida la url", nullptr));
        aceptPushButton->setText(QCoreApplication::translate("CategoryDialog", "Cambiar de categor\303\255a", nullptr));
        cancelPushButton->setText(QCoreApplication::translate("CategoryDialog", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CategoryDialog: public Ui_CategoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATEGORYDIALOG_H
