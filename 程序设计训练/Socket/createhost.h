#ifndef CREATEHOST_H
#define CREATEHOST_H

#include <QDialog>
#include <QDebug>
#include <QNetworkInterface>
#include <QtNetwork>

namespace Ui {
class CreateHost;
}

class CreateHost : public QDialog
{
    Q_OBJECT

public:
    explicit CreateHost(QWidget *parent = nullptr);
    ~CreateHost();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void startConnect();
    void endConnect();

private:
    Ui::CreateHost *ui;
    QString hostIP;
    void getHostIp();

};

#endif // CREATEHOST_H
