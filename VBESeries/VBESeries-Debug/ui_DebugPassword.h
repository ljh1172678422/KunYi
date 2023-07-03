/********************************************************************************
** Form generated from reading UI file 'DebugPassword.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGPASSWORD_H
#define UI_DEBUGPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DebugPassword
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditPwd;
    QHBoxLayout *horizontalLayout;
    QPushButton *BtnOK;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnCancel;

    void setupUi(QDialog *DebugPassword)
    {
        if (DebugPassword->objectName().isEmpty())
            DebugPassword->setObjectName(QString::fromUtf8("DebugPassword"));
        DebugPassword->resize(217, 119);
        gridLayout = new QGridLayout(DebugPassword);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(DebugPassword);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEditPwd = new QLineEdit(DebugPassword);
        lineEditPwd->setObjectName(QString::fromUtf8("lineEditPwd"));
        lineEditPwd->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEditPwd);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        BtnOK = new QPushButton(DebugPassword);
        BtnOK->setObjectName(QString::fromUtf8("BtnOK"));

        horizontalLayout->addWidget(BtnOK);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtnCancel = new QPushButton(DebugPassword);
        BtnCancel->setObjectName(QString::fromUtf8("BtnCancel"));

        horizontalLayout->addWidget(BtnCancel);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(DebugPassword);

        QMetaObject::connectSlotsByName(DebugPassword);
    } // setupUi

    void retranslateUi(QDialog *DebugPassword)
    {
        DebugPassword->setWindowTitle(QCoreApplication::translate("DebugPassword", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DebugPassword", "\345\257\206    \347\240\201\357\274\232", nullptr));
        BtnOK->setText(QCoreApplication::translate("DebugPassword", "\347\241\256\345\256\232", nullptr));
        BtnCancel->setText(QCoreApplication::translate("DebugPassword", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DebugPassword: public Ui_DebugPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGPASSWORD_H
