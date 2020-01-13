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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionLast_Step;
    QAction *actionNext_Step;
    QAction *actionReset;
    QAction *actionPlay;
    QAction *actionOpen_File;
    QAction *actionStart_2;
    QAction *actionReset_2;
    QAction *actionCleanable;
    QAction *actionNext_Frame;
    QAction *actionLast_Frame;
    QAction *actionMusic_on;
    QAction *actionOpen_File_2;
    QAction *actionSetTable;
    QAction *actionSet_Row_and_Column;
    QAction *actionHelp_H;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QMenu *menuOptions;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(750, 602);
        MainWindow->setStyleSheet(QString::fromUtf8("#centralWidget{\n"
"border-image: url(:/image/C:/Users/lenovo/Desktop/icons/background.jpg);\n"
"}\n"
"#MainWindow{\n"
"background-color: qradialgradient(spread:reflect, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 106, 145, 214), stop:1 rgba(255, 255, 255, 255));\n"
"}"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionLast_Step = new QAction(MainWindow);
        actionLast_Step->setObjectName(QString::fromUtf8("actionLast_Step"));
        actionNext_Step = new QAction(MainWindow);
        actionNext_Step->setObjectName(QString::fromUtf8("actionNext_Step"));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        actionPlay = new QAction(MainWindow);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName(QString::fromUtf8("actionOpen_File"));
        actionStart_2 = new QAction(MainWindow);
        actionStart_2->setObjectName(QString::fromUtf8("actionStart_2"));
        actionStart_2->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/icons/begin.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart_2->setIcon(icon);
        actionReset_2 = new QAction(MainWindow);
        actionReset_2->setObjectName(QString::fromUtf8("actionReset_2"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/icons/reset_1.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionReset_2->setIcon(icon1);
        actionCleanable = new QAction(MainWindow);
        actionCleanable->setObjectName(QString::fromUtf8("actionCleanable"));
        actionCleanable->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/icons/broom_on.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCleanable->setIcon(icon2);
        actionNext_Frame = new QAction(MainWindow);
        actionNext_Frame->setObjectName(QString::fromUtf8("actionNext_Frame"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/icons/next.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionNext_Frame->setIcon(icon3);
        actionLast_Frame = new QAction(MainWindow);
        actionLast_Frame->setObjectName(QString::fromUtf8("actionLast_Frame"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/icons/back_1.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionLast_Frame->setIcon(icon4);
        actionMusic_on = new QAction(MainWindow);
        actionMusic_on->setObjectName(QString::fromUtf8("actionMusic_on"));
        actionMusic_on->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/icons/Music-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMusic_on->setIcon(icon5);
        actionOpen_File_2 = new QAction(MainWindow);
        actionOpen_File_2->setObjectName(QString::fromUtf8("actionOpen_File_2"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/image/icons/openfile.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_File_2->setIcon(icon6);
        actionSetTable = new QAction(MainWindow);
        actionSetTable->setObjectName(QString::fromUtf8("actionSetTable"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/image/icons/settable.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetTable->setIcon(icon7);
        actionSet_Row_and_Column = new QAction(MainWindow);
        actionSet_Row_and_Column->setObjectName(QString::fromUtf8("actionSet_Row_and_Column"));
        actionHelp_H = new QAction(MainWindow);
        actionHelp_H->setObjectName(QString::fromUtf8("actionHelp_H"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("#centralWidget{\n"
"border-image: url(:/image/icons/background.jpg);\n"
"}\n"
""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("#groupBox{\n"
"color: rgb(255, 255, 255);\n"
"}"));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 450, 731, 42));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label);

        lcdNumber = new QLCDNumber(layoutWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(120, 40));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        lcdNumber->setFont(font2);
        lcdNumber->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(lcdNumber);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(0, 410, 181, 31));

        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 750, 26));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuOptions->addAction(actionSet_Row_and_Column);
        menuOptions->addAction(actionStart);
        menuOptions->addAction(actionStop);
        menuOptions->addAction(actionLast_Step);
        menuOptions->addAction(actionNext_Step);
        menuOptions->addAction(actionReset);
        menuOptions->addAction(actionPlay);
        menuOptions->addAction(actionOpen_File);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionHelp_H);
        mainToolBar->addAction(actionSetTable);
        mainToolBar->addAction(actionStart_2);
        mainToolBar->addAction(actionLast_Frame);
        mainToolBar->addAction(actionNext_Frame);
        mainToolBar->addAction(actionReset_2);
        mainToolBar->addAction(actionCleanable);
        mainToolBar->addAction(actionMusic_on);
        mainToolBar->addAction(actionOpen_File_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About(&A)", nullptr));
        actionStart->setText(QCoreApplication::translate("MainWindow", "Start(&S)", nullptr));
        actionStop->setText(QCoreApplication::translate("MainWindow", "Stop(&E)", nullptr));
        actionLast_Step->setText(QCoreApplication::translate("MainWindow", "Last Step(L)", nullptr));
        actionNext_Step->setText(QCoreApplication::translate("MainWindow", "Next Step(N)", nullptr));
        actionReset->setText(QCoreApplication::translate("MainWindow", "Reset(R)", nullptr));
        actionPlay->setText(QCoreApplication::translate("MainWindow", "Play Video(P)", nullptr));
        actionOpen_File->setText(QCoreApplication::translate("MainWindow", "Load File(L)", nullptr));
        actionStart_2->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
#if QT_CONFIG(tooltip)
        actionStart_2->setToolTip(QCoreApplication::translate("MainWindow", "Start the process", nullptr));
#endif // QT_CONFIG(tooltip)
        actionReset_2->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        actionReset_2->setToolTip(QCoreApplication::translate("MainWindow", "Reset the Process", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCleanable->setText(QCoreApplication::translate("MainWindow", "Cleanable", nullptr));
#if QT_CONFIG(tooltip)
        actionCleanable->setToolTip(QCoreApplication::translate("MainWindow", "The DMFB can be cleaned.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionNext_Frame->setText(QCoreApplication::translate("MainWindow", "Next Frame", nullptr));
#if QT_CONFIG(tooltip)
        actionNext_Frame->setToolTip(QCoreApplication::translate("MainWindow", "Show Next Frame", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLast_Frame->setText(QCoreApplication::translate("MainWindow", "Last_Frame", nullptr));
#if QT_CONFIG(tooltip)
        actionLast_Frame->setToolTip(QCoreApplication::translate("MainWindow", "Show the last frame.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMusic_on->setText(QCoreApplication::translate("MainWindow", "Music_on", nullptr));
#if QT_CONFIG(tooltip)
        actionMusic_on->setToolTip(QCoreApplication::translate("MainWindow", "Turn on the music.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpen_File_2->setText(QCoreApplication::translate("MainWindow", "Load_File", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen_File_2->setToolTip(QCoreApplication::translate("MainWindow", "Open and read the input file.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSetTable->setText(QCoreApplication::translate("MainWindow", "SetTable", nullptr));
#if QT_CONFIG(tooltip)
        actionSetTable->setToolTip(QCoreApplication::translate("MainWindow", "Set the row and column of table", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSet_Row_and_Column->setText(QCoreApplication::translate("MainWindow", "Set Row and Column(&M)", nullptr));
        actionHelp_H->setText(QCoreApplication::translate("MainWindow", "Help(&H)", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "BioChip", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Time:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Exit(&E)", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "Options(&O)", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help(&B)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
