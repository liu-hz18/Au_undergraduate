#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QList>
#include <QStack>
#include <QMap>
#include <QChar>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    int charNum;//命题字母个数
    int varNum;//命题变项个数(命题字母取set)

    QMap<QChar, bool> varMap;//存储命题变项对应的真值
    QList<QChar> varList;//对应于map的字母顺序
    QMap<QChar, int> priorityLevel;//用于存储运算符优先级

    QString mid_formula_show;//用于显示的中缀表达式
    QString mid_formula_cal;//用于计算的中缀表达式

    QList<QChar> preFormula;//前缀表达式
    QList<QChar> backFormula;//后缀表达式
    QStack<QChar> opStack;//运算符栈
    QList<QChar> charList;

    QList<int> minItem;//存储最小项
    QList<int> maxItem;//极大项

    void init();//初始化运算符优先级

    void midToPre();//中缀转前缀
    bool midToBack();//中缀转后缀
    void calcuBackFormula();//由code的二进制计算表达式的实际值，返回结果
    void getNum();//获取命题变项个数与字母个数
    bool isValidBackFormula();//合法后缀表达式
    bool isValidPreFormula();//合法前缀表达式
    void setVarMap(int code);//真值指派

    void showPreFormula();//显示前缀表达式
    void showBackFormula();//显示后缀表达式
    bool showDisjunctiveForm();//显示主析取范式
    void showConjunctiveForm();//显示主合取范式
    void showFormula();//显示由真值表构建的命题表达式

    void createTruthTable();//创建空真值表
    void createTable();//创建表格

};


#endif // DIALOG_H
