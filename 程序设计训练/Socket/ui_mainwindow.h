/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCreate_Host;
    QAction *actionCreate_Link;
    QAction *actionLoad_File;
    QAction *actionSave_File;
    QWidget *centralWidget;
    QFrame *line;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLCDNumber *lcdNumber;
    QLabel *label_2;
    QLabel *HintLabel;
    QMenuBar *menuBar;
    QMenu *menuOption;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 800);
        MainWindow->setMinimumSize(QSize(900, 800));
        MainWindow->setMaximumSize(QSize(1000, 900));
        actionCreate_Host = new QAction(MainWindow);
        actionCreate_Host->setObjectName(QString::fromUtf8("actionCreate_Host"));
        actionCreate_Link = new QAction(MainWindow);
        actionCreate_Link->setObjectName(QString::fromUtf8("actionCreate_Link"));
        actionLoad_File = new QAction(MainWindow);
        actionLoad_File->setObjectName(QString::fromUtf8("actionLoad_File"));
        actionSave_File = new QAction(MainWindow);
        actionSave_File->setObjectName(QString::fromUtf8("actionSave_File"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(150, 30, 20, 701));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 80, 102, 501));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font);

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setFont(font);

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setFont(font);

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setFont(font);

        verticalLayout->addWidget(pushButton_5);

        pushButton_7 = new QPushButton(layoutWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setFont(font);

        verticalLayout->addWidget(pushButton_7);

        pushButton_6 = new QPushButton(layoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setFont(font);

        verticalLayout->addWidget(pushButton_6);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        verticalLayout->addWidget(label_3);

        lcdNumber = new QLCDNumber(layoutWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        lcdNumber->setFont(font2);
        lcdNumber->setStyleSheet(QString::fromUtf8("color: rgb(255, 97, 44);"));

        verticalLayout->addWidget(lcdNumber);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        HintLabel = new QLabel(layoutWidget);
        HintLabel->setObjectName(QString::fromUtf8("HintLabel"));

        verticalLayout->addWidget(HintLabel);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 26));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QString::fromUtf8("menuOption"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOption->menuAction());
        menuOption->addAction(actionCreate_Host);
        menuOption->addAction(actionCreate_Link);
        menuOption->addSeparator();
        menuOption->addAction(actionLoad_File);
        menuOption->addAction(actionSave_File);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionCreate_Host->setText(QCoreApplication::translate("MainWindow", "Create Host", nullptr));
#if QT_CONFIG(shortcut)
        actionCreate_Host->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCreate_Link->setText(QCoreApplication::translate("MainWindow", "Create Link", nullptr));
#if QT_CONFIG(shortcut)
        actionCreate_Link->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoad_File->setText(QCoreApplication::translate("MainWindow", "Load File", nullptr));
#if QT_CONFIG(shortcut)
        actionLoad_File->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_File->setText(QCoreApplication::translate("MainWindow", "Save File", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_File->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\344\270\273\346\234\272(&H)", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\350\277\236\346\216\245(&L)", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\350\275\275\345\205\245\346\256\213\345\261\200(R)", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\256\213\345\261\200(&S)", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217(&B)", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\346\226\260\347\232\204\344\270\200\345\261\200(&N)", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\350\256\244\350\276\223(&F)", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\350\265\260\346\243\213\346\226\271:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\211\251\344\275\231\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\217\220\347\244\272\344\277\241\346\201\257\357\274\232", nullptr));
        HintLabel->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        menuOption->setTitle(QCoreApplication::translate("MainWindow", "Option", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
