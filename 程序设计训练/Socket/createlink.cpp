#include "createlink.h"
#include "ui_createlink.h"

CreateLink::CreateLink(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateLink)
{
    QSignalMapper *mapper = new QSignalMapper(this);
    ui->setupUi(this);
    str_ip.clear();
    connect(ui->pushButton_0, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_0,0);
    connect(ui->pushButton_1, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_1,1);
    connect(ui->pushButton_2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_2,2);
    connect(ui->pushButton_3, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_3,3);
    connect(ui->pushButton_4, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_4,4);
    connect(ui->pushButton_5, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_5,5);
    connect(ui->pushButton_6, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_6,6);
    connect(ui->pushButton_7, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_7,7);
    connect(ui->pushButton_8, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_8,8);
    connect(ui->pushButton_9, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton_9,9);
    connect(ui->pushButton_point,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->pushButton_point,10);

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(keyPressed(int)));
    //connect(this,SIGNAL(numChanged(QString)),ui->lineEdit,SLOT(setText(QString)));

}

CreateLink::~CreateLink()
{
    delete ui;
}

void CreateLink::keyPressed(int num)
{
    if(num < 10 && num >= 0)this->str_ip.append(QString::number(num));
    if(num == 10)this->str_ip.append(".");
    ui->lineEdit->setText(str_ip);
}

bool CreateLink::isCorrect(const QString &ip)
{
    QList<QString> subip = ip.split('.');
    qDebug()<<subip;
    if(subip.size() != 4)return false;
    for(int i = 0;i < 4;i ++){
        if(subip[i].toInt() < 0 || subip[i].toInt() > 255 || subip[i] == ""){
            return false;
        }
    }
    return true;
}

void CreateLink::showError()
{
    QString about_title = "Error!";
    QString about_info = "IP is wrong!";
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    QMessageBox::warning(this,about_title,about_info,QMessageBox::Ok,defaultButton);
    this->str_ip.clear();
}

void CreateLink::on_pushButton_clicked()
{
    str_ip = ui->lineEdit->text();
    if(!isCorrect(str_ip)){
        showError();
        ui->lineEdit->clear();
        str_ip.clear();
    }else {
        emit sendIP(str_ip);
        this->close();
        str_ip.clear();
    }
}

void CreateLink::on_pushButton_10_clicked()
{
    str_ip.clear();
    this->close();
}

void CreateLink::on_pushButton_11_clicked()
{
    if(!str_ip.isEmpty())str_ip = str_ip.left(str_ip.length() - 1);
    ui->lineEdit->setText(str_ip);
}
