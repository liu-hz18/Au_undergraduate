#ifndef CREATELINK_H
#define CREATELINK_H

#include <QDialog>
#include <QSignalMapper>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class CreateLink;
}

class CreateLink : public QDialog
{
    Q_OBJECT

public:
    explicit CreateLink(QWidget *parent = nullptr);
    ~CreateLink();

private slots:
    void keyPressed(int);
    void on_pushButton_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();

signals:
    void sendIP(QString);

private:
    Ui::CreateLink *ui;
    QString str_ip;

    bool isCorrect(const QString& ip);
    void showError();
};

#endif // CREATELINK_H
