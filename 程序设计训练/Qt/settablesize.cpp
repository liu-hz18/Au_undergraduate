#include "settablesize.h"
#include "ui_settablesize.h"

void SetTableSize::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_moving = true;
        m_lastPos = event->globalPos() - pos();
    }
    return QWidget::mousePressEvent(event);
}

void SetTableSize::mouseMoveEvent(QMouseEvent *event)
{
    if(m_moving && (event->buttons() == Qt::LeftButton) && ((event->globalPos() - m_lastPos).manhattanLength() > QApplication::startDragDistance())){
        move(event->globalPos() - m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}

void SetTableSize::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_moving = false;
}

SetTableSize::SetTableSize(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetTableSize)
{
    ui->setupUi(this);
    ui->label_4->setToolTip("Input Format: x,y");
    ui->label_5->setToolTip("Input Format: x,y");
}

SetTableSize::~SetTableSize()
{
    delete ui;
}

bool SetTableSize::isOnMargin(int x, int y)
{
    if((x == 1 || x == this->column) || (y == 1 || y == this->row))return true;
    else return false;
}

void SetTableSize::on_pushButton_4_clicked()
{
    this->row = ui->spinBox->value();
    this->column = ui->spinBox_2->value();

    QString str = ui->lineEdit->text();    
    QStringList sl = str.split(",");
    QStringList::Iterator iter;
    for(iter = sl.begin();iter != sl.end();iter++){
        this->input_list.append(iter->toInt());
    }

    str = ui->lineEdit_2->text();
    sl = str.split(",");
    this->output_x = sl.first().toInt();
    this->output_y = sl.last().toInt();

    if((row <= 3 && column <= 3) || row <= 0 ||column <=0 || row >= 16 || column >= 16){
        QString title = "Invalid Input";
        QString info = "Hint:\nValue of row and column CANNOT be smaller than 3 simultaneously.";
        QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
        QMessageBox::critical(this,title,info,QMessageBox::Ok,defaultButton);
    }
    else{
        bool flag = true;
        for(iter = sl.begin();iter != sl.end();iter ++){
            int tempx = iter->toInt();
            int tempy = (++iter)->toInt();
            if((!isOnMargin(tempx,tempy)) || tempx < 0 || tempy < 0){
                QString title = "Invalid Input";
                QString info = "Value of INPUT is NOT on the margin.";
                QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
                QMessageBox::critical(this,title,info,QMessageBox::Ok,defaultButton);
                flag = false;
                break;
            }
        }
        if(!isOnMargin(output_x,output_y) || output_x < 0 || output_y < 0){
            QString title = "Invalid Input";
            QString info = "Value of OUTPUT is NOT on the margin.";
            QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
            QMessageBox::critical(this,title,info,QMessageBox::Ok,defaultButton);
            flag = false;
        }
        if(flag){
            emit sendRow(this->row);
            emit sendColumn(this->column);
            emit sendInput(this->input_list);
            emit sendOutput_x(this->output_x);
            emit sendOutput_y(this->output_y);
            this->close();
        }
    }
}

