#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QFileDialog>
#include <QPainter>
#include <QBrush>
#include <QPixmap>
#include <QTimer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include "createhost.h"
#include "createlink.h"
#include "promotion.h"

//未做任务：

//胜负判断
//将军判断
//王车易位 测试一下？？
//逼和，弹窗显示两侧和棋（不送吃）
//容错机制，比如未连接之前不可以开始游戏。一方断开连接时，输出提示信息。


//棋子身份
namespace Pieces {
    const int black_bishop = -6;
    const int black_king = -5;
    const int black_knight = -4;
    const int black_pawn = -3;
    const int black_queen = -2;
    const int black_rook = -1;
    const int none = 0;
    const int white_bishop = 1;
    const int white_king = 2;
    const int white_knight = 3;
    const int white_pawn = 4;
    const int white_queen = 5;
    const int white_rook = 6;
}

namespace Color {
    const QColor darkGreen(0, 139, 69);
    const QColor lightGreen(255, 248, 220);
    const QColor hint(190,190,190,2);
}

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void setFloatBased(bool);

    //绘制棋盘
    void paintBoard(QPainter *paint);
    //绘制棋子
    void paintPieces(QPainter *paint);
    //绘制可走点
    void paintRoad(QPainter *paint);
    //绘制危险点
    void paintDanger(QPainter *paint);
    //绘制正在移动的棋子
    void paintMovePiece(QPainter *paint);
    //不同角色判断是否可走
    void paintBioshopCanWalk(QPainter* paint);
    void paintKingCanWalk(QPainter* paint);
    void paintKnightCanWalk(QPainter* paint);
    void paintPawnCanWalk(QPainter* paint);
    void paintQueenCanWalk(QPainter* paint);
    void paintRookCanWalk(QPainter* paint);
    void paintCanWalkPoint(QPainter* paint,int x, int y);

private slots:
    void receiveIP(QString);//接受子窗口发来的IP
    void receiveMessage();//主机接受信息
    void acceptConnection();
    void clientReceiveMessage();//客户端接受信息
    void iniServer();
    void delServer();
    void missLinkMessage();//连接失败
    void linkSuccess();//连接成功

    void overtimeMessage();//超时
    void pawnPromotion(int);
    void addWaittime();

    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_7_clicked();
    void on_actionCreate_Host_triggered();
    void on_actionCreate_Link_triggered();
    void on_actionLoad_File_triggered();
    void on_actionSave_File_triggered();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

signals:
    void waittimeout();

private:
    Ui::MainWindow *ui;

    CreateHost *createhost;
    CreateLink *createLink;
    Promotion *promotion;
    QTcpServer *listenSocket;
    QTcpSocket *serverreadWriteSocket;
    QTcpSocket *clientreadWriteSocket;
    bool haveConnected;

    QString hostIP;//当前主机IP
    QString inputIP;//连接端输入的IP

    QPixmap black_bishop;
    QPixmap black_king;
    QPixmap black_knight;
    QPixmap black_pawn;
    QPixmap black_queen;
    QPixmap black_rook;

    QPixmap white_bishop;
    QPixmap white_king;
    QPixmap white_knight;
    QPixmap white_pawn;
    QPixmap white_queen;
    QPixmap white_rook;

    int width = 80;

    //绘图起始坐标
    int begin_x = 210,
        begin_y = 100;

    //坐标转换
    int cadinate_jtox(int x);
    int cadinate_itoy(int y);

    int matrix[10][10];
    int dangerMatrix[10][10] = {{0}};
    int Walkable[10][10] = {{0}};//当前一步可以走到的点
    int tempMatrix[10][10] = {{0}};//保存当前局面的副本
    int attackMatrix[10][10] = {{0}};//敌方攻击范围，根据tempMatrix刷新
    int king_x,king_y;


    QPoint curPos;//当前鼠标位置
    int curMovePieceIndex;//当前移动棋子的索引
    int last_x,last_y;//移动的棋子原来的位置
    int cur_x,cur_y;//当前一局鼠标释放的位置
    bool isMoving;//当前是否在移动棋子
    bool foul;//该步是否犯规
    bool isOnCharge;//到本方行棋
    bool inGame;//在游戏中

    //表示当前玩家状态，0为白方，1为黑方，2为观战
    int state;

    //发出和接受到的消息，解析格式"%d.%d.%d.%d.%d",表示某一方的棋子从 某点 移动到 某点 ，白方为0，黑方为1
    QString order_send;
    QString order_receive;

    QTimer *timer;
    int waittime = 0;
    QTimer *linkTimer;

    //通信相关函数
    void connectHost();


    //初始化矩阵
    void inimatrix();
    //构建危险点矩阵
    void setDangerMatrix();
    //根据消息更改矩阵
    void changeMatrix(const QString& change);
    //设置玩家状态
    void setState(int);
    //加载图片
    void loadImage();
    //当前点是否可走
    bool canWalk(int x,int y);
    //每次走一步就更新一次危险点
    void resetDanger();
    //每走一步更新一次可走点，用于判断犯规
    void resetWalkable();
    //判断某点是否在敌方攻击范围内
    bool pointInDanger(int x,int y);
    //保存matrix副本
    void setTempMatrix();
    //记录敌方攻击范围，根据tempMatrix刷新
    void setAttackMatrix();
    //判断逼和
    bool stalemate();

    //对话框显示输赢
    void winMessage();//赢
    void loseMessage();//输
    void drawnMessage();//逼和
    void giveUpMessage();//确认是否认输
    void anotherGiveUpMessage();//对方认输

    //读入，保存残局
    void openFile();
    bool readFile(const QString& fileName);
    void saveFile();
    bool writeFile(const QString& fileName);
    QString numtoLetter(const int& num);
    int lettertoNum(const QString& str);
    bool haveRead;

};

#endif // MAINWINDOW_H
