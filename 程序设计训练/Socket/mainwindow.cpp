#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadImage();

    createLink = new CreateLink(this);
    createhost = new CreateHost(this);
    promotion = new Promotion(this);
    this->listenSocket =new QTcpServer;

    ui->lcdNumber->setSegmentStyle(QLCDNumber::Filled);

    this->state = 0;//默认为白方
    king_x = 1;king_y = 5;
    isMoving = false;
    foul = false;
    haveConnected = false;
    isOnCharge = false;
    inGame = false;
    haveRead = false;
    timer = new QTimer(this);
    linkTimer = new QTimer(this);
    linkTimer->setInterval(3000);
    linkTimer->stop();
    timer->setInterval(1000);
    timer->stop();

    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);

    connect(timer,SIGNAL(timeout()),this,SLOT(addWaittime()));
    connect(createLink,SIGNAL(sendIP(QString)),this,SLOT(receiveIP(QString)));
    connect(createhost,SIGNAL(startConnect()),this,SLOT(iniServer()));
    connect(createhost,SIGNAL(endConnect()),this,SLOT(delServer()));
    connect(this,SIGNAL(waittimeout()),this,SLOT(overtimeMessage()));
    connect(promotion,SIGNAL(promotionNumSet(int)),this,SLOT(pawnPromotion(int)));

    inimatrix();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter *paint = new QPainter(this);
    paintBoard(paint);
    paintDanger(paint);
    paintPieces(paint);
    if(isMoving){
        paintMovePiece(paint);
        paintRoad(paint);
    }
    paint->end();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mouse pressed.";
    resetWalkable();
    if(event->button() == Qt::LeftButton && isOnCharge && inGame){
        this->curPos = QMainWindow::mapFromGlobal(QCursor::pos());
        if(state == 0){
            int posx = 8 - (curPos.y() - begin_y) / width,posy = (curPos.x() - begin_x) / width + 1;
            qDebug()<<posx<<posy;
            if(posx < 1 || posx > 8 || posy < 1 || posy > 8)return;
            last_x = posx;
            last_y = posy;
            int p = matrix[posx][posy];
            if(p > 0){
                this->curMovePieceIndex = matrix[posx][posy];
                matrix[posx][posy] = Pieces::none;
                isMoving = true;
            }
        }else if(state == 1){
            int posx = 1 + (curPos.y() - begin_y) / width,posy = 8 - (curPos.x() - begin_x) / width;
            qDebug()<<posx<<posy;
            if(posx < 1 || posx > 8 || posy < 1 || posy > 8)return;
            last_x = posx;
            last_y = posy;
            int p = matrix[posx][posy];  
            if(p < 0){
                this->curMovePieceIndex = matrix[posx][posy];
                matrix[posx][posy] = Pieces::none;
                isMoving = true;
            }
        }
    }
    this->repaint();
    return QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    this->curPos = QMainWindow::mapFromGlobal(QCursor::pos());
    if(isMoving){
        if(state == 0){
            int posx = 8 - (curPos.y() - begin_y) / width,posy = (curPos.x() - begin_x) / width + 1;
            if(posx < 1 || posx > 8 || posy < 1 || posy > 8)return;
            if(Walkable[posx][posy] == 0)matrix[last_x][last_y] = this->curMovePieceIndex;
            else {
                QString tempSignal;
                if(curMovePieceIndex == Pieces::white_pawn && cur_x == 8){}
                else tempSignal = QString::number(curMovePieceIndex) + "." + QString::number(last_x) + "." + QString::number(last_y) + "." + QString::number(posx) + "." + QString::number(posy);
                ui->lineEdit->setText("BLACK");
                isOnCharge = false;
                if(curMovePieceIndex == Pieces::white_king){king_x = posx;king_y = posy;}
                if(matrix[posx][posy] == Pieces::black_king)winMessage();
                if(curMovePieceIndex == Pieces::white_king && abs(posy - last_y) == 2){
                    if(posy - last_y > 0){
                        matrix[posx][posy - 1] = Pieces::white_rook;
                        matrix[1][8] = Pieces::none;
                        tempSignal += "." + QString::number(Pieces::white_rook) + "." + QString::number(1) + "." + QString::number(8) + "." + QString::number(posx) + "." + QString::number(posy - 1);
                    }else {
                        matrix[1][1] = Pieces::none;
                        matrix[posx][posy + 1] = Pieces::white_rook;
                        tempSignal += "." + QString::number(Pieces::white_rook) + "." + QString::number(1) + "." + QString::number(1) + "." + QString::number(posx) + "." + QString::number(posy + 1);
                    }
                }
                QByteArray temparray = tempSignal.toUtf8();
                if(haveConnected)this->serverreadWriteSocket->write(temparray.data());
                matrix[posx][posy] = this->curMovePieceIndex;
                cur_x = posx;cur_y = posy;
                if(curMovePieceIndex == Pieces::white_pawn && state == 0 && cur_x == 8){
                    this->promotion->show();
                }
                waittime = 0;
            }
        }else if(state == 1){
            int posx = 1 + (curPos.y() - begin_y) / width,posy = 8 - (curPos.x() - begin_x) / width;
            if(posx < 1 || posx > 8 || posy < 1 || posy > 8)return;
            if(Walkable[posx][posy] == 0)matrix[last_x][last_y] = this->curMovePieceIndex;
            else {
                QString tempSignal;
                if(curMovePieceIndex == Pieces::black_pawn && cur_x == 1){}
                else tempSignal = QString::number(curMovePieceIndex) + "." + QString::number(last_x) + "." + QString::number(last_y) + "." + QString::number(posx) + "." + QString::number(posy);
                ui->lineEdit->setText("WHITE");
                isOnCharge = false;
                if(matrix[posx][posy] == Pieces::white_king)winMessage();
                if(curMovePieceIndex == Pieces::black_king){king_x = posx;king_y = posy;}
                if(curMovePieceIndex == Pieces::black_king && abs(posy - last_y) == 2){
                    if(posy - last_y > 0){
                        matrix[posx][posy - 1] = Pieces::black_rook;
                        matrix[8][8] = Pieces::none;
                        tempSignal += "." + QString::number(Pieces::black_rook) + "." + QString::number(8) + "." + QString::number(8) + "." + QString::number(posx) + "." + QString::number(posy - 1);
                    }else {
                        matrix[posx][posy + 1] = Pieces::black_rook;
                        matrix[8][1] = Pieces::none;
                        tempSignal += "." + QString::number(Pieces::black_rook) + "." + QString::number(8) + "." + QString::number(1) + "." + QString::number(posx) + "." + QString::number(posy + 1);
                    }
                }
                QByteArray temparray = tempSignal.toUtf8();
                if(haveConnected)this->clientreadWriteSocket->write(temparray.data());
                matrix[posx][posy] = this->curMovePieceIndex;
                cur_x = posx;cur_y = posy;
                if(curMovePieceIndex == Pieces::black_pawn && state == 1 && cur_x == 1){
                    this->promotion->show();
                }
                waittime = 0;
            }
        }
    }
    setTempMatrix();
    this->isMoving = false;

    this->repaint();
    return QMainWindow::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<isMoving;
    this->curPos = QMainWindow::mapFromGlobal(QCursor::pos());
    if(isMoving && (event->buttons() == Qt::LeftButton)){
        qDebug()<<"moving";
        this->repaint();
    }
    return QMainWindow::mouseMoveEvent(event);
}

void MainWindow::paintBoard(QPainter *paint)
{
    paint->setRenderHint(QPainter::Antialiasing);
    paint->setBrush(QBrush(Color::lightGreen,Qt::SolidPattern));
    paint->drawRect(begin_x, begin_y, width * 8, width * 8);

    paint->setBrush(QBrush(Color::darkGreen,Qt::SolidPattern));
    for(int i = 1;i <= 8 ;i++){
        if(i%2 == 1){
            for(int j = 2;j <= 8;j += 2){
                paint->drawRect(begin_x + (i-1) *width,begin_y + (j - 1) * width , width, width);
            }
        }else{
            for(int j = 1;j < 8;j += 2){
                paint->drawRect(begin_x + (i-1) *width, begin_y + (j - 1) * width, width, width);
            }
        }
    }
}

//绘图时根据主观视野进行中心对称，显示到 己方 视野
void MainWindow::paintPieces(QPainter *paint)
{
    QDebug  out  = qDebug();
    paint->setRenderHints(QPainter::SmoothPixmapTransform);

    if(state == 0 || state == 2){
        for(int i = 1;i <= 8;i ++){
            for(int j = 1;j <= 8;j ++){
                if(matrix[i][j] == Pieces::white_king){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->white_king);
                }else if(matrix[i][j] == Pieces::white_pawn){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->white_pawn);
                }else if(matrix[i][j] == Pieces::white_rook){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->white_rook);
                }else if(matrix[i][j] == Pieces::white_queen){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->white_queen);
                }else if(matrix[i][j] == Pieces::white_bishop){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->white_bishop);
                }else if(matrix[i][j] == Pieces::white_knight){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->white_knight);
                }else if(matrix[i][j] == Pieces::black_king){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->black_king);
                }else if(matrix[i][j] == Pieces::black_pawn){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->black_pawn);
                }else if(matrix[i][j] == Pieces::black_rook){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->black_rook);
                }else if(matrix[i][j] == Pieces::black_queen){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->black_queen);
                }else if(matrix[i][j] == Pieces::black_bishop){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->black_bishop);
                }else if(matrix[i][j] == Pieces::black_knight){
                    paint->drawPixmap(cadinate_jtox(j),cadinate_itoy(i),width,width,this->black_knight);
                }
            }
        }
    }else if(state == 1){
        for(int i = 1;i <= 8;i ++){
            for(int j = 1;j <= 8;j ++){
                if(matrix[i][j] == Pieces::white_king){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->white_king);
                }else if(matrix[i][j] == Pieces::white_pawn){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->white_pawn);
                }else if(matrix[i][j] == Pieces::white_rook){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->white_rook);
                }else if(matrix[i][j] == Pieces::white_queen){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->white_queen);
                }else if(matrix[i][j] == Pieces::white_bishop){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->white_bishop);
                }else if(matrix[i][j] == Pieces::white_knight){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->white_knight);
                }else if(matrix[i][j] == Pieces::black_king){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->black_king);
                }else if(matrix[i][j] == Pieces::black_pawn){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->black_pawn);
                }else if(matrix[i][j] == Pieces::black_rook){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->black_rook);
                }else if(matrix[i][j] == Pieces::black_queen){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->black_queen);
                }else if(matrix[i][j] == Pieces::black_bishop){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->black_bishop);
                }else if(matrix[i][j] == Pieces::black_knight){
                    paint->drawPixmap(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width,this->black_knight);
                }
            }
        }
    }
}

//绘制可行路径
void MainWindow::paintRoad(QPainter *paint)
{
    paint->setBrush(QBrush(Color::hint,Qt::SolidPattern));
    if(isMoving){
        if(curMovePieceIndex == Pieces::white_king || curMovePieceIndex == Pieces::black_king){   
            paintKingCanWalk(paint);
        }else if(curMovePieceIndex == Pieces::white_pawn || curMovePieceIndex == Pieces::black_pawn){
            paintPawnCanWalk(paint);
        }else if(curMovePieceIndex == Pieces::white_rook || curMovePieceIndex == Pieces::black_rook){
            paintRookCanWalk(paint);
        }else if(curMovePieceIndex == Pieces::white_queen || curMovePieceIndex == Pieces::black_queen){
            paintQueenCanWalk(paint);
        }else if(curMovePieceIndex == Pieces::white_bishop || curMovePieceIndex == Pieces::black_bishop){
            paintBioshopCanWalk(paint);
        }else if(curMovePieceIndex == Pieces::white_knight || curMovePieceIndex == Pieces::black_knight){
            paintKnightCanWalk(paint);
        }
    }
}

void MainWindow::paintDanger(QPainter *paint)
{
    paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    setDangerMatrix();
    for(int i = 1;i <= 8;i ++){
        for(int j = 1;j <= 8;j ++){
            if(dangerMatrix[i][j] == 1){
                if(state == 1)paint->drawRect(cadinate_jtox(9 - j),cadinate_itoy(9 - i),width,width);
                if(state == 0)paint->drawRect(cadinate_jtox(j),cadinate_itoy(i),width,width);
            }
        }
    }
}

void MainWindow::paintMovePiece(QPainter *paint)
{
    if(isMoving){
        if(state == 0){
            switch (this->curMovePieceIndex) {
            case Pieces::white_king:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->white_king);
                break;
            case Pieces::white_pawn:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->white_pawn);
                break;
            case Pieces::white_rook:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->white_rook);
                break;
            case Pieces::white_queen:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->white_queen);
                break;
            case Pieces::white_bishop:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->white_bishop);
                break;
            case Pieces::white_knight:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->white_knight);
                break;
            default:
                break;
            }
        }else if(state == 1){
            switch (this->curMovePieceIndex) {
            case Pieces::black_king:
                paint->drawPixmap(curPos.x() - width / 2,curPos.y()- width / 2,width,width,this->black_king);
                break;
            case Pieces::black_pawn:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->black_pawn);
                break;
            case Pieces::black_rook:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->black_rook);
                break;
            case Pieces::black_queen:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->black_queen);
                break;
            case Pieces::black_bishop:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->black_bishop);
                break;
            case Pieces::black_knight:
                paint->drawPixmap(curPos.x()- width / 2,curPos.y()- width / 2,width,width,this->black_knight);
                break;
            default:
                break;
            }
        }
    }
}

void MainWindow::paintBioshopCanWalk(QPainter *paint)
{
    for(int i = 1,j = 1;last_x + i <= 8 && last_y + j <= 8;i ++,j ++){
        if(canWalk(last_x + i,last_y + j)){
            if(matrix[last_x + i][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y + j);
                Walkable[last_x + i][last_y + j] = 1;
            }
            if(matrix[last_x + i][last_y + j] != 0){
                if(state == 0 && matrix[last_x + i][last_y + j] < 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                if(state == 1 && matrix[last_x + i][last_y + j] > 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                break;
            }
        }
    }
    for(int i = 1,j = -1;last_x + i <= 8 && last_y + j > 0;i ++,j --){
        if(canWalk(last_x + i,last_y + j)){
            if(matrix[last_x + i][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y + j);
                Walkable[last_x + i][last_y + j] = 1;
            }
            if(matrix[last_x + i][last_y + j] != 0){
                if(state == 0 && matrix[last_x + i][last_y + j] < 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                if(state == 1 && matrix[last_x + i][last_y + j] > 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                break;
            }
        }
    }
    for(int i = -1,j = -1;last_x + i > 0 && last_y + j > 0;i --,j --){
        if(canWalk(last_x + i,last_y + j)){
            if(matrix[last_x + i][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y + j);
                Walkable[last_x + i][last_y + j] = 1;
            }
            if(matrix[last_x + i][last_y + j] != 0){
                if(state == 0 && matrix[last_x + i][last_y + j] < 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                if(state == 1 && matrix[last_x + i][last_y + j] > 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                break;
            }
        }
    }
    for(int i = -1,j = 1;last_x + i > 0 && last_y + j <= 8;i --,j ++){
        if(canWalk(last_x + i,last_y + j)){
            if(matrix[last_x + i][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y + j);
                Walkable[last_x + i][last_y + j] = 1;
            }
            if(matrix[last_x + i][last_y + j] != 0){
                if(state == 0 && matrix[last_x + i][last_y + j] < 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                if(state == 1 && matrix[last_x + i][last_y + j] > 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                break;
            }
        }
    }
}

void MainWindow::paintKingCanWalk(QPainter *paint)
{
    //普通操作
    for(int i = -1;i <= 1;i ++){
        for(int j = -1;j <= 1;j ++){
            if(canWalk(i + last_x,j + last_y)){
                if(matrix[last_x + i][last_y + j] <= 0 && state == 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                if(matrix[last_x + i][last_y + j] >= 0 && state == 1){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
            }
        }
    }
    //王车易位
    setTempMatrix();
    setAttackMatrix();
    if(!pointInDanger(last_x,last_y)){
        for(int j = 1;last_y + j <= 8;j ++){
            if(state == 0 && last_x == 1 && last_y == 5){
                if(matrix[last_x][last_y + j] != Pieces::white_rook && matrix[last_x][last_y + j] != 0)break;
                if(matrix[last_x][last_y + j] == Pieces::white_rook && (!pointInDanger(last_x,last_y + 1)) && (!pointInDanger(last_x,last_y + 2))){
                    paintCanWalkPoint(paint,last_x,last_y + 1);
                    Walkable[last_x][last_y + 1] = 1;
                    paintCanWalkPoint(paint,last_x,last_y + 2);
                    Walkable[last_x][last_y + 2] = 1;
                }
            }else if(state == 1 && last_x == 8 && last_y == 5){
                if(matrix[last_x][last_y + j] != Pieces::black_rook && matrix[last_x][last_y + j] != 0)break;
                if(matrix[last_x][last_y + j] == Pieces::black_rook && (!pointInDanger(last_x,last_y + 1)) && (!pointInDanger(last_x,last_y + 2))){
                    paintCanWalkPoint(paint,last_x,last_y + 1);
                    Walkable[last_x][last_y + 1] = 1;
                    paintCanWalkPoint(paint,last_x,last_y + 2);
                    Walkable[last_x][last_y + 2] = 1;
                    break;
                }
            }
        }
        for(int j = -1;last_y + j > 0;j --){
            if(state == 0 && last_x == 1 && last_y == 5){
                if(matrix[last_x][last_y + j] != Pieces::white_rook && matrix[last_x][last_y + j] != 0)break;
                if(matrix[last_x][last_y + j] == Pieces::white_rook && (!pointInDanger(last_x,last_y - 1)) && (!pointInDanger(last_x,last_y - 2))){
                    paintCanWalkPoint(paint,last_x,last_y - 1);
                    Walkable[last_x][last_y - 1] = 1;
                    paintCanWalkPoint(paint,last_x,last_y - 2);
                    Walkable[last_x][last_y - 2] = 1;
                    break;
                }
            }else if(state == 1 && last_x == 8 && last_y == 5){
                if(matrix[last_x][last_y + j] != Pieces::black_rook && matrix[last_x][last_y + j] != 0)break;
                if(matrix[last_x][last_y + j] == Pieces::black_rook && (!pointInDanger(last_x,last_y - 1)) && (!pointInDanger(last_x,last_y - 2))){
                    paintCanWalkPoint(paint,last_x,last_y - 1);
                    Walkable[last_x][last_y - 1] = 1;
                    paintCanWalkPoint(paint,last_x,last_y - 2);
                    Walkable[last_x][last_y - 2] = 1;
                    break;
                }
            }
        }
    }
}

void MainWindow::paintKnightCanWalk(QPainter *paint)
{
    if(state == 0){
        if(matrix[last_x + 2][last_y + 1] <= 0 && canWalk(last_x + 2,last_y + 1)){paintCanWalkPoint(paint,last_x + 2,last_y + 1); Walkable[last_x + 2][last_y + 1] = 1;}
        if(matrix[last_x + 2][last_y - 1] <= 0 && canWalk(last_x + 2,last_y - 1)){paintCanWalkPoint(paint,last_x + 2,last_y - 1); Walkable[last_x + 2][last_y - 1] = 1;}
        if(matrix[last_x - 2][last_y + 1] <= 0 && canWalk(last_x - 2,last_y + 1)){paintCanWalkPoint(paint,last_x - 2,last_y + 1); Walkable[last_x - 2][last_y + 1] = 1;}
        if(matrix[last_x - 2][last_y - 1] <= 0 && canWalk(last_x - 2,last_y - 1)){paintCanWalkPoint(paint,last_x - 2,last_y - 1); Walkable[last_x - 2][last_y - 1] = 1;}
        if(matrix[last_x + 1][last_y + 2] <= 0 && canWalk(last_x + 1,last_y + 2)){paintCanWalkPoint(paint,last_x + 1,last_y + 2); Walkable[last_x + 1][last_y + 2] = 1;}
        if(matrix[last_x + 1][last_y - 2] <= 0 && canWalk(last_x + 1,last_y - 2)){paintCanWalkPoint(paint,last_x + 1,last_y - 2); Walkable[last_x + 1][last_y - 2] = 1;}
        if(matrix[last_x - 1][last_y + 2] <= 0 && canWalk(last_x - 1,last_y + 2)){paintCanWalkPoint(paint,last_x - 1,last_y + 2); Walkable[last_x - 1][last_y + 2] = 1;}
        if(matrix[last_x - 1][last_y - 2] <= 0 && canWalk(last_x - 1,last_y - 2)){paintCanWalkPoint(paint,last_x - 1,last_y - 2); Walkable[last_x - 1][last_y - 2] = 1;}
    }
    if(state == 1){
        if(matrix[last_x + 2][last_y + 1] >= 0 && canWalk(last_x + 2,last_y + 1)){paintCanWalkPoint(paint,last_x + 2,last_y + 1); Walkable[last_x + 2][last_y + 1] = 1;}
        if(matrix[last_x + 2][last_y - 1] >= 0 && canWalk(last_x + 2,last_y - 1)){paintCanWalkPoint(paint,last_x + 2,last_y - 1); Walkable[last_x + 2][last_y - 1] = 1;}
        if(matrix[last_x - 2][last_y + 1] >= 0 && canWalk(last_x - 2,last_y + 1)){paintCanWalkPoint(paint,last_x - 2,last_y + 1); Walkable[last_x - 2][last_y + 1] = 1;}
        if(matrix[last_x - 2][last_y - 1] >= 0 && canWalk(last_x - 2,last_y - 1)){paintCanWalkPoint(paint,last_x - 2,last_y - 1); Walkable[last_x - 2][last_y - 1] = 1;}
        if(matrix[last_x + 1][last_y + 2] >= 0 && canWalk(last_x + 1,last_y + 2)){paintCanWalkPoint(paint,last_x + 1,last_y + 2); Walkable[last_x + 1][last_y + 2] = 1;}
        if(matrix[last_x + 1][last_y - 2] >= 0 && canWalk(last_x + 1,last_y - 2)){paintCanWalkPoint(paint,last_x + 1,last_y - 2); Walkable[last_x + 1][last_y - 2] = 1;}
        if(matrix[last_x - 1][last_y + 2] >= 0 && canWalk(last_x - 1,last_y + 2)){paintCanWalkPoint(paint,last_x - 1,last_y + 2); Walkable[last_x - 1][last_y + 2] = 1;}
        if(matrix[last_x - 1][last_y - 2] >= 0 && canWalk(last_x - 1,last_y - 2)){paintCanWalkPoint(paint,last_x - 1,last_y - 2); Walkable[last_x - 1][last_y - 2] = 1;}
    }

}

void MainWindow::paintPawnCanWalk(QPainter *paint)
{
    if(state == 0){
        //第一步可以走两步
        if(last_x == 2){
            if(matrix[last_x + 1][last_y] == 0 && canWalk(last_x + 1,last_y)){
                paintCanWalkPoint(paint,last_x + 1,last_y);
                Walkable[last_x + 1][last_y] = 1;
            }
            if(matrix[last_x + 2][last_y] == 0 && matrix[last_x + 1][last_y] == 0 && canWalk(last_x + 2,last_y)){
                paintCanWalkPoint(paint,last_x + 2,last_y);
                Walkable[last_x + 2][last_y] = 1;
            }
        }
        //直走
        if(matrix[last_x + 1][last_y] == 0 && canWalk(last_x + 1,last_y)){
            paintCanWalkPoint(paint,last_x + 1,last_y);
            Walkable[last_x + 1][last_y] = 1;
        }
        //斜吃
        if(matrix[last_x + 1][last_y - 1] < 0 && canWalk(last_x + 1,last_y - 1)){
            paintCanWalkPoint(paint,last_x + 1,last_y - 1);
            Walkable[last_x + 1][last_y - 1] = 1;
        }
        if(matrix[last_x + 1][last_y + 1] < 0 && canWalk(last_x + 1,last_y + 1)){
            paintCanWalkPoint(paint,last_x + 1,last_y + 1);
            Walkable[last_x +  1][last_y + 1] = 1;
        }
    }else if(state == 1){
        //第一步可以走两步
        if(last_x == 7){
            if(matrix[last_x - 1][last_y] == 0 && canWalk(last_x - 1,last_y)){
                paintCanWalkPoint(paint,last_x - 1,last_y);
                Walkable[last_x - 1][last_y] = 1;
            }
            if(matrix[last_x - 2][last_y] == 0 && matrix[last_x - 1][last_y] == 0 && canWalk(last_x - 2,last_y)){
                paintCanWalkPoint(paint,last_x - 2,last_y);
                Walkable[last_x - 2][last_y] = 1;
            }
        }
        //直走
        if(matrix[last_x - 1][last_y] == 0 && canWalk(last_x - 1,last_y)){
            paintCanWalkPoint(paint,last_x - 1,last_y);
            Walkable[last_x - 1][last_y] = 1;
        }
        //斜吃
        if(matrix[last_x - 1][last_y - 1] > 0 && canWalk(last_x - 1,last_y - 1)){
            paintCanWalkPoint(paint,last_x - 1,last_y - 1);
            Walkable[last_x - 1][last_y - 1] = 1;
        }
        if(matrix[last_x - 1][last_y + 1] > 0 && canWalk(last_x - 1,last_y + 1)){
            paintCanWalkPoint(paint,last_x - 1,last_y + 1);
            Walkable[last_x - 1][last_y + 1] = 1;
        }
    }
}

void MainWindow::paintQueenCanWalk(QPainter *paint)
{
    //上下左右四个方向
    for(int i = 1;last_x + i <= 8;i ++){
        if(canWalk(last_x + i,last_y)){
            if(matrix[last_x + i][last_y] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y);
                Walkable[last_x + i][last_y] = 1;
            }
            if(matrix[last_x + i][last_y] != 0){
                if(matrix[last_x + i][last_y] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x + i,last_y);
                    Walkable[last_x + i][last_y] = 1;
                }
                if(matrix[last_x + i][last_y] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x + i,last_y);
                    Walkable[last_x + i][last_y] = 1;
                }
                break;
            }
        }
    }
    for(int i = -1;last_x + i > 0;i --){
        if(canWalk(last_x + i,last_y)){
            if(matrix[last_x + i][last_y] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y);
                Walkable[last_x + i][last_y] = 1;
            }
            if(matrix[last_x + i][last_y] != 0){
                if(matrix[last_x + i][last_y] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x + i,last_y);
                    Walkable[last_x + i][last_y] = 1;
                }
                if(matrix[last_x + i][last_y] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x + i,last_y);
                    Walkable[last_x + i][last_y] = 1;
                }
                break;
            }
        }
    }
    for(int j = 1;last_y + j <= 8;j ++){
        if(canWalk(last_x,last_y + j)){
            if(matrix[last_x][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x,last_y + j);
                Walkable[last_x][last_y + j] = 1;
            }
            if(matrix[last_x][last_y + j] != 0){
                if(matrix[last_x][last_y + j] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x,last_y + j);
                    Walkable[last_x][last_y + j] = 1;
                }
                if(matrix[last_x][last_y + j] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x,last_y + j);
                    Walkable[last_x][last_y + j] = 1;
                }
                break;
            }
        }
    }
    for(int j = -1;last_y + j > 0;j --){
        if(canWalk(last_x,last_y + j)){
            if(matrix[last_x][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x,last_y + j);
                Walkable[last_x][last_y + j] = 1;
            }
            if(matrix[last_x][last_y + j] != 0){
                if(matrix[last_x][last_y + j] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x,last_y + j);
                    Walkable[last_x][last_y + j] = 1;
                }
                if(matrix[last_x][last_y + j] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x,last_y + j);
                    Walkable[last_x][last_y + j] = 1;
                }
                break;
            }
        }
    }
    //斜向
    for(int i = 1,j = 1;last_x + i <= 8 && last_y + j <= 8;i ++,j ++){
        if(canWalk(last_x + i,last_y + j)){
            if(matrix[last_x + i][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y + j);
                Walkable[last_x+i][last_y + j] = 1;
            }
            if(matrix[last_x + i][last_y + j] != 0){
                if(matrix[last_x + i][last_y + j] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x+i][last_y+j] = 1;
                }
                if(matrix[last_x + i][last_y + j] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                break;
            }
        }
    }
    for(int i = 1,j = -1;last_x + i <= 8 && last_y + j > 0;i ++,j --){
        if(canWalk(last_x + i,last_y + j)){
            if(matrix[last_x + i][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y + j);
                Walkable[last_x+i][last_y + j] = 1;
            }
            if(matrix[last_x + i][last_y + j] != 0){
                if(matrix[last_x + i][last_y + j] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x+i][last_y+j] = 1;
                }
                if(matrix[last_x + i][last_y + j] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                break;
            }
        }
    }
    for(int i = -1,j = -1;last_x + i > 0 && last_y + j > 0;i --,j --){
        if(canWalk(last_x + i,last_y + j)){
            if(matrix[last_x + i][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y + j);
                Walkable[last_x+i][last_y + j] = 1;
            }
            if(matrix[last_x + i][last_y + j] != 0){
                if(matrix[last_x + i][last_y + j] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x+i][last_y+j] = 1;
                }
                if(matrix[last_x + i][last_y + j] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                break;
            }
        }
    }
    for(int i = -1,j = 1;last_x + i > 0 && last_y + j <= 8;i --,j ++){
        if(canWalk(last_x + i,last_y + j)){
            if(matrix[last_x + i][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y + j);
                Walkable[last_x+i][last_y + j] = 1;
            }
            if(matrix[last_x + i][last_y + j] != 0){
                if(matrix[last_x + i][last_y + j] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x+i][last_y+j] = 1;
                }
                if(matrix[last_x + i][last_y + j] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x + i,last_y + j);
                    Walkable[last_x + i][last_y + j] = 1;
                }
                break;
            }
        }
    }
}

void MainWindow::paintRookCanWalk(QPainter *paint)
{
    //上下左右四个方向
    for(int i = 1;last_x + i <= 8;i ++){
        if(canWalk(last_x + i,last_y)){
            if(matrix[last_x + i][last_y] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y);
                Walkable[last_x + i][last_y] = 1;
            }
            if(matrix[last_x + i][last_y] != 0){
                if(matrix[last_x + i][last_y] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x + i,last_y);
                    Walkable[last_x + i][last_y] = 1;
                }
                if(matrix[last_x + i][last_y] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x + i,last_y);
                    Walkable[last_x + i][last_y] = 1;
                }
                break;
            }
        }
    }
    for(int i = -1;last_x + i > 0;i --){
        if(canWalk(last_x + i,last_y)){
            if(matrix[last_x + i][last_y] == 0){
                paintCanWalkPoint(paint,last_x + i,last_y);
                Walkable[last_x + i][last_y] = 1;
            }
            if(matrix[last_x + i][last_y] != 0){
                if(matrix[last_x + i][last_y] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x + i,last_y);
                    Walkable[last_x + i][last_y] = 1;
                }
                if(matrix[last_x + i][last_y] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x + i,last_y);
                    Walkable[last_x + i][last_y] = 1;
                }
                break;
            }
        }
    }
    for(int j = 1;last_y + j <= 8;j ++){
        if(canWalk(last_x,last_y + j)){
            if(matrix[last_x][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x,last_y + j);
                Walkable[last_x][last_y + j] = 1;
            }
            if(matrix[last_x][last_y + j] != 0){
                if(matrix[last_x][last_y + j] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x,last_y + j);
                    Walkable[last_x][last_y + j] = 1;
                }
                if(matrix[last_x][last_y + j] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x,last_y + j);
                    Walkable[last_x][last_y + j] = 1;
                }
                break;
            }
        }
    }
    for(int j = -1;last_y + j > 0;j --){
        if(canWalk(last_x,last_y + j)){
            if(matrix[last_x][last_y + j] == 0){
                paintCanWalkPoint(paint,last_x,last_y + j);
                Walkable[last_x][last_y + j] = 1;
            }
            if(matrix[last_x][last_y + j] != 0){
                if(matrix[last_x][last_y + j] < 0 && state == 0){
                    paintCanWalkPoint(paint,last_x,last_y + j);
                    Walkable[last_x][last_y + j] = 1;
                }
                if(matrix[last_x][last_y + j] > 0 && state == 1){
                    paintCanWalkPoint(paint,last_x,last_y + j);
                    Walkable[last_x][last_y + j] = 1;
                }
                break;
            }
        }
    }
}

void MainWindow::paintCanWalkPoint(QPainter* paint,int x, int y)
{
    if(state == 0)paint->drawEllipse(cadinate_jtox(y) + width / 4,cadinate_itoy(x) + width / 4,width / 2,width / 2);
    else if(state == 1)paint->drawEllipse(cadinate_jtox(9 - y) + width / 4,cadinate_itoy(9 - x) + width / 4,width / 2,width / 2);
}

void MainWindow::addWaittime()
{
    if(waittime < 60)waittime ++;
    else {
        if(isOnCharge && inGame)emit waittimeout();
        else{
            if(inGame)winMessage();
        }
    }
    ui->lcdNumber->display(60 - waittime);
}

void MainWindow::receiveIP(QString ip)
{
    qDebug()<<"strat connect to host.";
    this->inputIP = ip;

    connectHost();
    //qDebug()<<ip;
}

int MainWindow::cadinate_jtox(int x)
{
    return begin_x + (x - 1) * width;
}

int MainWindow::cadinate_itoy(int y)
{
    return begin_y + (8 - y) * width;
}

void MainWindow::iniServer()
{
    qDebug()<<"iniServer.";

    //开始监听模式，对所有IP 监听，端口号指定8888。
    this->haveConnected = this->listenSocket->listen(QHostAddress::Any,8888);
    //listen接受连接请求到来(第一次握手)，发射信号进行处理
    QObject::connect(this->listenSocket,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    if(haveConnected){
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        setState(0);
    }
}

void MainWindow::delServer()
{
    this->listenSocket->close();
}

void MainWindow::connectHost()
{
    qDebug()<<"ini client.";
    this->clientreadWriteSocket = new QTcpSocket;
    this->clientreadWriteSocket->connectToHost(QHostAddress(inputIP),8888);
    linkTimer->start(2500);
    connect(linkTimer,SIGNAL(timeout()),this,SLOT(missLinkMessage()));
    connect(clientreadWriteSocket,SIGNAL(connected()),this,SLOT(linkSuccess()));
    QObject::connect(this->clientreadWriteSocket,SIGNAL(readyRead()),this,SLOT(clientReceiveMessage()));
}

//初始化棋盘
void MainWindow::inimatrix()
{
    //黑方：车马象王后象马车
    //白方：车马象后王象马车
    matrix[1][1] = matrix[1][8] = Pieces::white_rook;
    matrix[1][2] = matrix[1][7] = Pieces::white_knight;
    matrix[1][3] = matrix[1][6] = Pieces::white_bishop;
    matrix[1][4] = Pieces::white_queen;
    matrix[1][5] = Pieces::white_king;

    matrix[8][1] = matrix[8][8] = Pieces::black_rook;
    matrix[8][2] = matrix[8][7] = Pieces::black_knight;
    matrix[8][3] = matrix[8][6] = Pieces::black_bishop;
    matrix[8][4] = Pieces::black_queen;
    matrix[8][5] = Pieces::black_king;

    for(int i = 2;i < 8;i ++){
        for(int j = 1;j <= 8;j ++){
            if(i == 2){
                matrix[i][j] = Pieces::white_pawn;
            }else if(i == 7){
                matrix[i][j] = Pieces::black_pawn;
            }else{
                matrix[i][j] = Pieces::none;
            }
        }
    }
}

//刷新危险棋盘
void MainWindow::setDangerMatrix()
{
    resetDanger();
    for(int m = 1;m <= 8;m ++){
        for(int n = 1;n <= 8;n ++){
            if(state == 0 && matrix[m][n] < 0){
                switch (matrix[m][n]) {
                case -6://bishop
                    for(int i = 1,j = 1;m + i <= 8 && n + j <= 8;i ++,j ++){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] < 0)break;
                            if(matrix[m + i][n + j] > 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = 1,j = -1;m + i <= 8 && n + j > 0;i ++,j --){
                         if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] < 0)break;
                            if(matrix[m + i][n + j] > 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1,j = -1;m + i > 0 && n + j > 0;i --,j --){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] < 0)break;
                            if(matrix[m + i][n + j] > 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1,j = 1;m + i > 0 && n + j <= 8;i --,j ++){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] < 0)break;
                            if(matrix[m + i][n + j] > 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    break;
                case -5://king
                    for(int i = -1;i <= 1;i ++){
                        for(int j = -1;j <= 1;j ++){
                            if(canWalk(m + i,n + j)){
                                if(matrix[m + i][n + j] < 0)break;
                                if(matrix[m + i][n + j] > 0){
                                    dangerMatrix[m + i][n + j] = 1;
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case -4://knight
                    if(matrix[m + 2][n + 1] > 0 && canWalk(m + 2,n + 1))dangerMatrix[m + 2][n + 1] = 1;
                    if(matrix[m + 2][n - 1] > 0 && canWalk(m + 2,n - 1))dangerMatrix[m + 2][n - 1] = 1;
                    if(matrix[m - 2][n + 1] > 0 && canWalk(m - 2,n + 1))dangerMatrix[m - 2][n + 1] = 1;
                    if(matrix[m - 2][n - 1] > 0 && canWalk(m - 2,n - 1))dangerMatrix[m - 2][n - 1] = 1;
                    if(matrix[m + 1][n + 2] > 0 && canWalk(m + 1,n + 2))dangerMatrix[m + 1][n + 2] = 1;
                    if(matrix[m + 1][n - 2] > 0 && canWalk(m + 1,n - 2))dangerMatrix[m + 1][n - 2] = 1;
                    if(matrix[m - 1][n + 2] > 0 && canWalk(m - 1,n + 2))dangerMatrix[m - 1][n + 2] = 1;
                    if(matrix[m - 1][n - 2] > 0 && canWalk(m - 1,n - 2))dangerMatrix[m - 1][n - 2] = 1;
                    break;
                case -3://pawn
                    if(matrix[m - 1][n - 1] > 0 /*&& canWalk(m - 1,n - 1)*/)dangerMatrix[m - 1][n - 1] = 1;
                    if(matrix[m - 1][n + 1] > 0 /*&& canWalk(m - 1,n + 1)*/)dangerMatrix[m - 1][n + 1] = 1;
                    break;
                case -2://queen
                    for(int i = 1;m + i <= 8;i ++){
                        if(canWalk(m + i,n)){
                            if(matrix[m + i][n] < 0)break;
                            if(matrix[m + i][n] > 0){
                                dangerMatrix[m + i][n] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1;m + i > 0;i --){
                        if(canWalk(m + i,n)){
                            if(matrix[m + i][n] < 0)break;
                            if(matrix[m + i][n] > 0){
                                dangerMatrix[m + i][n] = 1;
                                break;
                            }
                        }
                    }
                    for(int j = 1;n + j <= 8;j ++){
                        if(canWalk(m,n + j)){
                            if(matrix[m][n + j] < 0)break;
                            if(matrix[m][n + j] > 0){
                                dangerMatrix[m][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int j = -1;n + j > 0;j --){
                        if(canWalk(m,n + j)){
                            if(matrix[m][n + j] < 0)break;
                            if(matrix[m][n + j] > 0){
                                dangerMatrix[m][n + j] = 1;
                                break;
                            }
                        }
                    }
                    //斜向
                    for(int i = 1,j = 1;m + i <= 8 && n + j <= 8;i ++,j ++){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] < 0)break;
                            if(matrix[m + i][n + j] > 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = 1,j = -1;m + i <= 8 && n + j > 0;i ++,j --){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] < 0)break;
                            if(matrix[m + i][n + j] > 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1,j = -1;m + i > 0 && n + j > 0;i --,j --){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] < 0)break;
                            if(matrix[m + i][n + j] > 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1,j = 1;m + i > 0 && n + j <= 8;i --,j ++){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] < 0)break;
                            if(matrix[m + i][n + j] > 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    break;
                case -1://rook
                    for(int i = 1;m + i <= 8;i ++){
                        if(canWalk(m + i,n)){
                            if(matrix[m + i][n] < 0)break;
                            if(matrix[m + i][n] > 0){
                                dangerMatrix[m + i][n] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1;m + i > 0;i --){
                        if(canWalk(m + i,n)){
                            if(matrix[m + i][n] < 0)break;
                            if(matrix[m + i][n] > 0){
                                dangerMatrix[m + i][n] = 1;
                                break;
                            }
                        }
                    }
                    for(int j = 1;n + j <= 8;j ++){
                        if(canWalk(m,n + j)){
                            if(matrix[m][n + j] < 0)break;
                            if(matrix[m][n + j] > 0){
                                dangerMatrix[m][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int j = -1;n + j > 0;j --){
                        if(canWalk(m,n + j)){
                            if(matrix[m][n + j] < 0)break;
                            if(matrix[m][n + j] > 0){
                                dangerMatrix[m][n + j] = 1;
                                break;
                            }
                        }
                    }
                    break;
                }
            }

            else if(state == 1 && matrix[m][n] > 0){
                switch (matrix[m][n]) {
                case 1:
                    for(int i = 1,j = 1;m + i <= 8 && n + j <= 8;i ++,j ++){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] > 0)break;
                            if(matrix[m + i][n + j] < 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = 1,j = -1;m + i <= 8 && n + j > 0;i ++,j --){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] > 0)break;
                            if(matrix[m + i][n + j] < 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1,j = -1;m + i > 0 && n + j > 0;i --,j --){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] > 0)break;
                            if(matrix[m + i][n + j] < 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1,j = 1;m + i > 0 && n + j <= 8;i --,j ++){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] > 0)break;
                            if(matrix[m + i][n + j] < 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    break;
                case 2:
                    for(int i = -1;i <= 1;i ++){
                        for(int j = -1;j <= 1;j ++){
                            if(canWalk(m + i,n + j)){
                                if(matrix[m + i][n + j] > 0)break;
                                if(matrix[m + i][n + j] < 0){
                                    dangerMatrix[m + i][n + j] = 1;
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case 3:
                    if(matrix[m + 2][n + 1] < 0 && canWalk(m + 2,n + 1))dangerMatrix[m + 2][n + 1] = 1;
                    if(matrix[m + 2][n - 1] < 0 && canWalk(m + 2,n - 1))dangerMatrix[m + 2][n - 1] = 1;
                    if(matrix[m - 2][n + 1] < 0 && canWalk(m - 2,n + 1))dangerMatrix[m - 2][n + 1] = 1;
                    if(matrix[m - 2][n - 1] < 0 && canWalk(m - 2,n - 1))dangerMatrix[m - 2][n - 1] = 1;
                    if(matrix[m + 1][n + 2] < 0 && canWalk(m + 1,n + 2))dangerMatrix[m + 1][n + 2] = 1;
                    if(matrix[m + 1][n - 2] < 0 && canWalk(m + 1,n - 2))dangerMatrix[m + 1][n - 2] = 1;
                    if(matrix[m - 1][n + 2] < 0 && canWalk(m - 1,n + 2))dangerMatrix[m - 1][n + 2] = 1;
                    if(matrix[m - 1][n - 2] < 0 && canWalk(m - 1,n - 2))dangerMatrix[m - 1][n - 2] = 1;
                    break;
                case 4:
                    if(matrix[m + 1][n - 1] < 0 && canWalk(m + 1,n - 1))dangerMatrix[m + 1][n - 1] = 1;
                    if(matrix[m + 1][n + 1] < 0 && canWalk(m + 1,n + 1))dangerMatrix[m + 1][n + 1] = 1;
                    break;
                case 5:
                    for(int i = 1;m + i <= 8;i ++){
                        if(canWalk(m + i,n)){
                            if(matrix[m + i][n] > 0)break;
                            if(matrix[m + i][n] < 0){
                                dangerMatrix[m + i][n] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1;m + i > 0;i --){
                        if(canWalk(m + i,n)){
                            if(matrix[m + i][n] > 0)break;
                            if(matrix[m + i][n] < 0){
                                dangerMatrix[m + i][n] = 1;
                                break;
                            }
                        }
                    }
                    for(int j = 1;n + j <= 8;j ++){
                        if(canWalk(m,n + j)){
                            if(matrix[m][n + j] > 0)break;
                            if(matrix[m][n + j] < 0){
                                dangerMatrix[m][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int j = -1;n + j > 0;j --){
                        if(canWalk(m,n + j)){
                            if(matrix[m][n + j] > 0)break;
                            if(matrix[m][n + j] < 0){
                                dangerMatrix[m][n + j] = 1;
                                break;
                            }
                        }
                    }
                    //斜向
                    for(int i = 1,j = 1;m + i <= 8 && n + j <= 8;i ++,j ++){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] > 0)break;
                            if(matrix[m + i][n + j] < 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = 1,j = -1;m + i <= 8 && n + j > 0;i ++,j --){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] > 0)break;
                            if(matrix[m + i][n + j] < 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1,j = -1;m + i > 0 && n + j > 0;i --,j --){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] > 0)break;
                            if(matrix[m + i][n + j] < 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1,j = 1;m + i > 0 && n + j <= 8;i --,j ++){
                        if(canWalk(m+i,n+j)){
                            if(matrix[m + i][n + j] > 0)break;
                            if(matrix[m + i][n + j] < 0){
                                dangerMatrix[m + i][n + j] = 1;
                                break;
                            }
                        }
                    }
                    break;
                case 6:
                    for(int i = 1;m + i <= 8;i ++){
                        if(canWalk(m + i,n)){
                            if(matrix[m + i][n] > 0)break;
                            if(matrix[m + i][n] < 0){
                                dangerMatrix[m + i][n] = 1;
                                break;
                            }
                        }
                    }
                    for(int i = -1;m + i > 0;i --){
                        if(canWalk(m + i,n)){
                            if(matrix[m + i][n] > 0)break;
                            if(matrix[m + i][n] < 0){
                                dangerMatrix[m + i][n] = 1;
                                break;
                            }
                        }
                    }
                    for(int j = 1;n + j <= 8;j ++){
                        if(canWalk(m,n + j)){
                            if(matrix[m][n + j] > 0)break;
                            if(matrix[m][n + j] < 0){
                                dangerMatrix[m][n + j] = 1;
                                break;
                            }
                        }
                    }
                    for(int j = -1;n + j > 0;j --){
                        if(canWalk(m,n + j)){
                            if(matrix[m][n + j] > 0)break;
                            if(matrix[m][n + j] < 0){
                                dangerMatrix[m][n + j] = 1;
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}

void MainWindow::setState(int s)
{
    this->state = s;
    inimatrix();
    resetDanger();
    resetWalkable();
    setTempMatrix();
    waittime = 0;
    timer->stop();
    inGame = false;
    if(state == 1){
        king_x = 8;
        king_y = 5;
    }
}

void MainWindow::loadImage()
{
    this->black_bishop.load(":/pictures/pic/black_bishop.png");
    this->black_king.load(":/pictures/pic/black_king.png");
    this->black_knight.load(":/pictures/pic/black_knight.png");
    this->black_pawn.load(":/pictures/pic/black_pawn.png");
    this->black_queen.load(":/pictures/pic/black_queen.png");
    this->black_rook.load(":/pictures/pic/black_rook.png");

    this->white_bishop.load(":/pictures/pic/white_bishop.png");
    this->white_king.load(":/pictures/pic/white_king.png");
    this->white_knight.load(":/pictures/pic/white_knight.png");
    this->white_pawn.load(":/pictures/pic/white_pawn.png");
    this->white_queen.load(":/pictures/pic/white_queen.png");
    this->white_rook.load(":/pictures/pic/white_rook.png");
}

bool MainWindow::canWalk(int x, int y)
{
    if((x != last_x || y != last_y) && x > 0 && x <= 8 && y > 0 && y <= 8){
        return true;
    }
    return false;
}

void MainWindow::resetDanger()
{
    for(int i = 0;i < 10;i ++){
        for(int j = 0;j < 10;j ++){
            dangerMatrix[i][j] = 0;
        }
    }
}

void MainWindow::resetWalkable()
{
    for(int i = 0;i < 10;i ++){
        for(int j = 0;j < 10;j ++){
            Walkable[i][j] = 0;
        }
    }
}

//判断某点是否在敌方攻击范围中
bool MainWindow::pointInDanger(int x, int y)
{
    if(attackMatrix[x][y] == 1)return true;
    else return false;
}

void MainWindow::setTempMatrix()
{
    for(int i = 1;i <= 8;i ++){
        for(int j = 1;j <= 8;j ++){
            tempMatrix[i][j] = matrix[i][j];
        }
    }
}

void MainWindow::setAttackMatrix()
{
    //攻击范围置零
    for(int i = 0;i < 10;i ++){
        for(int j = 0;j < 10;j ++){
            attackMatrix[i][j] = 0;
        }
    }
    if(state == 0){
        for(int i = 1;i <= 8;i ++){
            for(int j = 1;j <= 8;j ++){
                if(tempMatrix[i][j] < 0){
                    switch (tempMatrix[i][j]) {
                    case -1://rook
                        for(int t = 1;i + t <= 8;t ++){
                            if(tempMatrix[i + t][j] == 0)attackMatrix[i + t][j] = 1;
                            else if(tempMatrix[i + t][j] > 0){
                                attackMatrix[i + t][j] = 1;
                                break;
                            }else if(tempMatrix[i + t][j] < 0)break;
                        }
                        for(int t = -1;i + t > 0;t --){
                            if(tempMatrix[i + t][j] == 0)attackMatrix[i + t][j] = 1;
                            else if(tempMatrix[i + t][j] > 0){
                                attackMatrix[i + t][j] = 1;
                                break;
                            }else if(tempMatrix[i + t][j] < 0)break;
                        }
                        for(int t = 1;j + t <= 8;t ++){
                            if(tempMatrix[i][j + t] == 0)attackMatrix[i][j + t] = 1;
                            else if(tempMatrix[i][j + t] > 0){
                                attackMatrix[i][j + t] = 1;
                                break;
                            }else if(tempMatrix[i][j + t] < 0)break;
                        }
                        for(int t = -1;j + t > 0;t --){
                            if(tempMatrix[i][j + t] == 0)attackMatrix[i][j + t] = 1;
                            else if(tempMatrix[i][j + t] > 0){
                                attackMatrix[i][j + t] = 1;
                                break;
                            }else if(tempMatrix[i][j + t] < 0)break;
                        }
                        break;
                    case -2://queen
                        for(int t = 1;i + t <= 8;t ++){
                            if(tempMatrix[i + t][j] == 0)attackMatrix[i + t][j] = 1;
                            else if(tempMatrix[i + t][j] > 0){
                                attackMatrix[i + t][j] = 1;
                                break;
                            }else if(tempMatrix[i + t][j] < 0)break;
                        }
                        for(int t = -1;i + t > 0;t --){
                            if(tempMatrix[i + t][j] == 0)attackMatrix[i + t][j] = 1;
                            else if(tempMatrix[i + t][j] > 0){
                                attackMatrix[i + t][j] = 1;
                                break;
                            }else if(tempMatrix[i + t][j] < 0)break;
                        }
                        for(int t = 1;j + t <= 8;t ++){
                            if(tempMatrix[i][j + t] == 0)attackMatrix[i][j + t] = 1;
                            else if(tempMatrix[i][j + t] > 0){
                                attackMatrix[i][j + t] = 1;
                                break;
                            }else if(tempMatrix[i][j + t] < 0)break;
                        }
                        for(int t = -1;j + t > 0;t --){
                            if(tempMatrix[i][j + t] == 0)attackMatrix[i][j + t] = 1;
                            else if(tempMatrix[i][j + t] > 0){
                                attackMatrix[i][j + t] = 1;
                                break;
                            }else if(tempMatrix[i][j + t] < 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j + t <= 8;t++){
                            if(tempMatrix[i + t][j + t] == 0)attackMatrix[i + t][j + t] = 1;
                            else if(tempMatrix[i + t][j + t] > 0){
                                attackMatrix[i + t][j + t] = 1;
                                break;
                            }else if(tempMatrix[i + t][j + t] < 0)break;
                        }
                        for(int t = 1;i - t > 0 && j - t > 0;t++){
                            if(tempMatrix[i - t][j - t] == 0)attackMatrix[i - t][j - t] = 1;
                            else if(tempMatrix[i - t][j - t] > 0){
                                attackMatrix[i - t][j - t] = 1;
                                break;
                            }else if(tempMatrix[i - t][j - t] < 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j - t > 0;t ++){
                            if(tempMatrix[i + t][j - t] == 0)attackMatrix[i + t][j - t] = 1;
                            else if(tempMatrix[i + t][j - t] > 0){
                                attackMatrix[i + t][j - t] = 1;
                                break;
                            }else if(tempMatrix[i + t][j - t] < 0)break;
                        }
                        for(int t = 1;i - t > 0 && j + t <= 8;t ++){
                            if(tempMatrix[i - t][j + t] == 0)attackMatrix[i - t][j + t] = 1;
                            else if(tempMatrix[i - t][j + t] > 0){
                                attackMatrix[i - t][j + t] = 1;
                                break;
                            }else if(tempMatrix[i - t][j + t] < 0)break;
                        }
                        break;
                    case -3://pawn
                        if(tempMatrix[i - 1][j + 1] >= 0 && canWalk(i-1,j+1))attackMatrix[i - 1][j + 1] = 1;
                        if(tempMatrix[i - 1][j - 1] >= 0 && canWalk(i-1,j-1))attackMatrix[i - 1][j - 1] = 1;
                        break;
                    case -4://knight
                        if(tempMatrix[i + 1][j + 2] >= 0 && canWalk(i+1,j+2))attackMatrix[i + 1][j + 2] = 1;
                        if(tempMatrix[i + 1][j - 2] >= 0 && canWalk(i+1,j-2))attackMatrix[i + 1][j - 2] = 1;
                        if(tempMatrix[i - 1][j + 2] >= 0 && canWalk(i-1,j+2))attackMatrix[i - 1][j + 2] = 1;
                        if(tempMatrix[i - 1][j - 2] >= 0 && canWalk(i-1,j-2))attackMatrix[i - 1][j - 2] = 1;
                        if(tempMatrix[i + 2][j + 1] >= 0 && canWalk(i+2,j+1))attackMatrix[i + 2][j + 1] = 1;
                        if(tempMatrix[i + 2][j - 1] >= 0 && canWalk(i+2,j-1))attackMatrix[i + 2][j - 1] = 1;
                        if(tempMatrix[i - 2][j + 1] >= 0 && canWalk(i-2,j+1))attackMatrix[i - 2][j + 1] = 1;
                        if(tempMatrix[i - 2][j - 1] >= 0 && canWalk(i-2,j-1))attackMatrix[i - 2][j - 1] = 1;
                        break;
                    case -5://king
                        for(int m = -1;m <= 1;m++){
                            for(int n = -1;n <= 1;n ++){
                                if(canWalk(m + i,n + j)){
                                    if(tempMatrix[m + i][n + j] >= 0)attackMatrix[m + i][n + j] = 1;
                                }
                            }
                        }
                        break;
                    case -6://bishop
                        for(int t = 1;i + t <= 8 && j + t <= 8;t++){
                            if(tempMatrix[i + t][j + t] == 0)attackMatrix[i + t][j + t] = 1;
                            else if(tempMatrix[i + t][j + t] > 0){
                                attackMatrix[i + t][j + t] = 1;
                                break;
                            }else if(tempMatrix[i + t][j + t] < 0)break;
                        }
                        for(int t = 1;i - t > 0 && j - t > 0;t++){
                            if(tempMatrix[i - t][j - t] == 0)attackMatrix[i - t][j - t] = 1;
                            else if(tempMatrix[i - t][j - t] > 0){
                                attackMatrix[i - t][j - t] = 1;
                                break;
                            }else if(tempMatrix[i - t][j - t] < 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j - t > 0;t ++){
                            if(tempMatrix[i + t][j - t] == 0)attackMatrix[i + t][j - t] = 1;
                            else if(tempMatrix[i + t][j - t] > 0){
                                attackMatrix[i + t][j - t] = 1;
                                break;
                            }else if(tempMatrix[i + t][j - t] < 0)break;
                        }
                        for(int t = 1;i - t > 0 && j + t <= 8;t ++){
                            if(tempMatrix[i - t][j + t] == 0)attackMatrix[i - t][j + t] = 1;
                            else if(tempMatrix[i - t][j + t] > 0){
                                attackMatrix[i - t][j + t] = 1;
                                break;
                            }else if(tempMatrix[i - t][j + t] < 0)break;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }else if(state == 1){
        for(int i = 1;i <= 8;i ++){
            for(int j = 1;j <= 8;j ++){
                if(tempMatrix[i][j] > 0){
                    switch (tempMatrix[i][j]) {
                    case 1://bishop
                        for(int t = 1;i + t <= 8 && j + t <= 8;t++){
                            if(tempMatrix[i + t][j + t] == 0)attackMatrix[i + t][j + t] = 1;
                            else if(tempMatrix[i + t][j + t] < 0){
                                attackMatrix[i + t][j + t] = 1;
                                break;
                            }else if(tempMatrix[i + t][j + t] > 0)break;
                        }
                        for(int t = 1;i - t > 0 && j - t > 0;t++){
                            if(tempMatrix[i - t][j - t] == 0)attackMatrix[i - t][j - t] = 1;
                            else if(tempMatrix[i - t][j - t] < 0){
                                attackMatrix[i - t][j - t] = 1;
                                break;
                            }else if(tempMatrix[i - t][j - t] > 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j - t > 0;t ++){
                            if(tempMatrix[i + t][j - t] == 0)attackMatrix[i + t][j - t] = 1;
                            else if(tempMatrix[i + t][j - t] < 0){
                                attackMatrix[i + t][j - t] = 1;
                                break;
                            }else if(tempMatrix[i + t][j - t] > 0)break;
                        }
                        for(int t = 1;i - t > 0 && j + t <= 8;t ++){
                            if(tempMatrix[i - t][j + t] == 0)attackMatrix[i - t][j + t] = 1;
                            else if(tempMatrix[i - t][j + t] < 0){
                                attackMatrix[i - t][j + t] = 1;
                                break;
                            }else if(tempMatrix[i - t][j + t] > 0)break;
                        }
                        break;
                    case 2://king
                        for(int m = -1;m <= 1;m++){
                            for(int n = -1;n <= 1;n ++){
                                if(canWalk(m + i,n + j)){
                                    if(tempMatrix[m + i][n + j] <= 0)attackMatrix[m + i][n + j] = 1;
                                }
                            }
                        }
                        break;
                    case 3://knight
                        if(tempMatrix[i + 1][j + 2] <= 0 && canWalk(i+1,j+2))attackMatrix[i + 1][j + 2] = 1;
                        if(tempMatrix[i + 1][j - 2] <= 0 && canWalk(i+1,j-2))attackMatrix[i + 1][j - 2] = 1;
                        if(tempMatrix[i - 1][j + 2] <= 0 && canWalk(i-1,j+2))attackMatrix[i - 1][j + 2] = 1;
                        if(tempMatrix[i - 1][j - 2] <= 0 && canWalk(i-1,j-2))attackMatrix[i - 1][j - 2] = 1;
                        if(tempMatrix[i + 2][j + 1] <= 0 && canWalk(i+2,j+1))attackMatrix[i + 2][j + 1] = 1;
                        if(tempMatrix[i + 2][j - 1] <= 0 && canWalk(i+2,j-1))attackMatrix[i + 2][j - 1] = 1;
                        if(tempMatrix[i - 2][j + 1] <= 0 && canWalk(i-2,j+1))attackMatrix[i - 2][j + 1] = 1;
                        if(tempMatrix[i - 2][j - 1] <= 0 && canWalk(i-2,j-1))attackMatrix[i - 2][j - 1] = 1;
                        break;
                    case 4://pawn
                        if(tempMatrix[i + 1][j + 1] <= 0 && canWalk(i+1,j+1))attackMatrix[i + 1][j + 1] = 1;
                        if(tempMatrix[i + 1][j - 1] <= 0 && canWalk(i+1,j-1))attackMatrix[i + 1][j - 1] = 1;
                        break;
                    case 5://queen
                        for(int t = 1;i + t <= 8;t ++){
                            if(tempMatrix[i + t][j] == 0)attackMatrix[i + t][j] = 1;
                            else if(tempMatrix[i + t][j] < 0){
                                attackMatrix[i + t][j] = 1;
                                break;
                            }else if(tempMatrix[i + t][j] > 0)break;
                        }
                        for(int t = -1;i + t > 0;t --){
                            if(tempMatrix[i + t][j] == 0)attackMatrix[i + t][j] = 1;
                            else if(tempMatrix[i + t][j] < 0){
                                attackMatrix[i + t][j] = 1;
                                break;
                            }else if(tempMatrix[i + t][j] > 0)break;
                        }
                        for(int t = 1;j + t <= 8;t ++){
                            if(tempMatrix[i][j + t] == 0)attackMatrix[i][j + t] = 1;
                            else if(tempMatrix[i][j + t] < 0){
                                attackMatrix[i][j + t] = 1;
                                break;
                            }else if(tempMatrix[i][j + t] > 0)break;
                        }
                        for(int t = -1;j + t > 0;t --){
                            if(tempMatrix[i][j + t] == 0)attackMatrix[i][j + t] = 1;
                            else if(tempMatrix[i][j + t] < 0){
                                attackMatrix[i][j + t] = 1;
                                break;
                            }else if(tempMatrix[i][j + t] > 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j + t <= 8;t++){
                            if(tempMatrix[i + t][j + t] == 0)attackMatrix[i + t][j + t] = 1;
                            else if(tempMatrix[i + t][j + t] < 0){
                                attackMatrix[i + t][j + t] = 1;
                                break;
                            }else if(tempMatrix[i + t][j + t] > 0)break;
                        }
                        for(int t = 1;i - t > 0 && j - t > 0;t++){
                            if(tempMatrix[i - t][j - t] == 0)attackMatrix[i - t][j - t] = 1;
                            else if(tempMatrix[i - t][j - t] < 0){
                                attackMatrix[i - t][j - t] = 1;
                                break;
                            }else if(tempMatrix[i - t][j - t] > 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j - t > 0;t ++){
                            if(tempMatrix[i + t][j - t] == 0)attackMatrix[i + t][j - t] = 1;
                            else if(tempMatrix[i + t][j - t] < 0){
                                attackMatrix[i + t][j - t] = 1;
                                break;
                            }else if(tempMatrix[i + t][j - t] > 0)break;
                        }
                        for(int t = 1;i - t > 0 && j + t <= 8;t ++){
                            if(tempMatrix[i - t][j + t] == 0)attackMatrix[i - t][j + t] = 1;
                            else if(tempMatrix[i - t][j + t] < 0){
                                attackMatrix[i - t][j + t] = 1;
                                break;
                            }else if(tempMatrix[i - t][j + t] > 0)break;
                        }
                        break;
                    case 6://rook
                        for(int t = 1;i + t <= 8;t ++){
                            if(tempMatrix[i + t][j] == 0)attackMatrix[i + t][j] = 1;
                            else if(tempMatrix[i + t][j] < 0){
                                attackMatrix[i + t][j] = 1;
                                break;
                            }else if(tempMatrix[i + t][j] > 0)break;
                        }
                        for(int t = -1;i + t > 0;t --){
                            if(tempMatrix[i + t][j] == 0)attackMatrix[i + t][j] = 1;
                            else if(tempMatrix[i + t][j] < 0){
                                attackMatrix[i + t][j] = 1;
                                break;
                            }else if(tempMatrix[i + t][j] > 0)break;
                        }
                        for(int t = 1;j + t <= 8;t ++){
                            if(tempMatrix[i][j + t] == 0)attackMatrix[i][j + t] = 1;
                            else if(tempMatrix[i][j + t] < 0){
                                attackMatrix[i][j + t] = 1;
                                break;
                            }else if(tempMatrix[i][j + t] > 0)break;
                        }
                        for(int t = -1;j + t > 0;t --){
                            if(tempMatrix[i][j + t] == 0)attackMatrix[i][j + t] = 1;
                            else if(tempMatrix[i][j + t] < 0){
                                attackMatrix[i][j + t] = 1;
                                break;
                            }else if(tempMatrix[i][j + t] > 0)break;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
    QDebug out = qDebug();
    out<<"king loc"<<king_x<<king_y;
    for(int i = 1;i <= 8;i ++,out<<"\n"){
        for(int j = 1;j <= 8;j ++){
            out<<attackMatrix[i][j]<<" ";
        }
    }
}

bool MainWindow::stalemate()
{
    setTempMatrix();
    setAttackMatrix();
    //王没有被将军
    if(pointInDanger(king_x,king_y)){
        QMessageBox::information(this,"将军","你被将军了！");
        return false;
    }
    qDebug()<<"state"<<state;
    if(state == 0){
        //王无路可走
        for(int i = -1;i <= 1;i ++){
            for(int j = -1;j <= 1;j ++){
                if(matrix[king_x+i][king_y+j] <= 0 && canWalk(king_x+i,king_y+j)){
                    int temp = tempMatrix[king_x + i][king_y + j];
                    tempMatrix[king_x][king_y] = Pieces::none;
                    tempMatrix[king_x + i][king_y + j] = Pieces::white_king;
                    setAttackMatrix();
                    if(!pointInDanger(king_x+i,king_y+j)){return false;}
                    tempMatrix[king_x+i][king_y+j] = temp;
                    tempMatrix[king_x][king_y] = Pieces::white_king;
                }
            }
        }
        //其他兵无路可走
        for(int i = 1;i <= 8;i ++){
            for(int j = 1;j <= 8;j ++){
                if(matrix[i][j] > 0){
                    switch (matrix[i][j]) {
                    case 1://bishop
                        for(int t = 1;i + t <= 8 && j + t <= 8;t++){
                            if(matrix[i + t][j + t] == 0){
                                tempMatrix[i+t][j+t] = Pieces::white_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_bishop;
                                tempMatrix[i+t][j+t] = Pieces::none;
                            }else if(matrix[i + t][j + t] < 0){
                                int temp = tempMatrix[i+t][j+t];
                                tempMatrix[i+t][j+t] = Pieces::white_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_bishop;
                                tempMatrix[i+t][j+t] = temp;
                                break;
                            }else if(matrix[i + t][j + t] > 0)break;
                        }
                        for(int t = 1;i - t > 0 && j - t > 0;t++){
                            if(matrix[i-t][j-t] == 0){
                                tempMatrix[i-t][j-t] = Pieces::white_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_bishop;
                                tempMatrix[i-t][j-t] = Pieces::none;
                            }else if(matrix[i-t][j-t] < 0){
                                int temp = tempMatrix[i-t][j-t];
                                tempMatrix[i-t][j-t] = Pieces::white_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_bishop;
                                tempMatrix[i-t][j-t] = temp;
                                break;
                            }else if(matrix[i-t][j-t] > 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j - t > 0;t++){
                            if(matrix[i+t][j-t] == 0){
                                tempMatrix[i+t][j-t] = Pieces::white_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_bishop;
                                tempMatrix[i+t][j-t] = Pieces::none;
                            }else if(matrix[i+t][j-t] < 0){
                                int temp = tempMatrix[i+t][j-t];
                                tempMatrix[i+t][j-t] = Pieces::white_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_bishop;
                                tempMatrix[i+t][j-t] = temp;
                                break;
                            }else if(matrix[i+t][j-t] > 0)break;
                        }
                        for(int t = 1;i - t > 0 && j + t <= 8;t++){
                            if(matrix[i-t][j+t] == 0){
                                tempMatrix[i-t][j+t] = Pieces::white_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_bishop;
                                tempMatrix[i-t][j+t] = Pieces::none;
                            }else if(matrix[i-t][j+t] < 0){
                                int temp = tempMatrix[i-t][j+t];
                                tempMatrix[i-t][j+t] = Pieces::white_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_bishop;
                                tempMatrix[i-t][j+t] = temp;
                                break;
                            }else if(matrix[i-t][j+t] > 0)break;
                        }
                        break;
                    case 3://knight
                        if(matrix[i + 1][j + 2] <= 0 && canWalk(i+1,j+2)){
                            int temp = tempMatrix[i+1][j+2];
                            tempMatrix[i+1][j+2] = Pieces::white_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_knight;
                            tempMatrix[i+1][j+2] = temp;
                        }
                        if(matrix[i + 1][j - 2] <= 0 && canWalk(i+1,j-2)){
                            int temp = tempMatrix[i+1][j-2];
                            tempMatrix[i+1][j-2] = Pieces::white_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_knight;
                            tempMatrix[i+1][j-2] = temp;
                        }
                        if(matrix[i - 1][j + 2] <= 0 && canWalk(i-1,j+2)){
                            int temp = tempMatrix[i-1][j+2];
                            tempMatrix[i-1][j+2] = Pieces::white_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_knight;
                            tempMatrix[i-1][j+2] = temp;
                        }
                        if(matrix[i - 1][j - 2] <= 0 && canWalk(i-1,j-2)){
                            int temp = tempMatrix[i-1][j-2];
                            tempMatrix[i-1][j-2] = Pieces::white_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_knight;
                            tempMatrix[i-1][j-2] = temp;
                        }
                        if(matrix[i + 2][j + 1] <= 0 && canWalk(i+2,j+1)){
                            int temp = tempMatrix[i+2][j+1];
                            tempMatrix[i+2][j+1] = Pieces::white_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_knight;
                            tempMatrix[i+2][j+1] = temp;
                        }
                        if(matrix[i + 2][j - 1] <= 0 && canWalk(i+2,j-1)){
                            int temp = tempMatrix[i+2][j-1];
                            tempMatrix[i+2][j-1] = Pieces::white_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_knight;
                            tempMatrix[i+2][j-1] = temp;
                        }
                        if(matrix[i - 2][j + 1] <= 0 && canWalk(i-2,j+1)){
                            int temp = tempMatrix[i-2][j+1];
                            tempMatrix[i-2][j+1] = Pieces::white_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_knight;
                            tempMatrix[i-2][j+1] = temp;
                        }
                        if(matrix[i - 2][j - 1] <= 0 && canWalk(i-2,j-1)){
                            int temp = tempMatrix[i-2][j-1];
                            tempMatrix[i-2][j-1] = Pieces::white_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_knight;
                            tempMatrix[i-2][j-1] = temp;
                        }
                        break;
                    case 4://pawn
                        if(matrix[i + 1][j + 1] < 0 && canWalk(i+1,j+1)){
                            int temp = tempMatrix[i+1][j+1];
                            tempMatrix[i+1][j+1] = Pieces::white_pawn;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_pawn;
                            tempMatrix[i+1][j+1] = temp;
                        }
                        if(matrix[i + 1][j - 1] < 0 && canWalk(i+1,j-1)){
                            int temp = tempMatrix[i+1][j-1];
                            tempMatrix[i+1][j-1] = Pieces::white_pawn;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_pawn;
                            tempMatrix[i+1][j-1] = temp;
                        }
                        if(matrix[i + 1][j] == 0 && canWalk(i+1,j)){
                            int temp = tempMatrix[i+1][j];
                            tempMatrix[i+1][j] = Pieces::white_pawn;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_pawn;
                            tempMatrix[i+1][j] = temp;
                        }
                        if(i == 2 && matrix[i+1][j] == 0 && matrix[i+2][j] == 0 && canWalk(i+2,j)){
                            int temp = tempMatrix[i+2][j];
                            tempMatrix[i+2][j] = Pieces::white_pawn;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::white_pawn;
                            tempMatrix[i+2][j] = temp;
                        }
                        break;
                    case 5://queen
                        for(int t = 1;i + t <= 8 && j + t <= 8;t++){
                            if(matrix[i + t][j + t] == 0){
                                tempMatrix[i+t][j+t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i+t][j+t] = Pieces::none;
                            }else if(matrix[i + t][j + t] < 0){
                                int temp = tempMatrix[i+t][j+t];
                                tempMatrix[i+t][j+t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i+t][j+t] = temp;
                                break;
                            }else if(matrix[i + t][j + t] > 0)break;
                        }
                        for(int t = 1;i - t > 0 && j - t > 0;t++){
                            if(matrix[i-t][j-t] == 0){
                                tempMatrix[i-t][j-t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i-t][j-t] = Pieces::none;
                            }else if(matrix[i-t][j-t] < 0){
                                int temp = tempMatrix[i-t][j-t];
                                tempMatrix[i-t][j-t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i-t][j-t] = temp;
                                break;
                            }else if(matrix[i-t][j-t] > 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j - t > 0;t++){
                            if(matrix[i+t][j-t] == 0){
                                tempMatrix[i+t][j-t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i+t][j-t] = Pieces::none;
                            }else if(matrix[i+t][j-t] < 0){
                                int temp = tempMatrix[i+t][j-t];
                                tempMatrix[i+t][j-t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i+t][j-t] = temp;
                                break;
                            }else if(matrix[i+t][j-t] > 0)break;
                        }
                        for(int t = 1;i - t > 0 && j + t <= 8;t++){
                            if(matrix[i-t][j+t] == 0){
                                tempMatrix[i-t][j+t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i-t][j+t] = Pieces::none;
                            }else if(matrix[i-t][j+t] < 0){
                                int temp = tempMatrix[i-t][j+t];
                                tempMatrix[i-t][j+t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i-t][j+t] = temp;
                                break;
                            }else if(matrix[i-t][j+t] > 0)break;
                        }
                        for(int t = 1;i + t <= 8;t ++){
                            if(matrix[i + t][j] == 0){
                                tempMatrix[i+t][j] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i+t][j] = Pieces::none;
                            }else if(matrix[i + t][j] < 0){
                                int temp = tempMatrix[i+t][j];
                                tempMatrix[i+t][j] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i+t][j] = temp;
                                break;
                            }else if(matrix[i + t][j] > 0)break;
                        }
                        for(int t = -1;i + t > 0;t --){
                            if(matrix[i + t][j] == 0){
                                tempMatrix[i+t][j] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i+t][j] = Pieces::none;
                            }else if(matrix[i + t][j] < 0){
                                int temp = tempMatrix[i+t][j];
                                tempMatrix[i+t][j] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i+t][j] = temp;
                                break;
                            }else if(matrix[i + t][j] > 0)break;
                        }
                        for(int t = 1;j + t <= 8;t ++){
                            if(matrix[i][j] == 0){
                                tempMatrix[i][j+t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i][j+t] = Pieces::none;
                            }else if(matrix[i][j+t] < 0){
                                int temp = tempMatrix[i][j+t];
                                tempMatrix[i][j+t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i][j+t] = temp;
                                break;
                            }else if(matrix[i][j+t] > 0)break;
                        }
                        for(int t = -1;j + t > 0;t --){
                            if(matrix[i][j] == 0){
                                tempMatrix[i][j+t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i][j+t] = Pieces::none;
                            }else if(matrix[i][j+t] < 0){
                                int temp = tempMatrix[i][j+t];
                                tempMatrix[i][j+t] = Pieces::white_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_queen;
                                tempMatrix[i][j+t] = temp;
                                break;
                            }else if(matrix[i][j+t] > 0)break;
                        }
                        break;
                    case 6://rook
                        for(int t = 1;i + t <= 8;t ++){
                            if(matrix[i + t][j] == 0){
                                tempMatrix[i+t][j] = Pieces::white_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_rook;
                                tempMatrix[i+t][j] = Pieces::none;
                            }else if(matrix[i + t][j] < 0){
                                int temp = tempMatrix[i+t][j];
                                tempMatrix[i+t][j] = Pieces::white_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_rook;
                                tempMatrix[i+t][j] = temp;
                                break;
                            }else if(matrix[i + t][j] > 0)break;
                        }
                        for(int t = -1;i + t > 0;t --){
                            if(matrix[i + t][j] == 0){
                                tempMatrix[i+t][j] = Pieces::white_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_rook;
                                tempMatrix[i+t][j] = Pieces::none;
                            }else if(matrix[i + t][j] < 0){
                                int temp = tempMatrix[i+t][j];
                                tempMatrix[i+t][j] = Pieces::white_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_rook;
                                tempMatrix[i+t][j] = temp;
                                break;
                            }else if(matrix[i + t][j] > 0)break;
                        }
                        for(int t = 1;j + t <= 8;t ++){
                            if(matrix[i][j] == 0){
                                tempMatrix[i][j+t] = Pieces::white_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_rook;
                                tempMatrix[i][j+t] = Pieces::none;
                            }else if(matrix[i][j+t] < 0){
                                int temp = tempMatrix[i][j+t];
                                tempMatrix[i][j+t] = Pieces::white_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_rook;
                                tempMatrix[i][j+t] = temp;
                                break;
                            }else if(matrix[i][j+t] > 0)break;
                        }
                        for(int t = -1;j + t > 0;t --){
                            if(matrix[i][j] == 0){
                                tempMatrix[i][j+t] = Pieces::white_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_rook;
                                tempMatrix[i][j+t] = Pieces::none;
                            }else if(matrix[i][j+t] < 0){
                                int temp = tempMatrix[i][j+t];
                                tempMatrix[i][j+t] = Pieces::white_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::white_rook;
                                tempMatrix[i][j+t] = temp;
                                break;
                            }else if(matrix[i][j+t] > 0)break;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }else if(state == 1){
        //王无路可走
        for(int i = -1;i <= 1;i ++){
            for(int j = -1;j <= 1;j ++){
                if(matrix[king_x+i][king_y+j] >= 0 && canWalk(king_x+i,king_y+j)){
                    int temp = tempMatrix[king_x + i][king_y + j];
                    tempMatrix[king_x][king_y] = Pieces::none;
                    tempMatrix[king_x + i][king_y + j] = Pieces::black_king;
                    setAttackMatrix();
                    if(!pointInDanger(king_x+i,king_y+j)){return false;}
                    tempMatrix[king_x+i][king_y+j] = temp;
                    tempMatrix[king_x][king_y] = Pieces::black_king;
                }
            }
        }
        qDebug()<<"wang has no path.";
        //其他兵无路可走
        for(int i = 1;i <= 8;i ++){
            for(int j = 1;j <= 8;j ++){
                if(matrix[i][j] < 0){
                    switch (matrix[i][j]) {
                    case -6://bishop
                        for(int t = 1;i + t <= 8 && j + t <= 8;t++){
                            if(matrix[i + t][j + t] == 0){
                                tempMatrix[i+t][j+t] = Pieces::black_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_bishop;
                                tempMatrix[i+t][j+t] = Pieces::none;
                            }else if(matrix[i + t][j + t] > 0){
                                int temp = tempMatrix[i+t][j+t];
                                tempMatrix[i+t][j+t] = Pieces::black_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_bishop;
                                tempMatrix[i+t][j+t] = temp;
                                break;
                            }else if(matrix[i + t][j + t] < 0)break;
                        }
                        for(int t = 1;i - t > 0 && j - t > 0;t++){
                            if(matrix[i-t][j-t] == 0){
                                tempMatrix[i-t][j-t] = Pieces::black_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_bishop;
                                tempMatrix[i-t][j-t] = Pieces::none;
                            }else if(matrix[i-t][j-t] > 0){
                                int temp = tempMatrix[i-t][j-t];
                                tempMatrix[i-t][j-t] = Pieces::black_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_bishop;
                                tempMatrix[i-t][j-t] = temp;
                                break;
                            }else if(matrix[i-t][j-t] < 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j - t > 0;t++){
                            if(matrix[i+t][j-t] == 0){
                                tempMatrix[i+t][j-t] = Pieces::black_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_bishop;
                                tempMatrix[i+t][j-t] = Pieces::none;
                            }else if(matrix[i+t][j-t] > 0){
                                int temp = tempMatrix[i+t][j-t];
                                tempMatrix[i+t][j-t] = Pieces::black_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_bishop;
                                tempMatrix[i+t][j-t] = temp;
                                break;
                            }else if(matrix[i+t][j-t] < 0)break;
                        }
                        for(int t = 1;i - t > 0 && j + t <= 8;t++){
                            if(matrix[i-t][j+t] == 0){
                                tempMatrix[i-t][j+t] = Pieces::black_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_bishop;
                                tempMatrix[i-t][j+t] = Pieces::none;
                            }else if(matrix[i-t][j+t] > 0){
                                int temp = tempMatrix[i-t][j+t];
                                tempMatrix[i-t][j+t] = Pieces::black_bishop;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_bishop;
                                tempMatrix[i-t][j+t] = temp;
                                break;
                            }else if(matrix[i-t][j+t] < 0)break;
                        }
                        break;
                    case -4://knight
                        if(matrix[i + 1][j + 2] >= 0 && canWalk(i+1,j+2)){
                            int temp = tempMatrix[i+1][j+2];
                            tempMatrix[i+1][j+2] = Pieces::black_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_knight;
                            tempMatrix[i+1][j+2] = temp;
                        }
                        if(matrix[i + 1][j - 2] >= 0 && canWalk(i+1,j-2)){
                            int temp = tempMatrix[i+1][j-2];
                            tempMatrix[i+1][j-2] = Pieces::black_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_knight;
                            tempMatrix[i+1][j-2] = temp;
                        }
                        if(matrix[i - 1][j + 2] >= 0 && canWalk(i-1,j+2)){
                            int temp = tempMatrix[i-1][j+2];
                            tempMatrix[i-1][j+2] = Pieces::black_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_knight;
                            tempMatrix[i-1][j+2] = temp;
                        }
                        if(matrix[i - 1][j - 2] >= 0 && canWalk(i-1,j-2)){
                            int temp = tempMatrix[i-1][j-2];
                            tempMatrix[i-1][j-2] = Pieces::black_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_knight;
                            tempMatrix[i-1][j-2] = temp;
                        }
                        if(matrix[i + 2][j + 1] >= 0 && canWalk(i+2,j+1)){
                            int temp = tempMatrix[i+2][j+1];
                            tempMatrix[i+2][j+1] = Pieces::black_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_knight;
                            tempMatrix[i+2][j+1] = temp;
                        }
                        if(matrix[i + 2][j - 1] >= 0 && canWalk(i+2,j-1)){
                            int temp = tempMatrix[i+2][j-1];
                            tempMatrix[i+2][j-1] = Pieces::black_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_knight;
                            tempMatrix[i+2][j-1] = temp;
                        }
                        if(matrix[i - 2][j + 1] >= 0 && canWalk(i-2,j+1)){
                            int temp = tempMatrix[i-2][j+1];
                            tempMatrix[i-2][j+1] = Pieces::black_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_knight;
                            tempMatrix[i-2][j+1] = temp;
                        }
                        if(matrix[i - 2][j - 1] >= 0 && canWalk(i-2,j-1)){
                            int temp = tempMatrix[i-2][j-1];
                            tempMatrix[i-2][j-1] = Pieces::black_knight;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_knight;
                            tempMatrix[i-2][j-1] = temp;
                        }
                        break;
                    case -3://pawn
                        if(matrix[i - 1][j + 1] > 0 && canWalk(i-1,j+1)){
                            int temp = tempMatrix[i+1][j+1];
                            tempMatrix[i-1][j+1] = Pieces::black_pawn;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_pawn;
                            tempMatrix[i-1][j+1] = temp;
                        }
                        if(matrix[i - 1][j - 1] > 0 && canWalk(i-1,j-1)){
                            int temp = tempMatrix[i+1][j-1];
                            tempMatrix[i-1][j-1] = Pieces::black_pawn;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_pawn;
                            tempMatrix[i-1][j-1] = temp;
                        }
                        if(matrix[i - 1][j] == 0 && canWalk(i-1,j)){
                            int temp = tempMatrix[i-1][j];
                            tempMatrix[i-1][j] = Pieces::black_pawn;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_pawn;
                            tempMatrix[i-1][j] = temp;
                        }
                        if(i == 2 && matrix[i-1][j] == 0 && matrix[i-2][j] == 0 && canWalk(i-2,j)){
                            int temp = tempMatrix[i-2][j];
                            tempMatrix[i-2][j] = Pieces::black_pawn;
                            tempMatrix[i][j] = Pieces::none;
                            setAttackMatrix();
                            if(!pointInDanger(king_x,king_y))return false;
                            tempMatrix[i][j] = Pieces::black_pawn;
                            tempMatrix[i-2][j] = temp;
                        }
                        break;
                    case -2://queen
                        for(int t = 1;i + t <= 8 && j + t <= 8;t++){
                            if(matrix[i + t][j + t] == 0){
                                tempMatrix[i+t][j+t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i+t][j+t] = Pieces::none;
                            }else if(matrix[i + t][j + t] > 0){
                                int temp = tempMatrix[i+t][j+t];
                                tempMatrix[i+t][j+t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i+t][j+t] = temp;
                                break;
                            }else if(matrix[i + t][j + t] < 0)break;
                        }
                        for(int t = 1;i - t > 0 && j - t > 0;t++){
                            if(matrix[i-t][j-t] == 0){
                                tempMatrix[i-t][j-t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i-t][j-t] = Pieces::none;
                            }else if(matrix[i-t][j-t] > 0){
                                int temp = tempMatrix[i-t][j-t];
                                tempMatrix[i-t][j-t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i-t][j-t] = temp;
                                break;
                            }else if(matrix[i-t][j-t] < 0)break;
                        }
                        for(int t = 1;i + t <= 8 && j - t > 0;t++){
                            if(matrix[i+t][j-t] == 0){
                                tempMatrix[i+t][j-t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i+t][j-t] = Pieces::none;
                            }else if(matrix[i+t][j-t] > 0){
                                int temp = tempMatrix[i+t][j-t];
                                tempMatrix[i+t][j-t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i+t][j-t] = temp;
                                break;
                            }else if(matrix[i+t][j-t] < 0)break;
                        }
                        for(int t = 1;i - t > 0 && j + t <= 8;t++){
                            if(matrix[i-t][j+t] == 0){
                                tempMatrix[i-t][j+t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i-t][j+t] = Pieces::none;
                            }else if(matrix[i-t][j+t] > 0){
                                int temp = tempMatrix[i-t][j+t];
                                tempMatrix[i-t][j+t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i-t][j+t] = temp;
                                break;
                            }else if(matrix[i-t][j+t] < 0)break;
                        }
                        for(int t = 1;i + t <= 8;t ++){
                            if(matrix[i + t][j] == 0){
                                tempMatrix[i+t][j] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i+t][j] = Pieces::none;
                            }else if(matrix[i + t][j] > 0){
                                int temp = tempMatrix[i+t][j];
                                tempMatrix[i+t][j] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i+t][j] = temp;
                                break;
                            }else if(matrix[i + t][j] < 0)break;
                        }
                        for(int t = -1;i + t > 0;t --){
                            if(matrix[i + t][j] == 0){
                                tempMatrix[i+t][j] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i+t][j] = Pieces::none;
                            }else if(matrix[i + t][j] > 0){
                                int temp = tempMatrix[i+t][j];
                                tempMatrix[i+t][j] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i+t][j] = temp;
                                break;
                            }else if(matrix[i + t][j] < 0)break;
                        }
                        for(int t = 1;j + t <= 8;t ++){
                            if(matrix[i][j] == 0){
                                tempMatrix[i][j+t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i][j+t] = Pieces::none;
                            }else if(matrix[i][j+t] > 0){
                                int temp = tempMatrix[i][j+t];
                                tempMatrix[i][j+t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i][j+t] = temp;
                                break;
                            }else if(matrix[i][j+t] < 0)break;
                        }
                        for(int t = -1;j + t > 0;t --){
                            if(matrix[i][j] == 0){
                                tempMatrix[i][j+t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i][j+t] = Pieces::none;
                            }else if(matrix[i][j+t] > 0){
                                int temp = tempMatrix[i][j+t];
                                tempMatrix[i][j+t] = Pieces::black_queen;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_queen;
                                tempMatrix[i][j+t] = temp;
                                break;
                            }else if(matrix[i][j+t] < 0)break;
                        }
                        break;
                    case -1://rook
                        for(int t = 1;i + t <= 8;t ++){
                            if(matrix[i + t][j] == 0){
                                tempMatrix[i+t][j] = Pieces::black_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_rook;
                                tempMatrix[i+t][j] = Pieces::none;
                            }else if(matrix[i + t][j] > 0){
                                int temp = tempMatrix[i+t][j];
                                tempMatrix[i+t][j] = Pieces::black_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_rook;
                                tempMatrix[i+t][j] = temp;
                                break;
                            }else if(matrix[i + t][j] < 0)break;
                        }
                        for(int t = -1;i + t > 0;t --){
                            if(matrix[i + t][j] == 0){
                                tempMatrix[i+t][j] = Pieces::black_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_rook;
                                tempMatrix[i+t][j] = Pieces::none;
                            }else if(matrix[i + t][j] > 0){
                                int temp = tempMatrix[i+t][j];
                                tempMatrix[i+t][j] = Pieces::black_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_rook;
                                tempMatrix[i+t][j] = temp;
                                break;
                            }else if(matrix[i + t][j] < 0)break;
                        }
                        for(int t = 1;j + t <= 8;t ++){
                            if(matrix[i][j] == 0){
                                tempMatrix[i][j+t] = Pieces::black_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_rook;
                                tempMatrix[i][j+t] = Pieces::none;
                            }else if(matrix[i][j+t] > 0){
                                int temp = tempMatrix[i][j+t];
                                tempMatrix[i][j+t] = Pieces::black_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_rook;
                                tempMatrix[i][j+t] = temp;
                                break;
                            }else if(matrix[i][j+t] < 0)break;
                        }
                        for(int t = -1;j + t > 0;t --){
                            if(matrix[i][j] == 0){
                                tempMatrix[i][j+t] = Pieces::black_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_rook;
                                tempMatrix[i][j+t] = Pieces::none;
                            }else if(matrix[i][j+t] > 0){
                                int temp = tempMatrix[i][j+t];
                                tempMatrix[i][j+t] = Pieces::black_rook;
                                tempMatrix[i][j] = Pieces::none;
                                setAttackMatrix();
                                if(!pointInDanger(king_x,king_y))return false;
                                tempMatrix[i][j] = Pieces::black_rook;
                                tempMatrix[i][j+t] = temp;
                                break;
                            }else if(matrix[i][j+t] < 0)break;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        qDebug()<<"other have no path.";
    }
    return true;
}

void MainWindow::winMessage()
{
    QString about_title = "WIN!";
    QString about_info = "You WIN!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    inGame = false;
    timer->stop();
    waittime = 0;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void MainWindow::loseMessage()
{
    QString about_title = "LOSE!";
    QString about_info = "You LOSE!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    inGame = false;
    timer->stop();
    waittime = 0;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void MainWindow::drawnMessage()
{
    QString about_title = "DRAWN!";
    QString about_info = "逼和!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    QByteArray temp = "0.2.0.0";
    if(haveConnected){
        if(state == 0)this->serverreadWriteSocket->write(temp.data());
        else if(state == 1)this->clientreadWriteSocket->write(temp.data());
    }
    inGame = false;
    timer->stop();
    waittime = 0;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void MainWindow::overtimeMessage()
{
    QString about_title = "Time out";
    QString about_info = "The time is out.You LOSE!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton; 
    QByteArray temp = "0.1.0.0";
    if(haveConnected){
        if(state == 0)this->serverreadWriteSocket->write(temp.data());
        else if(state == 1)this->clientreadWriteSocket->write(temp.data());
    }
    inGame = false;
    timer->stop();
    waittime = 0;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void MainWindow::giveUpMessage()
{
    QString title = "Confirm";
    QString info = "Do you want to give up?";
    int temp = QMessageBox::question(this,title,info,QMessageBox::Yes,QMessageBox::No);
    if(temp == QMessageBox::Yes){
        QByteArray temp_send = "0.0.0.0";
        if(haveConnected){
            if(state == 0)serverreadWriteSocket->write(temp_send.data());
            if(state == 1)clientreadWriteSocket->write(temp_send.data());
        }
        inGame = false;
        timer->stop();
        waittime = 0;
    }
}

void MainWindow::anotherGiveUpMessage()
{
    QString about_title = "You WIN";
    QString about_info = "The Other Side has give up.You WIN!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;  
    inGame = false;
    timer->stop();
    waittime = 0;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void MainWindow::openFile()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = tr("Open a File");
    QString filiter = "Text(*.txt);;All(*.*)";
    QString FileName = QFileDialog::getOpenFileName(this,dlgTitle,curPath,filiter);
    if(FileName.isEmpty())return ;
    timer->stop();
    if(readFile(FileName)){
        QMessageBox::information(this,"Success","Read File Successfully.");
    }
}

bool MainWindow::readFile(const QString &fileName)
{
    haveRead = true;
    for(int i = 1;i <= 8;i ++){
        for(int j = 1;j <= 8;j ++){
            matrix[i][j] = 0;
        }
    }
    QFile aFile(fileName);
    if(!aFile.exists())return false;
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text))return false;
    QTextStream aStream(&aFile);//用文本流读取文件，将aFile和aStream捆绑起来，便于应用aStream的强大功能
    aStream.setAutoDetectUnicode(true);//自动读取unicode编码字符
    QString str;
    bool haveset = false;
    while(!aStream.atEnd()){
        str = aStream.readLine();
        if(str == "white"){if(state == 0){isOnCharge = true;haveset = true;}}
        else if(str == "black"){if(state == 1 && (!haveset)){isOnCharge = true;}break;}
        else{
            QList<QString> list = str.split(" ");
            if(list[0] == "bishop"){
                for(int i = 2;i < list.size();i++){
                    matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_bishop;
                }
            }else if(list[0] == "king"){
                for(int i = 2;i < list.size();i++){
                    matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_king;
                    if(state == 0){king_x = list[i][1].toLatin1() - '0';king_y = list[i][0].toLatin1() - 'a' + 1;}
                }
            }else if(list[0] == "knight"){
                for(int i = 2;i < list.size();i++){
                    matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_knight;
                }
            }else if(list[0] == "pawn"){
                for(int i = 2;i < list.size();i++){
                    matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_pawn;
                }
            }else if(list[0] == "queen"){
                for(int i = 2;i < list.size();i++){
                    matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_queen;
                }
            }else if(list[0] == "rook"){
                for(int i = 2;i < list.size();i++){
                    matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_rook;
                }
            }
        }
    }
    while(!aStream.atEnd()){
        str = aStream.readLine();
        if(str == "white")break;
        QList<QString> list = str.split(" ");
        if(list[0] == "bishop"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::black_bishop;
            }
        }else if(list[0] == "king"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::black_king;
                if(state == 1){king_x = list[i][1].toLatin1() - '0';king_y = list[i][0].toLatin1() - 'a' + 1;}
            }
        }else if(list[0] == "knight"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::black_knight;
            }
        }else if(list[0] == "pawn"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::black_pawn;
            }
        }else if(list[0] == "queen"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::black_queen;
            }
        }else if(list[0] == "rook"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::black_rook;
            }
        }
    }
    while(!aStream.atEnd()){
        str = aStream.readLine();
        QList<QString> list = str.split(" ");
        if(list[0] == "bishop"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_bishop;
            }
        }else if(list[0] == "king"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_king;
                if(state == 0){king_x = list[i][1].toLatin1() - '0';king_y = list[i][0].toLatin1() - 'a' + 1;}
            }
        }else if(list[0] == "knight"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_knight;
            }
        }else if(list[0] == "pawn"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_pawn;
            }
        }else if(list[0] == "queen"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_queen;
            }
        }else if(list[0] == "rook"){
            for(int i = 2;i < list.size();i++){
                matrix[list[i][1].toLatin1() - '0'][list[i][0].toLatin1() - 'a' + 1] = Pieces::white_rook;
            }
        }
    }
    resetDanger();
    resetWalkable();
    setTempMatrix();
    waittime = 0;
    timer->stop();
    inGame = false;
    this->repaint();
    return true;
}

void MainWindow::saveFile()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = tr("Save your File");
    QString filter = "Text(*.txt);;All(*.*)";
    QString FileName = QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if(FileName.isEmpty()) return ;
    //timer->stop();
    //waittime = 0;
    if(writeFile(FileName)){
        QMessageBox::information(this,"Succecs","Save File Succecsfully.");
    }
}

bool MainWindow::writeFile(const QString &fileName)
{
    QFile aFile(fileName);
    if(!aFile.open(QIODevice::WriteOnly | QIODevice::Text))return false;
    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);//自动读取unicode编码字符
    //b_b = 7;b_k = 8;b_kni = 9;b_p = 10;b_q = 11;b_r = 12;
    //w_b = 1;w_k = 2;w_kni = 3;w_p = 4;w_q = 5;w_r = 6;

    int loc[15][10][2];//存放位置
    int pie[15] = {0};//存放个数
    for(int i = 1;i <= 8;i++){
        for(int j = 1;j <= 8;j ++){
            if(matrix[i][j] != 0){
                switch (matrix[i][j]) {
                case Pieces::white_king://2
                    loc[2][pie[2]][0] = j;loc[2][pie[2]][1] = i;pie[2]++;
                    break;
                case Pieces::white_pawn://4
                    loc[4][pie[4]][0] = j;loc[4][pie[4]][1] = i;pie[4]++;
                    break;
                case Pieces::white_rook://6
                    loc[6][pie[6]][0] = j;loc[6][pie[6]][1] = i;pie[6]++;
                    break;
                case Pieces::white_queen://5
                    loc[5][pie[5]][0] = j;loc[5][pie[5]][1] = i;pie[5]++;
                    break;
                case Pieces::white_bishop://1
                    loc[1][pie[1]][0] = j;loc[1][pie[1]][1] = i;pie[1]++;
                    break;
                case Pieces::white_knight://3
                    loc[3][pie[3]][0] = j;loc[3][pie[3]][1] = i;pie[3]++;
                    break;
                case Pieces::black_king://8
                    loc[8][pie[8]][0] = j;loc[8][pie[8]][1] = i;pie[8]++;
                    break;
                case Pieces::black_pawn://10
                    loc[10][pie[10]][0] = j;loc[10][pie[10]][1] = i;pie[10]++;
                    break;
                case Pieces::black_rook://12
                    loc[12][pie[12]][0] = j;loc[12][pie[12]][1] = i;pie[12]++;
                    break;
                case Pieces::black_queen://11
                    loc[11][pie[11]][0] = j;loc[11][pie[11]][1] = i;pie[11]++;
                    break;
                case Pieces::black_bishop://7
                    loc[7][pie[7]][0] = j;loc[7][pie[7]][1] = i;pie[7]++;
                    break;
                case Pieces::black_knight://9
                    loc[9][pie[9]][0] = j;loc[9][pie[9]][1] = i;pie[9]++;
                    break;
                default:
                    break;
                }
            }
        }
    }

    QString str;
    aStream<<"white"<<"\n";
    for(int i = 1;i <= 6;i++){
        switch (i) {
        case 1:
            if(pie[i] > 0){
                aStream<<"bishop "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1])<<" ";
                }
                aStream<<"\n";
            }
            break;
        case 2:
            if(pie[i] > 0){
                aStream<<"king "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            aStream<<"\n";
            break;
        case 3:
            if(pie[i] > 0){
                aStream<<"knight "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            aStream<<"\n";
            break;
        case 4:
            if(pie[i] > 0){
                aStream<<"pawn "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            aStream<<"\n";
            break;
        case 5:
            if(pie[i] > 0){
                aStream<<"queen "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            aStream<<"\n";
            break;
        case 6:
            if(pie[i] > 0){
                aStream<<"rook "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            aStream<<"\n";
            break;
        }
    }
    aStream<<"black"<<"\n";
    for(int i = 7;i <= 12;i ++){
        switch (i) {
        case 7:
            if(pie[i] > 0){
                aStream<<"bishop "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1])<<" ";
                }
                aStream<<"\n";
            }
            break;
        case 8:
            if(pie[i] > 0){
                aStream<<"king "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            aStream<<"\n";
            break;
        case 9:
            if(pie[i] > 0){
                aStream<<"knight "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            aStream<<"\n";
            break;
        case 10:
            if(pie[i] > 0){
                aStream<<"pawn "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            aStream<<"\n";
            break;
        case 11:
            if(pie[i] > 0){
                aStream<<"queen "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            aStream<<"\n";
            break;
        case 12:
            if(pie[i] > 0){
                aStream<<"rook "<<QString::number(pie[i]);
                for(int j = 0;j < pie[i];j ++){
                    aStream<<" "<<numtoLetter(loc[i][j][0])<<QString::number(loc[i][j][1]);
                }
            }
            //aStream<<"\n";
            break;
        }
    }
    aFile.close();
    return true;
}

QString MainWindow::numtoLetter(const int &num)
{
    QString str;
    switch (num) {
    case 1:
        str = "a";
        break;
    case 2:
        str = "b";
        break;
    case 3:
        str = "c";
        break;
    case 4:
        str = "d";
        break;
    case 5:
        str = "e";
        break;
    case 6:
        str = "f";
        break;
    case 7:
        str = "g";
        break;
    case 8:
        str = "h";
        break;
    }
    return str;
}

int MainWindow::lettertoNum(const QString &str)
{
    if(str == "a"){
        return 1;
    }else if(str == "b"){
        return 2;
    }else if(str == "c"){
        return 3;
    }else if(str == "d"){
        return 4;
    }else if(str == "e"){
        return 5;
    }else if(str == "f"){
        return 6;
    }else if(str == "g"){
        return 7;
    }else if(str == "h"){
        return 8;
    }
    return 0;
}

void MainWindow::missLinkMessage()
{
    QString about_title = "Link Time Out";
    QString about_info = "Fail to Link to Server.";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    linkTimer->stop();
    this->haveConnected = false;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
    createLink->show();
}

void MainWindow::linkSuccess()
{
    QString about_title = "Success!";
    QString about_info = "Success to Link to Server.";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    linkTimer->stop();
    this->haveConnected = true;
    if(haveConnected){
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        setState(1);
    }
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void MainWindow::pawnPromotion(int num)
{
    if(state == 0){
        matrix[cur_x][cur_y] = num;
        QString str = QString::number(num) + "." + QString::number(last_x) + "." + QString::number(last_y) + "." + QString::number(cur_x) + "." + QString::number(cur_y);
        QByteArray arr = str.toLocal8Bit();
        if(haveConnected)this->serverreadWriteSocket->write(arr);
    }else if(state == 1){
        matrix[cur_x][cur_y] = -num;
        QString str = QString::number(-num) + "." + QString::number(last_x) + "." + QString::number(last_y) + "." + QString::number(cur_x) + "." + QString::number(cur_y);
        QByteArray arr = str.toLocal8Bit();
        if(haveConnected)this->serverreadWriteSocket->write(arr);
    }
    this->repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    createLink->show();
}

void MainWindow::on_pushButton_clicked()
{
    createhost->show();
}

void MainWindow::receiveMessage()
{
    qDebug()<<"server received";
    order_receive = this->serverreadWriteSocket->readAll();
    ui->HintLabel->setText(order_receive);
    QList<QString> strlist = order_receive.split(".");
    qDebug()<<strlist;
    if(strlist[0] == "start"){
        timer->start();
        if(!haveRead)inimatrix();
        resetDanger();
        resetWalkable();
        this->repaint();
        waittime = 0;
        ui->lineEdit->setText("WHITE");
        isOnCharge = true;
        inGame = true;
    }else if(strlist[0] == "restart"){
        haveRead = false;
        inimatrix();
        resetDanger();
        resetWalkable();
        waittime = 0;
        king_x = 1;king_y = 5;
        timer->stop();
        inGame = false;
    }else{
        if(strlist[0].toInt() != 0){
            if(matrix[strlist[3].toInt()][strlist[4].toInt()] == Pieces::white_king){
                loseMessage();
            }
            matrix[strlist[1].toInt()][strlist[2].toInt()] = 0;
            matrix[strlist[3].toInt()][strlist[4].toInt()] = strlist[0].toInt();
            if(strlist.size() == 10){
                matrix[strlist[6].toInt()][strlist[7].toInt()] = 0;
                matrix[strlist[8].toInt()][strlist[9].toInt()] = strlist[5].toInt();
            }
        }
        ui->lineEdit->setText("WHITE");
        isOnCharge = true;
        //如果第一个是0.0,就认为对方是认输。0.1为对方因为输棋 或 超时。 0.2为逼和
        if(strlist[0].toInt() == 0 && strlist[1].toInt() == 0){
            inGame = false;
            anotherGiveUpMessage();
        }else if(strlist[0].toInt() == 0&& strlist[1].toInt() == 1){//对方输棋或超时
            inGame = false;
            timer->stop();
            waittime = 0;
        }else if(strlist[0].toInt() == 0 && strlist[1].toInt() == 2){//逼和
            inGame = false;
            timer->stop();
            waittime = 0;
            QMessageBox::information(this,"DRAWN","逼和！");
        }
        waittime = 0;
    }
    this->repaint();
    if(stalemate()){
        drawnMessage();
    }
}

void MainWindow::acceptConnection()
{
    qDebug()<<"accept connection.";
    //发出第二次握手，接受第三次握手，返回QTcpSocket套接字，该套接字是QTcpServer的子对象
    this->serverreadWriteSocket =this->listenSocket->nextPendingConnection();
    //接受发送请求之后接受信息
    QObject::connect(this->serverreadWriteSocket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
}

void MainWindow::clientReceiveMessage()
{
    qDebug()<<"client received";
    order_receive = this->clientreadWriteSocket->readAll();
    QList<QString> strlist = order_receive.split(".");
    qDebug()<<strlist;
    if(strlist[0] == "start"){
        timer->start();
        if(!haveRead)inimatrix();
        resetDanger();
        resetWalkable();
        this->repaint();
        waittime = 0;
        ui->lineEdit->setText("WHITE");
        isOnCharge = false;
        inGame = true;
   }else if(strlist[0] == "restart"){
        haveRead = false;
        inimatrix();
        resetDanger();
        resetWalkable();
        setTempMatrix();
        king_x = 8;king_y = 5;
        waittime = 0;
        timer->stop();
        inGame = false;
   }else{
        if(strlist[0].toInt() != 0){
            if(matrix[strlist[3].toInt()][strlist[4].toInt()] == Pieces::black_king){
                loseMessage();
            }
            matrix[strlist[1].toInt()][strlist[2].toInt()] = 0;
            matrix[strlist[3].toInt()][strlist[4].toInt()] = strlist[0].toInt();
            if(strlist.size() == 10){
                matrix[strlist[6].toInt()][strlist[7].toInt()] = 0;
                matrix[strlist[8].toInt()][strlist[9].toInt()] = strlist[5].toInt();
            }
        }
        ui->lineEdit->setText("BLACK");
        isOnCharge = true;
        //如果第一个是0.0,就认为对方是认输。0.1为对方因为输棋 或 超时。 0.2为逼和
        if(strlist[0].toInt() == 0 && strlist[1].toInt() == 0){
            inGame = false;
            anotherGiveUpMessage();
        }else if(strlist[0].toInt() == 0 && strlist[1].toInt() == 1){//对方输棋或超时
            inGame = false;
            timer->stop();
            waittime = 0;
        }else if(strlist[0].toInt() == 0 && strlist[1].toInt() == 2){//逼和
            inGame = false;
            timer->stop();
            waittime = 0;
            QMessageBox::information(this,"DRAWN","逼和！");
        }
        waittime = 0;
    }
    this->repaint();
    if(stalemate()){
        drawnMessage();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    giveUpMessage();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString str = "start";
    QByteArray array = str.toUtf8();
    if(!haveRead)inimatrix();
    resetDanger();
    resetWalkable();
    waittime = 0;
    if(haveConnected){
        if(state == 0){
            this->serverreadWriteSocket->write(array.data());
        }else if(state == 1){
            this->clientreadWriteSocket->write(array.data());
        }
    }
    timer->start();
    isOnCharge = true;
    inGame = true;
    ui->lineEdit->setText("WHITE");
    this->repaint();
}

void MainWindow::on_pushButton_4_clicked()
{
    if(inGame){
        saveFile();
    }else{
        QMessageBox::warning(this,"Error","You haven't begun a game!");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    openFile();
}

void MainWindow::on_pushButton_7_clicked()
{
    QString str = "restart";
    QByteArray array = str.toUtf8();
    haveRead = false;
    inimatrix();
    resetDanger();
    resetWalkable();
    setTempMatrix();
    waittime = 0;
    timer->stop();
    inGame = false;
    if(state == 1){king_x = 8;king_y = 5;}
    else if(state == 0){king_x = 1;king_y = 5;}
    if(haveConnected){
        if(state == 0){
            this->serverreadWriteSocket->write(array.data());
        }else if(state == 1){
            this->clientreadWriteSocket->write(array.data());
        }
    }
    this->repaint();
}

void MainWindow::on_actionCreate_Host_triggered()
{
    on_pushButton_clicked();
}

void MainWindow::on_actionCreate_Link_triggered()
{
    on_pushButton_2_clicked();
}

void MainWindow::on_actionLoad_File_triggered()
{
    on_pushButton_3_clicked();
}

void MainWindow::on_actionSave_File_triggered()
{
    on_pushButton_4_clicked();
}
