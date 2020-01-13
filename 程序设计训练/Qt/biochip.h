#ifndef BIOCHIP_H
#define BIOCHIP_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QObject>
#include <QSet>
#include <QHash>
#include <QMessageBox>
#include <QSound>
#include "order.h"
#include "drop.h"
#include "pollutionevent.h"
#include "washer.h"

namespace Ui {
class BioChip;
}


namespace MyColor {
const QColor ColorSet[] = {QColor(255,99,71),
                           QColor(127,255,0),
                           QColor(255,255,0),
                           QColor(218,112,214),
                           QColor(64,224,205),
                           QColor(255,0,0),
                           QColor(0,0,255),
                           QColor(160,32,240),
                           QColor(192,192,192)
                           };
}


class BioChip : public QWidget
{
    Q_OBJECT
private:
    QTimer *fTimer;//全局计时器

public:
    explicit BioChip(QWidget *parent = nullptr);
    ~BioChip();
    int width;
    int row,column;
    int output_x,output_y;
    QList<int> input;
    int begin_x,begin_y;
    int widget_size;
    Order order;            //存放命令
    bool matrixset;
    int totTime;
    int subtotTime;         //存储总时间副本
    int dropNum;            //液滴数量

    //设置行数
    void setRow(int r);
    //设置列数
    void setColumn(int c);
    //设置格子宽度
    void setWidth(int w);
    //设置入口和出口位置
    void setGate(QList<int> inp, int out_x, int out_y);
    //解析文件指令，初始化各参数矩阵
    void getOrder(Order& od);
    //获取当前时间
    int getCurTime()const;
    //将剩余时间流状态设置为相同
    void setLeftMatrix(int t,int x,int y,int value);
    //各个参数置零 或 回到默认状态
    void setZero();
    //音乐开启
    void setMusicOn(bool);
    //清洗模式开启
    void setCleanerOn(bool);
    //是否从输入口输入
    bool checkBesideInput(int x,int y);
    //是否从输出口输出
    bool checkBesideOutput(int x,int y);
    //静态约束,返回出错时间
    int checkNotStaticBeside();
    //动态约束，返回出错时间
    int checkNotDynamicBeside();
    //初始化污染情况矩阵
    void iniPollutionMatrix();
    //将剩余时间流状态设置为相同
    void setLeftTimeValue(int, int, int, int);

protected:
    //重写父类函数
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);

    //图形绘制 子函数
    void MatrixPaintEvent(QPainter *paint,int curTime);
    //画圆
    void EllispePaintEvent(QPainter *paint,int x,int y,int flag);
    //画中等液滴
    void pointPaintEvent(QPainter *paint,int x,int y);
    //合并后大液滴
    void LargePointPaintEvent(QPainter *paint,int x,int y);
    //分裂后小液滴
    void SmallPointPaintEvent(QPainter *paint,int x,int y);
    //绘制芯片表格
    void chipPaintEvent(QPainter *paint,int row,int column);
    //绘制出入口和清洗液滴出入口
    void gatePaintEvent(QPainter *paint);
    void IOputPaintEvent(QPainter* paint);
    //传入字符串，绘制出入口的文字
    void putPaintEvent(QPainter *paint,int x,int y,const QString &str);
    //绘制污染曲线
    void drawPollutionEvent(QPainter *paint,int curtime);
    //绘制污染次数
    void drawPollutionNumEvent(QPainter *paint);
    //在方格中画数字
    inline void numPaintEvent(QPainter *paint,int x,int y,int num);
    //绘制污染情况
    void barrierPaintEvent(QPainter* paint);
    //绘制清洗液滴
    void cleanerPaintEvent(QPainter* paint, int t);

public slots:
    void addcurTime();
    void reducecurTime();
    void resetTime();
    void startTimer();
    void endTimer();
    void updateChip();

signals:
    void ButtonUnable();
    void sendCurTime(int);
    void cleanerButtonOff();
    void pollutionExisted();
    void pollutionClear();
    void noPath();
    void findPath();

private:
    Ui::BioChip *ui;

    bool isSetted;
    bool errorSolved;
    bool errorHappened ;
    bool beforeError;
    bool pollutionError;
    bool paintPollution;
    bool music_on;
    bool cleaner_on;
    bool cleaner_doing;
    bool cleaner_done;
    bool play_forwoard;
    bool have_reached_final;

    //记录出错时间或清洗时间
    int errorInputTime;
    int errorOutputTime;
    int errorStaticTime;
    int errorDynamicTime;
    int errorPollutionTime;
    int stopTime;
    int freezeTime;
    int totcleantime;
    int curtime;

    //当前在场上的清洗液滴
    Washdrop curCleaner;

    //帧矩阵，维度信息：时间流,x,y
    int matrix[100][18][18] = {{{0}}};
    //记录污染情况,维度信息：液滴编号，x,y
    int pollutionMatrix[50][21][21] = {{{0}}};
    //记录液滴位置信息,维度信息为 液滴编号，时间，位置x = [0],y = [1],位置均初始化为20，表示未赋值. dropState[i][0][2]表示其第一次出现的时间
    int dropState[20][100][3] = {{{0}}};
    //记录每时刻障碍
    int barrierMatrix[100][18][18] = {{{0}}};
    //记录障碍位置
    QList<QPoint> barrierPos;
    //记录污染信息的四元数(x,y,t1,t2) / (x,y,第一个液滴经过时间，发生污染时间)
    QList<pollutionEvent> pollutionList;
    //第一维为污染事件索引，第二维是四元数的[t1,t2]
    int timeStartEnd[50][5];
    //在x,y上标记哪个液滴最后一次经过该点
    int whoPolluteMatrix[21][21] = {{0}};

    //存储相应矩阵的初始副本，便于reset
    int sub_dropState[20][100][3] = {{{0}}};
    int sub_matrix[100][18][18] = {{{0}}};
    int sub_barrierMatrix[100][18][18] = {{{0}}};
    int sub_timeStarEnd[50][5];

    //清洗液滴管理器，存放清洗液滴列表
    Washer washer;

    //当前路径
    QString rootPath;
    QString musicPath;

    //音乐播放
    QSound *merge_sound;
    QSound *background_sound;
    QSound *move_sound;
    QSound *split_finish_sound;
    QSound *split_strech_sound;

    //实时改变清洗液滴路径
    void changePath();
    //设置音乐路径
    void setSoundPath();

    //设置 帧矩阵
    void iniMatirx();
    //初始化每时刻障碍矩阵
    void iniBarrierMatrix();
    //初始化污染情况矩阵
    void iniPollutionList();

    //错误信息管理函数
    bool showErrorMessage();
    //显示输入不在输入端口的错误
    void showWorngInputMessage();
    //显示输出不在输出端口的错误
    void showWrongOutputMessage();
    //显示静态约束错误
    void showStaticErrorMessage();
    //显示动态约束错误
    void showDynamicErrorMessage();
    //显示发生污染错误
    void showPollutionErrorMessage();
    static bool compare(const pollutionEvent &p1, const pollutionEvent &p2);
    inline int max(int &a,int &b);

    //开始时保存副本，reset时重置初态
    void getSubMatrix();
    void getSubDropState();
    void getBarrierMatrix();
    void gettimeStartEnd();
    void resetMatrix();
    void resetDropState();
    void resetBarrierMatrix();
    void resettimeStartEnd();

    //将表格坐标转换为Qt绘图坐标
    int changetoQtCoordinate_x(int x);
    int changetoQtCoordinate_y(int y);


};
#endif // BIOCHIP_H
