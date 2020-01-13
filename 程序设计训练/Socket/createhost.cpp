#include "createhost.h"
#include "ui_createhost.h"

CreateHost::CreateHost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateHost)
{
    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
    getHostIp();
}

CreateHost::~CreateHost()
{
    delete ui;
}

//开始建立连接
void CreateHost::on_pushButton_clicked()
{
    qDebug()<<"OK pressed.";
    emit startConnect();
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setEnabled(false);
    this->close();
}

//中断连接
void CreateHost::on_pushButton_2_clicked()
{
    emit endConnect();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    this->close();
}

//获取主机IP
void CreateHost::getHostIp()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            strIpAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // 如果没有找到，则以本地IP地址为IP
    if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
    this->hostIP = strIpAddress;
    ui->lineEdit->setText(hostIP);
    //qDebug()<<hostIP;
}
