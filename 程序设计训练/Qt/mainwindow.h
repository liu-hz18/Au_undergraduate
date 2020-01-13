#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "biochip.h"
#include "order.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int row;
    int column;
    QList<int> input;
    int output_x,output_y;
    Order order;
    inline bool isSet(int a)const;
    void setSound();
    inline int max(int& a,int& b);

private slots:
    void on_actionSetTable_triggered();
    void on_actionAbout_triggered();
    void on_actionHelp_H_triggered();
    void on_actionSet_Row_and_Column_triggered();
    void on_actionMusic_on_toggled(bool arg1);
    void on_actionOpen_File_2_triggered();
    void on_actionOpen_File_triggered();
    void on_pushButton_clicked();
    void on_actionNext_Frame_triggered();
    void on_actionLast_Frame_triggered();
    void on_actionReset_2_triggered();
    void on_actionStart_2_toggled(bool arg1);
    void on_actionStart_toggled(bool arg1);
    void on_actionStop_triggered();
    void on_actionLast_Step_triggered();
    void on_actionNext_Step_triggered();
    void on_actionReset_triggered();
    void on_actionPlay_triggered();
    void on_actionCleanable_toggled(bool arg1);

    void receiveRow(int);
    void receiveColumn(int);
    void receiveInput(QList<int>);
    void receiveOutput_x(int);
    void receiveOutput_y(int);

    //绘制初始界面
    bool allValueisSet();
    void drawChip();

signals:
    void setAllValue();

private:
    Ui::MainWindow *ui;
    QString rootPath;
    QString filePath;
    BioChip *biochip;

};

#endif   // MAINWINDOW_H
