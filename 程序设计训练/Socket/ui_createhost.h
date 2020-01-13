/********************************************************************************
** Form generated from reading UI file 'createhost.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEHOST_H
#define UI_CREATEHOST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateHost
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *CreateHost)
    {
        if (CreateHost->objectName().isEmpty())
            CreateHost->setObjectName(QString::fromUtf8("CreateHost"));
        CreateHost->resize(382, 192);
        label = new QLabel(CreateHost);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 91, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        lineEdit = new QLineEdit(CreateHost);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(160, 50, 201, 31));
        pushButton = new QPushButton(CreateHost);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 140, 93, 28));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton->setFont(font1);
        pushButton_2 = new QPushButton(CreateHost);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 140, 93, 28));
        pushButton_2->setFont(font1);

        retranslateUi(CreateHost);

        QMetaObject::connectSlotsByName(CreateHost);
    } // setupUi

    void retranslateUi(QDialog *CreateHost)
    {
        CreateHost->setWindowTitle(QCoreApplication::translate("CreateHost", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CreateHost", "Host IP:", nullptr));
        pushButton->setText(QCoreApplication::translate("CreateHost", "OK", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CreateHost", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateHost: public Ui_CreateHost {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEHOST_H
