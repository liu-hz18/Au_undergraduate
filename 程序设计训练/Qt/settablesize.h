#ifndef SETTABLESIZE_H
#define SETTABLESIZE_H

#include <QWidget>
#include <QMouseEvent>
#include <QString>
#include <string.h>
#include "mainwindow.h"

namespace Ui {
class SetTableSize;
}

class SetTableSize : public QWidget
{
    Q_OBJECT
private:
    bool m_moving = false;//窗口拖动状态
    QPoint m_lastPos;//窗口上次位置

protected:
    //使得子窗口可以跟随鼠标移动
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    explicit SetTableSize(QWidget *parent = nullptr);
    ~SetTableSize();
    bool isOnMargin(int x,int y);
    int row,column;
    QList<int> input_list;
    int output_x,output_y;

signals:
    void sendRow(int);
    void sendColumn(int);
    void sendInput(QList<int>);
    void sendOutput_x(int);
    void sendOutput_y(int);

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::SetTableSize *ui;
};

#endif // SETTABLESIZE_H
