#include "biochip.h"
#include "ui_biochip.h"

BioChip::BioChip(QWidget *parent) :
    QWidget(parent),
    widget_size(250),
    ui(new Ui::BioChip)
{
    ui->setupUi(this);
    isSetted = false;
    matrixset = false;
    cleaner_on = false;
    cleaner_doing = false;
    cleaner_done = true;
    pollutionError = false;
    have_reached_final = false;
    barrierPos.clear();
    pollutionList.clear();
    washer.reset();
    fTimer = new QTimer(this);
    fTimer->stop();


    rootPath = QCoreApplication::applicationDirPath();
    musicPath = rootPath + "\\audio\\";
    setSoundPath();

    curtime = 0;
    dropNum = 0;
    errorInputTime = -2;
    errorOutputTime = -2;
    errorStaticTime = -2;
    errorDynamicTime = -2;
    errorPollutionTime = -2;
    errorSolved = true;
    errorHappened = false;
    beforeError = true;
    paintPollution = false;

    begin_x = parent->geometry().x() + 250 ;
    begin_y = parent->geometry().y() + 100;
    fTimer->setInterval(500);

    connect(fTimer,SIGNAL(timeout()),this,SLOT(updateChip()));

    //framerate = 20;
}

BioChip::~BioChip()
{
    delete ui;
}

void BioChip::setRow(int r)
{
    this->row = r;
}

void BioChip::setColumn(int c)
{
    this->column = c;
}

void BioChip::setWidth(int w)
{
    this->width = w;
}

void BioChip::setGate(QList<int> inp, int out_x, int out_y)
{
    this->input = inp;
    this->output_x = out_x;
    this->output_y = out_y;
    isSetted = true;
}

void BioChip::setSoundPath()
{
    this->move_sound = new QSound(musicPath + "move.wav",this);
    this->merge_sound = new QSound(musicPath + "merge.wav",this);
    this->split_finish_sound = new QSound(musicPath + "Split_finish.wav",this);
    this->split_strech_sound = new QSound(musicPath + "Split_stretch.wav",this);
    this->background_sound = new QSound(musicPath + "background.wav",this);
}

void BioChip::showWorngInputMessage()
{
    QString about_title = "Wrong Input!";
    QString about_info = "The drop must appear near the input gate!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void BioChip::showWrongOutputMessage()
{
    QString about_title = "Wrong Output!";
    QString about_info = "The drop must disappear near the output gate!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

bool BioChip::showErrorMessage()
{
    if(curtime == errorInputTime && errorSolved == false){
        fTimer->stop();
        errorSolved = true;
        errorHappened = true;
        stopTime = curtime;
        showWorngInputMessage();
        //matrixset = false;
    }else if(curtime == errorOutputTime && errorSolved == false){
        fTimer->stop();
        errorSolved = true;
        errorHappened = true;
        stopTime = curtime;
        //MatrixPaintEvent(paint,curtime);
        showWrongOutputMessage();
        //matrixset = false;
    }else if(curtime == errorStaticTime && errorSolved == false){
        fTimer->stop();
        errorSolved = true;
        errorHappened = true;
        stopTime = curtime;
        //MatrixPaintEvent(paint,curtime);
        showStaticErrorMessage();
    }else if(curtime == errorDynamicTime && errorSolved == false){
        fTimer->stop();
        errorSolved = true;
        errorHappened = true;
        //MatrixPaintEvent(paint,curtime - 1);
        stopTime = curtime;
        showDynamicErrorMessage();
    }
    return errorHappened;
}

void BioChip::showStaticErrorMessage()
{
    QString about_title = "Static Error!";
    QString about_info = "The drop move must obey the static condition!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void BioChip::showDynamicErrorMessage()
{
    QString about_title = "Dynamic Error!";
    QString about_info = "The drop move must obey the dynamic condition!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void BioChip::showPollutionErrorMessage()
{
    QString about_title = "Pollution Happened!";
    QString about_info = "The drop is polluted in this step.";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

bool BioChip::compare(const pollutionEvent &p1, const pollutionEvent &p2)
{
    return p1.t2 < p2.t2;
}

void BioChip::getSubMatrix()
{

    for(int t = 0;t < 100;t++){
        for(int i = 0;i < 18;i ++){
            for(int j = 0;j < 18;j ++){
                sub_matrix[t][i][j] = matrix[t][i][j];
            }
        }
    }
}

void BioChip::getSubDropState()
{
    for(int t = 0;t < 20;t++){
        for(int i = 0;i < 100;i ++){
            for(int j = 0;j < 3;j ++){
                sub_dropState[t][i][j] = dropState[t][i][j];
            }
        }
    }
}

void BioChip::getBarrierMatrix()
{
    for(int i = 0;i < 100;i ++){
        for(int j = 0;j < 18;j ++){
            for(int t = 0;t < 18;t ++){
                sub_barrierMatrix[i][j][t] = barrierMatrix[i][j][t];
            }
        }
    }
}

void BioChip::gettimeStartEnd()
{
    for(int i = 0;i < 50;i ++){
        for(int j = 0;j < 5;j ++){
            sub_timeStarEnd[i][j] = timeStartEnd[i][j];
        }
    }
}

void BioChip::resetMatrix()
{
    for(int t = 0;t < 100;t++){
        for(int i = 0;i < 18;i ++){
            for(int j = 0;j < 18;j ++){
                matrix[t][i][j] = sub_matrix[t][i][j];
            }
        }
    }
}

void BioChip::resetDropState()
{
    for(int t = 0;t < 20;t++){
        for(int i = 0;i < 100;i ++){
            for(int j = 0;j < 3;j ++){
                dropState[t][i][j] = sub_dropState[t][i][j];
            }
        }
    }
}

void BioChip::resetBarrierMatrix()
{
    for(int i = 0;i < 100;i ++){
        for(int j = 0;j < 18;j ++){
            for(int t = 0;t < 18;t ++){
                barrierMatrix[i][j][t] = sub_barrierMatrix[i][j][t];
            }
        }
    }
}

void BioChip::resettimeStartEnd()
{
    for(int i = 0;i < 50;i ++){
        for(int j = 0;j < 5;j ++){
            timeStartEnd[i][j] = sub_timeStarEnd[i][j];
        }
    }
}

void BioChip::changePath()
{
    if(cleaner_on && cleaner_doing){
        QList<Washdrop>::Iterator iter;
        QList<Washdrop>::Iterator subiter;
        iter = washer.getOnMove(curtime);
        int lastTotTime = iter->getTottime();
        int startTime = iter->getStarttime();

        bool flag = iter->changePath(barrierMatrix[curtime],curtime,row,column);
        if(!flag){
            emit noPath();
        }else{
            int newtotcleanTime = iter->getTottime();
            for(subiter = this->washer.washdropList.begin();subiter != this->washer.washdropList.end();subiter ++){
                if(subiter->getStarttime() > curtime && subiter != iter)subiter->setStartTime(subiter->getStarttime() - lastTotTime + newtotcleanTime);
            }
            int interval = newtotcleanTime - lastTotTime;
            totTime += interval;
            totcleantime += interval;
            if(errorOutputTime > curtime)errorOutputTime += interval;
            if(errorInputTime > curtime)errorInputTime += interval;
            if(errorStaticTime > curtime)errorStaticTime += interval;
            if(errorDynamicTime > curtime)errorDynamicTime += interval;

            if(interval > 0){
                for(int n = 1;n <= dropNum;n ++){
                    if(curtime <= dropState[n][0][2])dropState[n][0][2] += interval;
                    for(int m = totTime;m >= startTime + newtotcleanTime;m -- ){
                        dropState[n][m][0] = dropState[n][m - interval][0];
                        dropState[n][m][1] = dropState[n][m - interval][1];
                    }
                    for(int t = curtime + 1;t < startTime + newtotcleanTime;t ++){
                        dropState[n][t][0] = dropState[n][curtime][0];
                        dropState[n][t][1] = dropState[n][curtime][1];
                    }
                }
                for(int m = totTime;m >= startTime + newtotcleanTime;m --){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            matrix[m][i][j] = matrix[m - interval][i][j];
                            matrix[m][i][j] = matrix[m - interval][i][j];
                        }
                    }
                }
                for(int t = curtime + 1;t < startTime + newtotcleanTime;t ++){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            matrix[t][i][j] = matrix[curtime][i][j];
                            matrix[t][i][j] = matrix[curtime][i][j];
                        }
                    }
                }
                for(int m = totTime;m >= startTime + newtotcleanTime;m --){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            barrierMatrix[m][i][j] = barrierMatrix[m - interval][i][j];
                            barrierMatrix[m][i][j] = barrierMatrix[m - interval][i][j];
                        }
                    }
                }
                for(int t = curtime + 1;t < startTime + newtotcleanTime;t ++){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            barrierMatrix[t][i][j] = barrierMatrix[curtime][i][j];
                            barrierMatrix[t][i][j] = barrierMatrix[curtime][i][j];
                        }
                    }
                }
            }else if(interval < 0){
                for(int n = 1;n <= dropNum;n ++){
                    if(curtime <= dropState[n][0][2])dropState[n][0][2] += interval;
                    for(int m = startTime + totcleantime;m <= totTime;m ++ ){
                        dropState[n][m][0] = dropState[n][m - interval][0];
                        dropState[n][m][1] = dropState[n][m - interval][1];
                    }
                }
                for(int m = startTime + totcleantime;m <= totTime;m ++){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            matrix[m][i][j] = matrix[m - interval][i][j];
                            matrix[m][i][j] = matrix[m - interval][i][j];
                        }
                    }
                }
                for(int m = startTime + totcleantime;m <= totTime;m ++){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            barrierMatrix[m][i][j] = barrierMatrix[m - interval][i][j];
                            barrierMatrix[m][i][j] = barrierMatrix[m - interval][i][j];
                        }
                    }
                }
            }
            emit findPath();
            curCleaner = *iter;
        }
    }
}

//接收命令并将命令初始化
void BioChip::getOrder(Order &od)
{
    this->order = od;
    int t = 0;
    this->setZero();
    while(!order.isEmpty()){
        QString curOrder = order.getCurOrder();
        QList<int> curArg = order.getCurArguments();

        t = curArg.takeFirst();
        //将命令形成矩阵
        if(curOrder == "Input"){
            dropNum ++;
            int x = curArg.takeFirst();
            int y = curArg.takeFirst();
            setLeftMatrix(t + 1,x,y,1);
            setLeftTimeValue(dropNum,t + 1,x,y);

            dropState[dropNum][0][2] = t + 1;

            if(x == 1 && y != 1){
                matrix[t][x - 1][y] = 1;
            }else if (x < column && y == 1){
                matrix[t][x][y - 1] = 1;
            }else if(x > 1 && x <= column && y == row){
                matrix[t][x][y + 1] = 1;
            }else if(x > column && y == row){
                matrix[t][x + 1][y] = 1;
            }
            if(matrix[t][0][0] < 103 || matrix[t][0][0] > 105)matrix[t][0][0] = 101;//音乐播放控制
            if((!checkBesideInput(x,y)) && errorSolved == true){
                errorInputTime = t + 1;
                errorSolved = false;
            }
        }else if(curOrder == "Move"){
            int beg_x = curArg.takeFirst();
            int beg_y = curArg.takeFirst();
            int end_x = curArg.takeFirst();
            int end_y = curArg.takeFirst();
            //链接路径
            for(int i = 1;i <= dropNum;i ++){
                if(dropState[i][t][0] == beg_x && dropState[i][t][1] == beg_y){
                    setLeftTimeValue(i,t + 1,end_x,end_y);
                    break;
                }
            }
            setLeftMatrix(t + 1,beg_x,beg_y,0);          
            setLeftMatrix(t + 1,end_x,end_y,1);

            if(matrix[t][0][0] < 103 || matrix[t][0][0] > 105)matrix[t][0][0] = 102;//音乐播放控制
        }else if(curOrder == "Split"){//消耗2时间单位
            int x = curArg.takeFirst();
            int y = curArg.takeFirst();
            setLeftMatrix(t + 1,x,y,0);
            for(int i = 1;i <= dropNum;i ++){
                if(dropState[i][t][0] == x && dropState[i][t][1] == y){
                    setLeftTimeValue(i,t + 1,0,0);
                    break;
                }
            }
            matrix[t][x][y] = 1;
            matrix[t + 1][x][y] = 2;//表示中间状态，横向椭圆
            int end_x1 = curArg.takeFirst();
            int end_y1 = curArg.takeFirst();
            setLeftMatrix(t + 2,end_x1,end_y1,1);
            dropNum++;

            setLeftTimeValue(dropNum,t + 2,end_x1,end_y1);
            dropState[dropNum][0][2] = t + 2;

            int end_x2 = curArg.takeFirst();
            int end_y2 = curArg.takeFirst();
            setLeftMatrix(t + 2,end_x2,end_y2,1);
            dropNum++;

            setLeftTimeValue(dropNum,t + 2,end_x2,end_y2);
            dropState[dropNum][0][2] = t + 2;

            if(end_x1 == end_x2)matrix[t + 1][x][y] = 3;//纵向椭圆
            matrix[t][0][0] = 103;
            matrix[t + 1][0][0] = 104;
        }else if(curOrder == "Mix"){
            int count = 0;
            int x = 0,y = 0,last_x = 0,last_y = 0;
            while(!curArg.isEmpty()){
                x = curArg.takeFirst();
                y = curArg.takeFirst();
                if(count == 0){
                    setLeftMatrix(t + count + 1,x,y,0);
                }else if(count > 0){
                    for(int i = 1;i <= dropNum;i ++){
                        if(dropState[i][t + count - 1][0] == last_x && dropState[i][t + count - 1][1] == last_y){
                            dropState[i][t + count][0] = x;
                            dropState[i][t + count][1] = y;
                            break;
                        }
                    }
                }
                matrix[t + count][x][y] = 1;
                count ++;
                if(matrix[t+count][0][0] < 103 || matrix[t+count][0][0] > 105)matrix[t + count][0][0] = 102;
                last_x = x;last_y = y;
            }
            setLeftMatrix(t + count,x,y,1);
            for(int i = 1;i <= dropNum;i ++){
                if(dropState[i][t + count - 1][0] == last_x && dropState[i][t + count - 1][1] == last_y){
                    setLeftTimeValue(i,t + count,x,y);
                    break;
                }
            }
        }else if(curOrder == "Merge"){//消耗2时间单位
            int x1 = curArg.takeFirst();
            int y1 = curArg.takeFirst();
            int x2 = curArg.takeFirst();
            int y2 = curArg.takeFirst();
            setLeftMatrix(t + 1,x1,y1,0);
            setLeftMatrix(t + 1,x2,y2,0);
            for(int i = 1;i <= dropNum;i ++){
                if(dropState[i][t][0] == x1 && dropState[i][t][1] == y1){
                    setLeftTimeValue(i,t + 1,0,0);
                    break;
                }
            }
            for(int i = 1;i <= dropNum;i ++){
                if(dropState[i][t][0] == x2 && dropState[i][t][1] == y2){
                    setLeftTimeValue(i,t + 1,0,0);
                    break;
                }
            }
            if(x1 == x2)matrix[t + 1][(x1 + x2) / 2][(y1 + y2) / 2] = 3;//标记为2表示中间状态，纵向椭圆
            else matrix[t + 1][(x1 + x2) / 2][(y1 + y2) / 2] = 2;//横向椭圆
            dropNum ++;

            setLeftTimeValue(dropNum,t + 2,(x1 + x2) / 2,(y1 + y2) / 2);

            dropState[dropNum][0][2] = t + 2;
            setLeftMatrix(t + 2,(x1 + x2) / 2,(y1 + y2) / 2,1);
            matrix[t][0][0] = 105;

        }else if(curOrder == "Output"){
            int x = curArg.takeFirst();
            int y = curArg.takeFirst();
            setLeftMatrix(t + 1,x,y,0);
            for(int i = 1;i <= dropNum;i ++){
                if(dropState[i][t][0] == x && dropState[i][t][1] == y){
                    setLeftTimeValue(i,t + 1,0,0);
                    break;
                }
            }
            matrix[t][x][y] = 1;
            if(x == 1 && y != 1){
                matrix[t + 1][x - 1][y] = 1;
            }else if (x < column && y == 1){
                matrix[t + 1][x][y - 1] = 1;
            }else if(x > 1 && x <= column && y == row){
                matrix[t + 1][x][y + 1] = 1;
            }else if(x == column && y != row){
                matrix[t + 1][x + 1][y] = 1;
            }
            if(matrix[t][0][0] < 103 || matrix[t][0][0] > 105)matrix[t][0][0] = 102;
            if((!checkBesideOutput(x,y)) && errorSolved == true){
                errorOutputTime = t + 1;
                errorSolved = false;
            }
        }
    }
    totTime = t + 1;
    matrixset = true;
    qDebug()<<errorInputTime;
    qDebug()<<errorOutputTime;

    //污染矩阵初始化和错误检查
    iniPollutionMatrix();
    //初始化障碍矩阵
    iniBarrierMatrix();
    //初始化污染四元数
    iniPollutionList();
    getSubMatrix();
    getSubDropState();
    gettimeStartEnd();
    getBarrierMatrix();
    subtotTime = totTime;

    errorStaticTime = checkNotStaticBeside();
    errorDynamicTime = checkNotDynamicBeside();
    if(errorStaticTime > 0 || errorDynamicTime > 0)errorSolved = false;

    washer.iniPath(barrierMatrix,timeStartEnd,row,column);

}

//绘制整个过程，只有一个函数
void BioChip::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter* paint = new QPainter(this);

    //界面初始化
    if(isSetted){
        chipPaintEvent(paint,this->row,this->column);
        gatePaintEvent(paint);
        IOputPaintEvent(paint);
    }
    //绘制矩阵
    if(matrixset){
        qDebug()<<"curtime"<<curtime<<"totTime"<<totTime;
        if(curtime >= 0 && curtime <= totTime){
            drawPollutionEvent(paint,curtime);
            MatrixPaintEvent(paint,curtime);
            qDebug()<<cleaner_on<<"clearner_on";
            barrierPaintEvent(paint);
            if(cleaner_on)cleanerPaintEvent(paint,curtime);
        }else if(paintPollution || curtime > totTime){
            drawPollutionNumEvent(paint);
        }
    }
    paint->end();
}

//鼠标点击就将其变色，同时改变当前时刻的障碍矩阵
void BioChip::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && cleaner_on && cleaner_doing){
        QPoint mousepos = QWidget::mapFromGlobal(QCursor::pos());
        int temp_x = int((mousepos.x() - begin_x + 30) / width);
        int temp_y = int((280 - mousepos.y() + begin_y) / width);
        if(matrixset && temp_x > 0 && temp_x <= column && temp_y > 0 && temp_y <= row){
            QPoint p(temp_x,temp_y);
            if(barrierMatrix[curtime][temp_x][temp_y] == 0){
                for(int t = curtime;t < 100;t ++)barrierMatrix[t][temp_x][temp_y] = 1;
                barrierPos.push_back(p);
            }
            else if(barrierMatrix[curtime][temp_x][temp_y] == 1){
                for(int t = curtime;t < 100;t ++)barrierMatrix[t][temp_x][temp_y] = 0;
                QList<QPoint>::Iterator iter;
                for(iter = barrierPos.begin();iter != barrierPos.end();++ iter){
                    if((*iter).x() == p.x() && (*iter).y() == p.y()){
                        barrierPos.removeAll(p);
                        break;
                    }
                }
            }
        }
        qDebug()<<temp_x<<temp_y<<width<<curtime;
        changePath();
    }
    this->repaint();
    return QWidget::mousePressEvent(event);
}

//绘制芯片
void BioChip::chipPaintEvent(QPainter *paint, int r, int c)
{
    paint->setPen(QPen(Qt::gray , 2 , Qt::SolidLine));
    //画横线
    for(int i = 0;i < r + 1;++i){
        paint->drawLine(begin_x , begin_y + width * i , begin_x + width * c,begin_y + width * i);
    }
    for(int i = 0;i < c + 1;++i){
        paint->drawLine(begin_x + width * i, begin_y, begin_x + width * i,begin_y + width * r);
    }
}

//绘制清洗出入口
void BioChip::gatePaintEvent(QPainter *paint)
{
    paint->setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
    paint->drawRect(begin_x - int(1.6 * width),begin_y + width * (row - 1),int(1.6 * width),width);
    paint->drawRect(begin_x + width * column,begin_y,int(1.6 * width),width);
    paint->setFont(QFont("Times New Roman",10));
    QPointF point(begin_x - 1.6 * width,begin_y + (width) * (row - 0.4));
    paint->drawText(point,"WashInput");
    QPointF point_o(begin_x + width * column,begin_y + (width) * 0.7);
    paint->drawText(point_o,"Waste");
}

//绘制液滴出入口
void BioChip::IOputPaintEvent(QPainter *paint)
{
    QList<int>::Iterator iter;
    for(iter = this->input.begin();iter != this->input.end();iter++){
        int tempx = *iter;
        int tempy = *(++iter);
        putPaintEvent(paint,tempx,tempy,"INPUT");
    }
    putPaintEvent(paint,output_x,output_y,"OUTPUT");
}

//绘制融合和分裂过程
void BioChip::MatrixPaintEvent(QPainter *paint,int curTime)
{
    paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    int flag = 0;
    for(int i = 0;i <= column + 1;i ++){
        for(int j = 0;j <= row + 1;j ++){
            if(music_on && curTime < totTime){
                flag = matrix[curTime - 1][0][0];
                if(flag == 101 || flag == 102 || flag == 106)move_sound->play();
                else if(flag == 103)split_strech_sound->play();
                else if(flag == 104)split_finish_sound->play();
                else if(flag == 105)merge_sound->play();
            }
            if(matrix[curTime][i][j] == 2)EllispePaintEvent(paint,i,j,2);
            else if(matrix[curTime][i][j] == 3)EllispePaintEvent(paint,i,j,3);
        }
    }
}

//绘制椭圆
void BioChip::EllispePaintEvent(QPainter *paint, int x, int y, int flag)
{
    paint->setBrush(QBrush(Qt::red, Qt::SolidPattern));//颜色，实图案
    if(flag == 2){//横向椭圆
        paint->drawEllipse(changetoQtCoordinate_x(x) - width,changetoQtCoordinate_y(y),int(width * 2.5),width / 2);
    }else if(flag == 3){//纵向椭圆
        paint->drawEllipse(changetoQtCoordinate_x(x),changetoQtCoordinate_y(y) - width,width / 2,int(width * 2.5));
    }
}

//绘制门
void BioChip::putPaintEvent(QPainter *paint, int x, int y, const QString &str)
{
    paint->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    paint->setFont(QFont("Times New Roman",10));
    if(x == 1 && y != 1){
        QRect rec(begin_x - int(1.6 * width),begin_y + width * (row - y),int(1.6 * width),width);
        paint->drawRect(rec);
        QPointF point(changetoQtCoordinate_x(0) - width,changetoQtCoordinate_y(y) - int(0.7 * width));
        paint->drawText(rec,Qt::TextSingleLine,str);
    }else if(x < column && y == 1){
        QRect rec(begin_x + width * (x - 1),begin_y + width * row,width,int(width * 1.6));
        paint->drawRect(rec);
        QPointF point(changetoQtCoordinate_x(x),changetoQtCoordinate_y(0));
        paint->drawText(rec,Qt::TextWordWrap,str);
    }else if(x > 1 && x <= column && y == row){
        QRect rec(begin_x + width * (x - 1),begin_y - int(1.6 * width),width,int(1.6 * width));
        paint->drawRect(rec);
        QPointF point(changetoQtCoordinate_x(x),changetoQtCoordinate_y(row + 1));
        paint->drawText(rec,Qt::TextWordWrap,str);
    }else if(x == column && y != row){
        QRect rec(begin_x + width * column,begin_y + width*(row - y),int(1.6 * width),width);
        paint->drawRect(rec);
        QPointF point(changetoQtCoordinate_x(column + 1),changetoQtCoordinate_y(y) - 0.7 * width);
        paint->drawText(rec,Qt::TextSingleLine,str);
    }
}

//绘制污染曲线 和 液滴
void BioChip::drawPollutionEvent(QPainter *paint,int curtime)
{
    if(cleaner_on){
        QList<Washdrop>::Iterator wash_iter;
        paint->setPen(QPen(QBrush(MyColor::ColorSet[8]),width * 0.4,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for(wash_iter = this->washer.washdropList.begin();wash_iter != this->washer.washdropList.end();wash_iter++){
            int count = 0;
            int start = wash_iter->getStarttime();
            QList<Position>::Iterator iter = wash_iter->pathList.begin();
            QList<Position>::Iterator nextiter = iter + 1;
            for(;iter != wash_iter->pathList.end() && count < curtime - start && nextiter != wash_iter->pathList.end();iter++,nextiter++,count++){
                if(nextiter != wash_iter->pathList.end()){
                    if(count < curtime - start){
                        int x1 = changetoQtCoordinate_x(iter->x);
                        int y1 = changetoQtCoordinate_y(iter->y);
                        int x2 = changetoQtCoordinate_x(nextiter->x);
                        int y2 = changetoQtCoordinate_y(nextiter->y);
                        paint->drawLine(x1+ width / 4,y1 + width / 4,x2 + width / 4,y2 + width / 4);
                    }
                }
            }
        }
    }

    int begintime,x1,x2,y1,y2;
    for(int n = 1;n <= dropNum;n ++){
        paint->setPen(QPen(QBrush(MyColor::ColorSet[n % 9]),width * 0.4,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        begintime = dropState[n][0][2];
        for(int t = begintime + 1;t <= curtime;t++){
            if(dropState[n][t][0] > 0 && dropState[n][t][1] > 0){
                x1 = changetoQtCoordinate_x(dropState[n][t - 1][0]);
                x2 = changetoQtCoordinate_x(dropState[n][t][0]);
                y1 = changetoQtCoordinate_y(dropState[n][t- 1][1]);
                y2 = changetoQtCoordinate_y(dropState[n][t][1]);
                paint->drawLine(x1 + width / 4,y1 + width / 4,x2 + width / 4,y2 + width / 4);
            }
        }
        if(dropState[n][curtime][0] > 0 && dropState[n][curtime][1] > 0){
            if(whoPolluteMatrix[dropState[n][curtime][0]][dropState[n][curtime][1]] != n){
                if(whoPolluteMatrix[dropState[n][curtime][0]][dropState[n][curtime][1]] > 0 && whoPolluteMatrix[dropState[n][curtime][0]][dropState[n][curtime][1]] != n){
                    emit pollutionExisted();
                }else {
                    emit pollutionClear();
                }
                if(play_forwoard && (!have_reached_final))pollutionMatrix[0][dropState[n][curtime][0]][dropState[n][curtime][1]] ++;
                whoPolluteMatrix[dropState[n][curtime][0]][dropState[n][curtime][1]] = n;
            }
            x2 = changetoQtCoordinate_x(dropState[n][curtime][0]);
            y2 = changetoQtCoordinate_y(dropState[n][curtime][1]);
            paint->drawEllipse(x2 , y2, width / 2,width / 2);//显示在方格中心
        }
    }

}

//在指定坐标上画污染次数
void BioChip::drawPollutionNumEvent(QPainter *paint)
{
    paint->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    paint->setFont(QFont("Times New Roman",10));
    for(int i = 1;i <= column;i++){
        for(int j = 1;j <= row;j ++){
            numPaintEvent(paint,i,j,pollutionMatrix[0][i][j]);
        }
    }
}

//在某格位置上绘制数字
inline void BioChip::numPaintEvent(QPainter *paint, int x, int y, int num)
{
    paint->drawText(changetoQtCoordinate_x(x) + width / 5,changetoQtCoordinate_y(y) + width / 2,QString::number(num));
}

//绘制鼠标设置的障碍
void BioChip::barrierPaintEvent(QPainter *paint)
{
    QList<QPoint>::Iterator iter;
    for(iter = barrierPos.begin();iter != barrierPos.end();iter ++){
        if(cleaner_on){
            QColor tempcolor(255,20,147);
            paint->setBrush(QBrush(tempcolor,Qt::SolidPattern));
            paint->drawRect(changetoQtCoordinate_x((*iter).x()) - int(width * 0.2),changetoQtCoordinate_y((*iter).y()) - int(width * 0.2),int(width * 0.8),int(width * 0.8));
        }
    }
}

//绘制清洗液滴
void BioChip::cleanerPaintEvent(QPainter *paint,int t)
{
    if(cleaner_doing){
        paint->setPen(QPen(QBrush(MyColor::ColorSet[8]),width * 0.4,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        int count = 0;
        int start = curCleaner.getStarttime();
        QList<Position>::Iterator iter = curCleaner.pathList.begin();
        QList<Position>::Iterator nextiter;
        for(;iter != curCleaner.pathList.end() && count < t - start;iter++,count++){
            nextiter = iter + 1;
            if(count < t - start){
                int x1 = changetoQtCoordinate_x(iter->x);
                int y1 = changetoQtCoordinate_y(iter->y);
                int x2 = changetoQtCoordinate_x(nextiter->x);
                int y2 = changetoQtCoordinate_y(nextiter->y);
                paint->drawLine(x1 + width / 4,y1 + width / 4,x2+ width / 4,y2+ width / 4);
            }
        }

        if(count == t - start){
            if(music_on)this->move_sound->play();
            Position pos(curCleaner.getPositionAtTime(t - start));

            if(pollutionMatrix[0][pos.x][pos.y] > 0){
                pollutionMatrix[0][pos.x][pos.y] = 0;
                whoPolluteMatrix[pos.x][pos.y] = 0;
            }
            paint->drawEllipse(changetoQtCoordinate_x(pos.x),changetoQtCoordinate_y(pos.y),width / 2,width / 2);
        }
    }
}

//绘制中等球
void BioChip::pointPaintEvent(QPainter *paint,int x,int y)
{
    paint->setBrush(QBrush(Qt::red, Qt::SolidPattern));//颜色，实图案
    paint->drawEllipse(changetoQtCoordinate_x(x) , changetoQtCoordinate_y(y), width / 2,width / 2);//显示在方格中心
}

//绘制大球
void BioChip::LargePointPaintEvent(QPainter *paint, int x, int y)
{
    paint->setBrush(QBrush(Qt::red, Qt::SolidPattern));//颜色，实图案
    paint->drawEllipse(changetoQtCoordinate_x(x) - int(width * 0.12), changetoQtCoordinate_y(y) - int(width * 0.12), int(width * 0.8),int(width * 0.8));//显示在方格中心
}

//绘制小球
void BioChip::SmallPointPaintEvent(QPainter *paint, int x, int y)
{
    paint->setBrush(QBrush(Qt::red, Qt::SolidPattern));//颜色，实图案
    paint->drawEllipse(changetoQtCoordinate_x(x) + int(width * 0.1), changetoQtCoordinate_y(y) + int(width * 0.1), int(width * 0.3),int(width * 0.3));//显示在方格中心
}

//输入规定坐标系坐标x，返回Qt的绘图坐标x
int BioChip::changetoQtCoordinate_x(int x)
{
    return begin_x + width / 4 + width * (x - 1);
}
//输入规定坐标系坐标y，返回Qt的绘图坐标y
int BioChip::changetoQtCoordinate_y(int y)
{
    return begin_y + width / 4 + width * (row - y);
}

//初始化障碍矩阵
void BioChip::iniBarrierMatrix()
{
    for(int t = 0;t <= totTime;t ++ ){
        for(int i = 1;i <= row;i ++){
            for(int j = 1;j <= column;j ++){
                if(matrix[t][i][j] > 0){
                    for(int x = 0;x < 3;x ++){
                        for(int y = 0;y < 3;y ++){
                            barrierMatrix[t][i + x - 1][j + y - 1] = 1;
                        }
                    }
                }
            }
        }
    }
}

//初始化污染事件列表 并将列表 导入矩阵
void BioChip::iniPollutionList()
{
    int t1,t2;
    for(int i = 1;i <= row;i ++){
        for(int j =1;j <= column;j ++){
            for(int count = 1;count <= dropNum;count ++){
                if((t1 = pollutionMatrix[count][i][j]) > 0){
                    for(int count1 = count + 1;count1 <= dropNum;count1++){
                        if(count1 != count){
                            if((t2 = pollutionMatrix[count1][i][j]) > 0){
                                if(t1 > t2){
                                    pollutionEvent temp(i,j,t2,t1);
                                    pollutionList.append(temp);
                                }else if(t1 < t2){
                                    pollutionEvent temp(i,j,t1,t2);
                                    pollutionList.append(temp);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::sort(pollutionList.begin(),pollutionList.end(),compare);
    QList<pollutionEvent>::Iterator iter;
    int count = 1;
    for(iter = pollutionList.begin();iter != pollutionList.end();iter++,count++){
        timeStartEnd[count][0] = iter->x;
        timeStartEnd[count][1] = iter->y;
        timeStartEnd[count][2] = iter->t1;
        timeStartEnd[count][3] = iter->t2;
    }
}

int BioChip::getCurTime() const
{
    return curtime;
}

void BioChip::setLeftMatrix(int t, int x, int y, int value)
{
    for(int i = t;i < 50;i ++){
        matrix[i][x][y] = value;
    }
}

void BioChip::setZero()
{
    curtime = 0;
    totTime = 0;
    dropNum = 0;
    stopTime = -1;
    errorInputTime = -2;
    errorOutputTime = -2;
    errorStaticTime = -2;
    errorDynamicTime = -2;
    errorPollutionTime = -2;
    errorSolved = true;
    errorHappened = false;
    paintPollution = false;
    cleaner_on = false;
    cleaner_doing = false;
    cleaner_done = true;
    barrierPos.clear();
    pollutionList.clear();
    washer.reset();
    for(int t = 0; t < 100;t ++){
        for(int i = 0;i < 18;i++){
            for(int j = 0;j < 18;j ++){
                matrix[t][i][j] = 0;
            }
        }
    }
    for(int t = 0; t < 50;t ++){
        for(int i = 0;i < 21;i++){
            for(int j = 0;j < 21;j ++){
                 pollutionMatrix[t][i][j] = 0;
            }
        }
    }
    for(int t = 0; t < 20;t ++){
        for(int i = 0;i < 100;i++){
            for(int j = 0;j < 3;j ++){
                 dropState[t][i][j] = 0;
            }
        }
    }
    for(int t = 0;t < 100;t ++){
        for(int i = 0;i < 18;i ++){
            for(int j = 0;j < 18;j ++){
                barrierMatrix[t][i][j] = 0;
            }
        }
    }
    for(int i = 0;i < 50;i ++){
        for(int j = 0;j < 5 ;j ++){
            timeStartEnd[i][j] = 0;
        }
    }
    for(int i = 0;i < 21;i ++){
        for(int j = 0;j < 21;j ++){
            whoPolluteMatrix[i][j] = 0;
        }
    }

}

void BioChip::setMusicOn(bool state)
{
    music_on = state;
}

void BioChip::setCleanerOn(bool state)
{
    this->cleaner_on = state;
    if(cleaner_on == false)barrierPos.clear();
}

bool BioChip::checkBesideInput(int x,int y)
{
    bool flag = false;
    int temp1,temp2;
    QList<int>::Iterator iter;
    for(iter = this->input.begin();iter != this->input.end(); iter++){
        temp1 = *iter;
        temp2 = *(++iter);
        if(x == temp1 && y == temp2){
            flag = true;
            break;
        }
    }
    return flag;
}

bool BioChip::checkBesideOutput(int x, int y)
{
    if(x == this->output_x && y == this->output_y)return true;
    else return false;
}

//静态检查
int BioChip::checkNotStaticBeside()
{
    bool flag = false;
    int errortime = -1;
    for(int i = 1; i <= dropNum;i ++){
        for(int j = 1;j <= dropNum;j ++){
            if(i!=j){
                for(int t = 0;t <= totTime;t ++){
                    if(dropState[i][t][0] != 0 && dropState[j][t][0] != 0 && dropState[i][t][1] != 0 && dropState[i][t][1] != 0){
                        if(abs(dropState[i][t][0] - dropState[j][t][0]) <= 1 && abs(dropState[i][t][1] - dropState[j][t][1]) <= 1){
                            flag = true;
                            errortime = t;
                            break;
                        }
                    }
                }
            }
            if(flag == true)break;
        }
        if(flag == true)break;
    }
    return errortime;
}

//动态检查
int BioChip::checkNotDynamicBeside()
{
    bool flag = false;
    int errortime = -1;
    for(int i = 1; i <= dropNum;i ++){
        for(int j = 1;j <= dropNum;j ++){
            if(i!=j){
                for(int t = 0;t < totTime;t ++){
                    if(dropState[i][t + 1][0] != 0 && dropState[j][t][0] != 0 && dropState[i][t + 1][1] != 0 && dropState[i][t][1] != 0){
                        if(abs(dropState[i][t + 1][0] - dropState[j][t][0]) <= 1 && abs(dropState[i][t + 1][1] - dropState[j][t][1]) <= 1){
                            flag = true;
                            errortime = t;
                            break;
                        }
                    }
                }
            }
            if(flag == true)break;
        }
        if(flag == true)break;
    }
    return errortime;
}

//初始化污染情况矩阵
void BioChip::iniPollutionMatrix()
{
    for(int count = 1;count <= dropNum;count ++){
        for(int t = 0;t < 100;t ++){
            if(pollutionMatrix[count][dropState[count][t][0]][dropState[count][t][1]]  == 0){
                pollutionMatrix[count][dropState[count][t][0]][dropState[count][t][1]] = t;
            }
        }
    }
}

void BioChip::setLeftTimeValue(int num,int t,int x,int y)
{
    for(int i = t;i < 100;i++){
        dropState[num][i][0] = x;
        dropState[num][i][1] = y;
    }
}

//当前时间++
void BioChip::addcurTime()
{
    if(curtime <= totTime)curtime ++;
    play_forwoard = true;
    if(beforeError && showErrorMessage()){
        curtime = stopTime;
        beforeError = false;
    }
    if(cleaner_on){
        QList<Washdrop>::Iterator iter;
        QList<Washdrop>::Iterator subiter;
        for(iter = this->washer.washdropList.begin();iter != this->washer.washdropList.end() && cleaner_done;iter ++){
            if(curtime == iter->getStarttime()){
                subiter = washer.washdropList.begin();
                cleaner_doing = true;
                cleaner_done = false;

                totcleantime = iter->getTottime();
                freezeTime = curtime;
                for(;subiter != this->washer.washdropList.end();subiter ++){
                    if(subiter->getStarttime() > curtime && subiter != iter)subiter->setStartTime(subiter->getStarttime() + totcleantime);
                }

                totTime += totcleantime;
                if(errorOutputTime > curtime)errorOutputTime += totcleantime;
                if(errorInputTime > curtime)errorInputTime += totcleantime;
                if(errorStaticTime > curtime)errorStaticTime += totcleantime;
                if(errorDynamicTime > curtime)errorDynamicTime += totcleantime;

                curCleaner = *iter;
                for(int n = 1;n <= dropNum;n ++){
                    if(curtime <= dropState[n][0][2])dropState[n][0][2] += totcleantime;
                    for(int m = totTime + totcleantime;m >= freezeTime + totcleantime;m -- ){
                        dropState[n][m][0] = dropState[n][m - totcleantime][0];
                        dropState[n][m][1] = dropState[n][m - totcleantime][1];
                    }
                    for(int t = freezeTime + 1;t < freezeTime + totcleantime;t ++){
                        dropState[n][t][0] = dropState[n][freezeTime][0];
                        dropState[n][t][1] = dropState[n][freezeTime][1];
                    }
                }
                for(int m = totTime + totcleantime;m >= freezeTime + totcleantime;m --){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            matrix[m][i][j] = matrix[m - totcleantime][i][j];
                            matrix[m][i][j] = matrix[m - totcleantime][i][j];
                        }
                    }
                }
                for(int t = freezeTime;t < freezeTime + totcleantime;t++){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            matrix[t][i][j] = matrix[freezeTime][i][j];
                            matrix[t][i][j] = matrix[freezeTime][i][j];
                        }
                    }
                }
                for(int m = totTime + totcleantime;m >= freezeTime + totcleantime;m --){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            barrierMatrix[m][i][j] = barrierMatrix[m - totcleantime][i][j];
                            barrierMatrix[m][i][j] = barrierMatrix[m - totcleantime][i][j];
                        }
                    }
                }
                for(int t = freezeTime;t < freezeTime + totcleantime;t++){
                    for(int i = 0;i <18;i ++ ){
                        for(int j = 0;j < 18;j ++){
                            barrierMatrix[t][i][j] = barrierMatrix[freezeTime][i][j];
                            barrierMatrix[t][i][j] = barrierMatrix[freezeTime][i][j];
                        }
                    }
                }
                break;
           }
        }
        if(curtime == curCleaner.getStarttime() + 1)changePath();
        if(cleaner_doing && curtime == freezeTime + totcleantime){
            totcleantime = 0;
            freezeTime = 0;
            cleaner_doing = false;
            cleaner_done = true;
        }
    }
    emit sendCurTime(curtime);
    if(curtime == totTime + 1)have_reached_final = true;
    this->repaint();
}

void BioChip::reducecurTime()
{
    if(curtime > 0)curtime --;
    beforeError = true;
    errorHappened = false;
    errorSolved = false;
    paintPollution = false;
    play_forwoard = false;
    emit sendCurTime(curtime);
    this->repaint();
}

void BioChip::resetTime()
{
    curtime = 0;
    beforeError = true;
    errorHappened = false;
    errorSolved = false;
    paintPollution = false;
    pollutionError = false;
    play_forwoard = true;
    have_reached_final = false;

    barrierPos.clear();
    pollutionList.clear();
    resetMatrix();
    resetDropState();
    resettimeStartEnd();
    resetBarrierMatrix();

    totTime = subtotTime;
    washer.reset();
    washer.iniPath(barrierMatrix,timeStartEnd,row,column);
    for(int i = 0;i < 21;i ++){
        for(int j = 0;j < 21;j ++){
            whoPolluteMatrix[i][j] = 0;
        }
    }
    for(int t = 0; t < 50;t ++){
        for(int i = 0;i < 21;i++){
            for(int j = 0;j < 21;j ++){
                 pollutionMatrix[t][i][j] = 0;
            }
        }
    }
    emit sendCurTime(curtime);
    emit cleanerButtonOff();
    emit pollutionClear();
}

void BioChip::startTimer()
{
    fTimer->start();
    beforeError = true;
    errorHappened = false;
    errorSolved = false;
    paintPollution = false;
    play_forwoard = true;
}

void BioChip::endTimer()
{
    fTimer->stop();
    paintPollution = true;
}

void BioChip::updateChip()
{
    this->addcurTime();
    if(curtime >= totTime + 1){
        fTimer->stop();
        paintPollution = true;
        emit ButtonUnable();
    }
    emit sendCurTime(curtime);
}

