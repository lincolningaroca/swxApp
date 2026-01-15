/********************************************************************************
** Form generated from reading UI file 'publicurldialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUBLICURLDIALOG_H
#define UI_PUBLICURLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PublicUrlDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *categoryComboBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTableView *urlTableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *openPushButton;

    void setupUi(QDialog *PublicUrlDialog)
    {
        if (PublicUrlDialog->objectName().isEmpty())
            PublicUrlDialog->setObjectName("PublicUrlDialog");
        PublicUrlDialog->resize(691, 467);
        verticalLayout_2 = new QVBoxLayout(PublicUrlDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(PublicUrlDialog);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label);

        categoryComboBox = new QComboBox(PublicUrlDialog);
        categoryComboBox->setObjectName("categoryComboBox");

        horizontalLayout_2->addWidget(categoryComboBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        groupBox = new QGroupBox(PublicUrlDialog);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        urlTableView = new QTableView(groupBox);
        urlTableView->setObjectName("urlTableView");
        urlTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        urlTableView->setShowGrid(false);

        verticalLayout->addWidget(urlTableView);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        openPushButton = new QPushButton(PublicUrlDialog);
        openPushButton->setObjectName("openPushButton");

        horizontalLayout->addWidget(openPushButton);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(PublicUrlDialog);

        QMetaObject::connectSlotsByName(PublicUrlDialog);
    } // setupUi

    void retranslateUi(QDialog *PublicUrlDialog)
    {
        PublicUrlDialog->setWindowTitle(QCoreApplication::translate("PublicUrlDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("PublicUrlDialog", "Categoria: ", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PublicUrlDialog", "Lista de direcciones p\303\272blicas", nullptr));
        openPushButton->setText(QCoreApplication::translate("PublicUrlDialog", "Abrir en el navegador", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PublicUrlDialog: public Ui_PublicUrlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUBLICURLDIALOG_H
