#ifndef PROMOTION_H
#define PROMOTION_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Promotion;
}

class Promotion : public QDialog
{
    Q_OBJECT

public:
    explicit Promotion(QWidget *parent = nullptr);
    ~Promotion();

signals:
    void promotionNumSet(int);

private slots:
    void on_buttonqueen_clicked();
    void on_buttonbioshop_clicked();
    void on_buttonrook_clicked();
    void on_buttonknight_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::Promotion *ui;

    QPixmap white_bishop;
    QPixmap white_knight;
    QPixmap white_queen;
    QPixmap white_rook;

    int number;

    void loadImage();

};

#endif // PROMOTION_H
