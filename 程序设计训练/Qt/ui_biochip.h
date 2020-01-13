/********************************************************************************
** Form generated from reading UI file 'biochip.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIOCHIP_H
#define UI_BIOCHIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BioChip
{
public:

    void setupUi(QWidget *BioChip)
    {
        if (BioChip->objectName().isEmpty())
            BioChip->setObjectName(QString::fromUtf8("BioChip"));
        BioChip->resize(701, 452);
        BioChip->setMaximumSize(QSize(1000000, 1000000));

        retranslateUi(BioChip);

        QMetaObject::connectSlotsByName(BioChip);
    } // setupUi

    void retranslateUi(QWidget *BioChip)
    {
        BioChip->setWindowTitle(QCoreApplication::translate("BioChip", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BioChip: public Ui_BioChip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIOCHIP_H
