/********************************************************************************
** Form generated from reading UI file 'promotion.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROMOTION_H
#define UI_PROMOTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Promotion
{
public:
    QLabel *label;
    QPushButton *buttonqueen;
    QPushButton *buttonrook;
    QPushButton *buttonbioshop;
    QPushButton *buttonknight;
    QPushButton *pushButton_5;

    void setupUi(QDialog *Promotion)
    {
        if (Promotion->objectName().isEmpty())
            Promotion->setObjectName(QString::fromUtf8("Promotion"));
        Promotion->resize(526, 227);
        label = new QLabel(Promotion);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 30, 291, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        buttonqueen = new QPushButton(Promotion);
        buttonqueen->setObjectName(QString::fromUtf8("buttonqueen"));
        buttonqueen->setGeometry(QRect(30, 100, 101, 51));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        buttonqueen->setFont(font1);
        buttonrook = new QPushButton(Promotion);
        buttonrook->setObjectName(QString::fromUtf8("buttonrook"));
        buttonrook->setGeometry(QRect(270, 100, 101, 51));
        buttonrook->setFont(font1);
        buttonbioshop = new QPushButton(Promotion);
        buttonbioshop->setObjectName(QString::fromUtf8("buttonbioshop"));
        buttonbioshop->setGeometry(QRect(150, 100, 101, 51));
        buttonbioshop->setFont(font1);
        buttonknight = new QPushButton(Promotion);
        buttonknight->setObjectName(QString::fromUtf8("buttonknight"));
        buttonknight->setGeometry(QRect(390, 100, 111, 51));
        buttonknight->setFont(font1);
        pushButton_5 = new QPushButton(Promotion);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(400, 180, 93, 28));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton_5->setFont(font2);

        retranslateUi(Promotion);

        QMetaObject::connectSlotsByName(Promotion);
    } // setupUi

    void retranslateUi(QDialog *Promotion)
    {
        Promotion->setWindowTitle(QCoreApplication::translate("Promotion", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Promotion", "Please Promote the Pawn!", nullptr));
        buttonqueen->setText(QCoreApplication::translate("Promotion", "Queen", nullptr));
        buttonrook->setText(QCoreApplication::translate("Promotion", "Rook", nullptr));
        buttonbioshop->setText(QCoreApplication::translate("Promotion", "Bioshop", nullptr));
        buttonknight->setText(QCoreApplication::translate("Promotion", "Knight", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Promotion", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Promotion: public Ui_Promotion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROMOTION_H
