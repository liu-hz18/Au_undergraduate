/********************************************************************************
** Form generated from reading UI file 'createlink.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATELINK_H
#define UI_CREATELINK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateLink
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_0;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_point;
    QPushButton *pushButton;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;

    void setupUi(QDialog *CreateLink)
    {
        if (CreateLink->objectName().isEmpty())
            CreateLink->setObjectName(QString::fromUtf8("CreateLink"));
        CreateLink->resize(408, 280);
        label = new QLabel(CreateLink);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 70, 101, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        lineEdit = new QLineEdit(CreateLink);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(190, 70, 191, 31));
        pushButton_0 = new QPushButton(CreateLink);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setGeometry(QRect(70, 130, 31, 28));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_0->setFont(font1);
        pushButton_1 = new QPushButton(CreateLink);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setGeometry(QRect(120, 130, 31, 28));
        pushButton_1->setFont(font1);
        pushButton_2 = new QPushButton(CreateLink);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(170, 130, 31, 28));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(CreateLink);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(220, 130, 31, 28));
        pushButton_3->setFont(font1);
        pushButton_4 = new QPushButton(CreateLink);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(270, 130, 31, 28));
        pushButton_4->setFont(font1);
        pushButton_5 = new QPushButton(CreateLink);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(70, 170, 31, 28));
        pushButton_5->setFont(font1);
        pushButton_6 = new QPushButton(CreateLink);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(120, 170, 31, 28));
        pushButton_6->setFont(font1);
        pushButton_7 = new QPushButton(CreateLink);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(170, 170, 31, 28));
        pushButton_7->setFont(font1);
        pushButton_8 = new QPushButton(CreateLink);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(220, 170, 31, 28));
        pushButton_8->setFont(font1);
        pushButton_9 = new QPushButton(CreateLink);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(270, 170, 31, 28));
        pushButton_9->setFont(font1);
        pushButton_point = new QPushButton(CreateLink);
        pushButton_point->setObjectName(QString::fromUtf8("pushButton_point"));
        pushButton_point->setGeometry(QRect(320, 170, 31, 28));
        pushButton_point->setFont(font1);
        pushButton = new QPushButton(CreateLink);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(70, 220, 93, 28));
        pushButton->setFont(font1);
        pushButton_10 = new QPushButton(CreateLink);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(230, 220, 93, 28));
        pushButton_10->setFont(font1);
        pushButton_11 = new QPushButton(CreateLink);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(320, 130, 31, 28));
        pushButton_11->setFont(font1);

        retranslateUi(CreateLink);

        QMetaObject::connectSlotsByName(CreateLink);
    } // setupUi

    void retranslateUi(QDialog *CreateLink)
    {
        CreateLink->setWindowTitle(QCoreApplication::translate("CreateLink", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CreateLink", "Enter IP:", nullptr));
        pushButton_0->setText(QCoreApplication::translate("CreateLink", "0", nullptr));
        pushButton_1->setText(QCoreApplication::translate("CreateLink", "1", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CreateLink", "2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CreateLink", "3", nullptr));
        pushButton_4->setText(QCoreApplication::translate("CreateLink", "4", nullptr));
        pushButton_5->setText(QCoreApplication::translate("CreateLink", "5", nullptr));
        pushButton_6->setText(QCoreApplication::translate("CreateLink", "6", nullptr));
        pushButton_7->setText(QCoreApplication::translate("CreateLink", "7", nullptr));
        pushButton_8->setText(QCoreApplication::translate("CreateLink", "8", nullptr));
        pushButton_9->setText(QCoreApplication::translate("CreateLink", "9", nullptr));
        pushButton_point->setText(QCoreApplication::translate("CreateLink", ".", nullptr));
        pushButton->setText(QCoreApplication::translate("CreateLink", "OK", nullptr));
        pushButton_10->setText(QCoreApplication::translate("CreateLink", "Cancle", nullptr));
        pushButton_11->setText(QCoreApplication::translate("CreateLink", "<-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateLink: public Ui_CreateLink {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATELINK_H
