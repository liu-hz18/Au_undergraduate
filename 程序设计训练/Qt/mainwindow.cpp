#include "mainwindow.h"
#include "settablesize.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    rootPath = QCoreApplication::applicationDirPath();
    filePath = rootPath + "\\Input\\";
    biochip = new BioChip(ui->groupBox);

    //绘制初始芯片
    connect(this,SIGNAL(setAllValue()),this,SLOT(drawChip()));
    connect(biochip,&BioChip::ButtonUnable,this,[=](){
        ui->actionStart_2->setChecked(false);
    });
    connect(biochip,SIGNAL(sendCurTime(int)),ui->lcdNumber,SLOT(display(int)));
    connect(biochip,&BioChip::cleanerButtonOff,this,[=](){
        ui->actionCleanable->setChecked(false);
    });
    connect(biochip,&BioChip::pollutionExisted,this,[=](){
        ui->lineEdit->setText("Pollution Existed!");
    });
    connect(biochip,&BioChip::pollutionClear,this,[=](){
       ui->lineEdit->setText(nullptr);
    });
    connect(biochip,&BioChip::noPath,this,[=](){
        ui->lineEdit->setText("No Path Found!");
    });
    connect(biochip,&BioChip::findPath,this,[=](){
        ui->lineEdit->setText(nullptr);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::allValueisSet()
{
    if(isSet(this->row) && isSet(this->column)&& isSet(this->output_x) && isSet(this->output_y)){
        QList<int>::Iterator iter;
        bool flag = true;
        for(iter = this->input.begin();iter!=this->input.end();iter++){
            if(!isSet(*iter)){flag = false;break;}
        }
        if(flag){
            emit setAllValue();
            return true;
        }else return false;
    }
    else return false;
}

inline bool MainWindow::isSet(int a)const
{
    if(a > 0 && a < 16)return true;
    return false;
}

void MainWindow::on_actionSetTable_triggered()
{
    SetTableSize *setWidget = new SetTableSize(this);

    connect(setWidget,SIGNAL(sendRow(int)),this,SLOT(receiveRow(int)));
    connect(setWidget,SIGNAL(sendColumn(int)),this,SLOT(receiveColumn(int)));
    connect(setWidget,SIGNAL(sendInput(QList<int>)),this,SLOT(receiveInput(QList<int>)));
    connect(setWidget,SIGNAL(sendOutput_x(int)),this,SLOT(receiveOutput_x(int)));
    connect(setWidget,SIGNAL(sendOutput_y(int)),this,SLOT(receiveOutput_y(int)));

    connect(setWidget,SIGNAL(sendOutput_y(int)),this,SLOT(allValueisSet()));

    setWidget->show();
    setWidget->move((this->geometry().width() - setWidget->geometry().width()) / 2,(this->geometry().height() - setWidget->geometry().height())/ 2);
}

void MainWindow::on_actionAbout_triggered()
{
    QString about_title = "About DMFB";
    QString about_info = "For more things about DMFB,please go to:\nhttp://microfluidics.cs.ucr.edu/dmfb_static_simulator/benchmarks.html";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void MainWindow::on_actionHelp_H_triggered()
{
    QString about_title = "Help";
    QString about_info = "Setting Button:  set the row and column of the BioChip.(Row and Column CANNOT be smaller than 3 simultaneously)\nAnd then you can select SEVERAL INPUT gate and ONE OUTPUT gate on the MARGIN of the Chip.\n\n"
                         "File Button: Select a .txt file that contains the order and it will be load into this app.\n(Be sure that the foemat is CORRECT)\n\n"
                         "INPUT FILE Format:\n\tInput t,x,y\n\tOutput t,x,y\n\tMerge t,x1,y1,x2,y2\n\tSplit t,x1,y1,x2,y2\n\tMix t,x1,y1,x2,y2,x3,y3...\n\n"
                         "Play Button: After you load a file ,you can push it to play the whole process.\n\n"
                         "Next Step Button:  You can press it to get the next frame.\n\n"
                         "Last Step Button:  You can press it to get the previous frame.\n\n"
                         "Reset Button:   You can press it to reset the process.Then you can press PLAY or NEXT STEP...\n\n"
                         "Cleaner Mode Button:  You can press it to have the cleaner to clean the BioChip to avoid pollution.\n\n"
                         "Music Button:  Press it to play the audio during the process.";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    QMessageBox::information(this,about_title,about_info,QMessageBox::Ok,defaultButton);
}

void MainWindow::on_actionSet_Row_and_Column_triggered()
{
    on_actionSetTable_triggered();
}

void MainWindow::on_actionOpen_File_2_triggered()
{
    QString openFileTitle = tr("Open and read a .txt file");
    QString filiter = "Text(*.txt);;All(*.*);;Programs(*.h *.cpp)";
    QString FileName = QFileDialog::getOpenFileName(this,openFileTitle,filePath,filiter);
    if(FileName.isEmpty())return ;
    order.readFile(FileName);   
    biochip->getOrder(order);//将命令传输给绘图类
    on_actionReset_triggered();
}

void MainWindow::on_actionOpen_File_triggered()
{
    on_actionOpen_File_2_triggered();
}

void MainWindow::receiveRow(int r)
{
    this->row = r;
}

void MainWindow::receiveColumn(int c)
{
    this->column = c;
}

void MainWindow::receiveInput(QList<int> src)
{
    this->input = src;
}

void MainWindow::receiveOutput_x(int out_x)
{
    this->output_x = out_x;
}

void MainWindow::receiveOutput_y(int out_y)
{
    this->output_y = out_y;
}

void MainWindow::drawChip()
{
    biochip->setRow(this->row);
    biochip->setColumn(this->column);
    biochip->setWidth(biochip->widget_size / max(this->row,this->column));
    biochip->setGate(this->input,this->output_x,this->output_y);
    biochip->matrixset = false;
    biochip->update();
}

inline int MainWindow::max(int &a, int &b)
{
    return ((a>b)?a:b);
}

void MainWindow::on_pushButton_clicked()
{
    qApp->exit(0);
}

void MainWindow::on_actionNext_Frame_triggered()
{
    biochip->addcurTime();
}

void MainWindow::on_actionLast_Frame_triggered()
{
    biochip->reducecurTime();
}

void MainWindow::on_actionReset_2_triggered()
{
    biochip->resetTime();
    biochip->update();
    ui->actionStart_2->setChecked(false);
}

void MainWindow::on_actionStart_2_toggled(bool arg1)
{
    if(arg1)biochip->startTimer();
    else biochip->endTimer();
}

void MainWindow::on_actionStart_toggled(bool arg1)
{
    on_actionStart_2_toggled(arg1);
}

void MainWindow::on_actionStop_triggered()
{
    on_actionStart_2_toggled(false);
}

void MainWindow::on_actionLast_Step_triggered()
{
    on_actionLast_Frame_triggered();
}

void MainWindow::on_actionNext_Step_triggered()
{
    on_actionNext_Frame_triggered();
}

void MainWindow::on_actionReset_triggered()
{
    on_actionReset_2_triggered();
}

void MainWindow::on_actionPlay_triggered()
{
    on_actionStart_2_toggled(true);
}

void MainWindow::on_actionMusic_on_toggled(bool arg1)
{
    biochip->setMusicOn(arg1);
}

void MainWindow::on_actionCleanable_toggled(bool arg1)
{
    biochip->setCleanerOn(arg1);
}
