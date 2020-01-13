#include "promotion.h"
#include "ui_promotion.h"

Promotion::Promotion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Promotion)
{
    ui->setupUi(this);
    loadImage();
    number = 0;
}

Promotion::~Promotion()
{
    delete ui;
}

void Promotion::loadImage()
{
    this->white_bishop.load(":/pictures/pic/white_bishop.png");
    this->white_knight.load(":/pictures/pic/white_knight.png");
    this->white_queen.load(":/pictures/pic/white_queen.png");
    this->white_rook.load(":/pictures/pic/white_rook.png");

    ui->buttonqueen->setIcon(white_queen);//5
    ui->buttonrook->setIcon(white_rook);//6
    ui->buttonknight->setIcon(white_knight);//3
    ui->buttonbioshop->setIcon(white_bishop);//1
}

void Promotion::on_buttonqueen_clicked()
{
    number = 5;
}

void Promotion::on_buttonbioshop_clicked()
{
    number = 1;
}

void Promotion::on_buttonrook_clicked()
{
    number = 6;
}

void Promotion::on_buttonknight_clicked()
{
    number = 3;
}

void Promotion::on_pushButton_5_clicked()
{
    if(number == 0){
        QString title = "Error!";
        QString info = "You haven't selected a promotion!";
        QMessageBox::warning(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
    }
    else if(number == 1||number == 3 || number == 5|| number == 6){
        emit promotionNumSet(number);
        this->close();
    }
}
