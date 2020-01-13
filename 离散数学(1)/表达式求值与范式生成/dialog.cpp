
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->init();
    ui->setupUi(this);
    charList<<'P'<<'Q'<<'R'<<'S'<<'T'<<'U'<<'A'<<'B'<<'C';
    ui->pushButton->setEnabled(false);
    ui->label_10->setAlignment(Qt::AlignHCenter);
    //键值信号槽构建
    connect(ui->pushButton_P, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('P');
        this->mid_formula_show.append('P');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_R, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('R');
        this->mid_formula_show.append('R');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_S, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('S');
        this->mid_formula_show.append('S');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_a, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('A');
        this->mid_formula_show.append('A');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_b, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('B');
        this->mid_formula_show.append('B');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_c, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('C');
        this->mid_formula_show.append('C');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_t, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('T');
        this->mid_formula_show.append('T');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_u, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('U');
        this->mid_formula_show.append('U');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_Q, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('Q');
        this->mid_formula_show.append('Q');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    //or = |
    connect(ui->pushButton_or, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('|');
        this->mid_formula_show.append("∨");
        ui->lineEdit->setText(this->mid_formula_show);
    });
    //and = &
    connect(ui->pushButton_and, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('&');
        this->mid_formula_show.append("∧");
        ui->lineEdit->setText(this->mid_formula_show);
    });
    //not = !
    connect(ui->pushButton_not, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('!');
        this->mid_formula_show.append("¬");
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_left, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('(');
        this->mid_formula_show.append('(');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_right, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append(')');
        this->mid_formula_show.append(')');
        ui->lineEdit->setText(this->mid_formula_show);
    });
    //then = '>'
    connect(ui->pushButton_then, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('>');
        this->mid_formula_show.append("→");
        ui->lineEdit->setText(this->mid_formula_show);
    });
    //equal = '='
    connect(ui->pushButton_equal, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('=');
        this->mid_formula_show.append("↔");
        ui->lineEdit->setText(this->mid_formula_show);
    });
    //ornot = #
    connect(ui->pushButton_ornot, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('#');
        this->mid_formula_show.append("↓");
        ui->lineEdit->setText(this->mid_formula_show);
    });
    //andnot = $
    connect(ui->pushButton_andnot, &QPushButton::clicked, [=](){
        this->mid_formula_cal.append('$');
        this->mid_formula_show.append("↑");
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_caculate, &QPushButton::clicked, [=](){
        qDebug()<<mid_formula_cal;
        if(this->midToBack()){
            this->midToPre();
            this->calcuBackFormula();
            this->showDisjunctiveForm();
            this->showConjunctiveForm();
        }else{
            ui->tableWidget->clearContents();
        }
    });
    connect(ui->pushButton_delete, &QPushButton::clicked, [=](){
        mid_formula_cal = mid_formula_cal.left(mid_formula_show.size() - 1);
        mid_formula_show = mid_formula_show.left(mid_formula_show.size() - 1);
        ui->lineEdit->setText(this->mid_formula_show);
    });
    connect(ui->pushButton_table, &QPushButton::clicked, [=](){
        ui->pushButton->setEnabled(false);
        this->createTruthTable();
    });
    connect(ui->pushButton, &QPushButton::clicked, [=](){
        ui->lineEdit->setText("");
        if(this->showDisjunctiveForm()){
            this->showConjunctiveForm();
            this->showFormula();
            if(this->midToBack()){
                this->midToPre();
            }
        }
    });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::init(){
    priorityLevel.insert('!',5);
    priorityLevel.insert('&',4);
    priorityLevel.insert('$',4);
    priorityLevel.insert('|',3);
    priorityLevel.insert('#',3);
    priorityLevel.insert('>',2);
    priorityLevel.insert('=',1);
}

bool isLetter(const QChar& str){
    if(str == 'P' || str == 'Q' || str == 'R' || str == 'A' || str == 'B' || str == 'C' || str == 'S' || str == 'T' || str == 'U'){
        return true;
    }else return false;
}

void Dialog::midToPre(){
    if(ui->lineEdit->text() == "T"){
        ui->lineEdit_2->setText("T");
        ui->lineEdit_3->setText("T");
        return ;
    }else if(ui->lineEdit->text() == "F"){
        ui->lineEdit_2->setText("F");
        ui->lineEdit_3->setText("F");
        return ;
    }
    this->preFormula.clear();
    opStack.clear();
    for(int i = mid_formula_cal.size() - 1;i >= 0;i --){
        if(isLetter(mid_formula_cal[i])){
            preFormula.append(mid_formula_cal[i]);
        }else{
            if(mid_formula_cal[i] == ')'){
                opStack.push(mid_formula_cal[i]);
            }else if(mid_formula_cal[i] == '!'){
                preFormula.append(mid_formula_cal[i]);
            }else if(opStack.isEmpty()){
                opStack.push(mid_formula_cal[i]);
            }else if(opStack.top() == ')'){
                opStack.push(mid_formula_cal[i]);
            }else if(mid_formula_cal[i] == '('){
                QChar last;
                while((!opStack.isEmpty()) && opStack.top() != ')'){
                    preFormula.append(last = opStack.pop());
                }
                if(opStack.isEmpty() || opStack.top() != ')'){
                    ui->lineEdit_3->setText("ERROR!");
                    ui->lineEdit_2->setText("ERROR!");
                    return;
                }else opStack.pop();
            }else if(priorityLevel[mid_formula_cal[i]] >= priorityLevel[opStack.top()]){
                opStack.push_back(mid_formula_cal[i]);
            }else if(priorityLevel[mid_formula_cal[i]] < priorityLevel[opStack.top()]){
                while((!opStack.isEmpty()) && priorityLevel[mid_formula_cal[i]] < priorityLevel[opStack.top()]){
                    QChar temp = opStack.pop();
                    if(temp != ')'){
                        preFormula.append(temp);
                    }
                    if((!opStack.isEmpty()) && opStack.top() == ')'){
                        //opStack.pop();
                        break;
                    }
                }
                opStack.push_back(mid_formula_cal[i]);
            }
        }
    }
    while(!opStack.isEmpty()){
        QChar temp = opStack.pop();
        if(temp != ')'){
            preFormula.append(temp);
        }
    }
    for(int k = 0; k < (preFormula.size()/2); k++)preFormula.swap(k,preFormula.size() - (1+k));
    if(isValidPreFormula()){
        showPreFormula();
    }else{
        ui->lineEdit_2->setText("ERROR!");
        ui->lineEdit_3->setText("ERROR!");
    }
}

bool Dialog::midToBack(){
    this->backFormula.clear();
    opStack.clear();
    if(ui->lineEdit->text() == "T"){
        ui->lineEdit_2->setText("T");
        ui->lineEdit_3->setText("T");
        return true;
    }else if(ui->lineEdit->text() == "F"){
        ui->lineEdit_2->setText("F");
        ui->lineEdit_3->setText("F");
        return true;
    }
    //错误检查
    if((!isLetter(mid_formula_cal[mid_formula_cal.size() - 1])) && mid_formula_cal[mid_formula_cal.size() - 1] != ')'){
        ui->lineEdit_3->setText("ERROR!");
        ui->lineEdit_2->setText("ERROR!");
        return false;
    }
    if((!isLetter(mid_formula_cal[0])) && mid_formula_cal[0] != '!' && mid_formula_cal[0] != '('){
        ui->lineEdit_3->setText("ERROR!");
        ui->lineEdit_2->setText("ERROR!");
        return false;
    }
    for(int i = 0;i < mid_formula_cal.size() - 1;i ++){
        if(mid_formula_cal[i] == '!' && (!isLetter(mid_formula_cal[i + 1])) && mid_formula_cal[i + 1] != '('){
            ui->lineEdit_3->setText("ERROR!");
            ui->lineEdit_2->setText("ERROR!");
            return false;
        }
    }
    //计算
    for(int i = 0;i < mid_formula_cal.size();i++){
        if(isLetter(mid_formula_cal[i])){
            backFormula.append(mid_formula_cal[i]);
        }else{
            if(mid_formula_cal[i] == '(' || priorityLevel[mid_formula_cal[i]] == 1){
                opStack.push_back(mid_formula_cal[i]);
            }else if(opStack.isEmpty()){
                opStack.push_back(mid_formula_cal[i]);
            }else if(opStack.top() == '('){
                opStack.push_back(mid_formula_cal[i]);
            }else if(mid_formula_cal[i] == ')'){
                QChar last;
                while((!opStack.isEmpty()) && opStack.top() != '('){
                    backFormula.append(opStack.pop());
                }
                qDebug()<<last;
                if(opStack.isEmpty() || opStack.top() != '('){
                    ui->lineEdit_3->setText("ERROR!");
                    ui->lineEdit_2->setText("ERROR!");
                    return false;
                }else opStack.pop();
            }else if(priorityLevel[mid_formula_cal[i]] >= priorityLevel[opStack.top()]){
                opStack.push_back(mid_formula_cal[i]);
            }else if(priorityLevel[mid_formula_cal[i]] < priorityLevel[opStack.top()]){
                while((!opStack.isEmpty()) && priorityLevel[mid_formula_cal[i]] < priorityLevel[opStack.top()]){
                    QChar temp = opStack.pop();
                    if(temp != '('){
                        backFormula.append(temp);
                    }
                    if((!opStack.isEmpty()) && opStack.top() == '('){
                        //opStack.pop();
                        break;
                    }
                }
                opStack.push_back(mid_formula_cal[i]);
            }
        }
    }
    while(!opStack.isEmpty()){
        QChar temp;
        if((temp = opStack.pop()) != '('){
            backFormula.append(temp);
        }
    }
    getNum();
    if(isValidBackFormula()){
        showBackFormula();
    }else{
        ui->lineEdit_2->setText("ERROR!");
        ui->lineEdit_3->setText("ERROR!");
        return false;
    }
    return true;
}

void Dialog::getNum(){
    charNum = 0;
    varNum = 0;
    varMap.clear();
    varList.clear();
    for(int i = 0;i < backFormula.size();i ++){
        if(isLetter(backFormula[i])){
            charNum ++;
            if(!varMap.contains(backFormula[i])){
                varMap.insert(backFormula[i],0);
                varList.append(backFormula[i]);
                varNum ++;
            }
        }
    }
    ui->label_8->setText("命题变项个数:" + QString::number(varNum));
}

bool Dialog::isValidBackFormula()
{
    QStack<QChar> var;
    if(backFormula.contains(')')||backFormula.contains('('))return false;
    for(int i = 0;i < backFormula.size();i++){
        if(isLetter(backFormula[i])){
            var.push_back(backFormula[i]);
        }else{
            if(backFormula[i] != '!' && var.size() < 2){
                return false;
            }else if(var.size() < 1){
                return false;
            }
        }
    }
    return true;
}

bool Dialog::isValidPreFormula()
{
    QStack<QChar> var;
    if(preFormula.contains('(')||preFormula.contains(')'))return false;
    for(int i = preFormula.size() - 1;i >= 0;i--){
        if(isLetter(preFormula[i])){
            var.push_back(preFormula[i]);
        }else{
            if(preFormula[i] != '!' && var.size() < 2){
                return false;
            }else if(var.size() < 1){
                return false;
            }
        }
    }
    return true;
}

void Dialog::setVarMap(int code)
{
    qDebug()<<code;
    qDebug()<<varList;
    for(int i = 0;i < varNum;i++){
        varMap[varList[varNum - i - 1]] = bool(code & (1 << i));
    }
    qDebug()<<varMap;
}

void Dialog::showPreFormula(){
    QString pre;
    for(int i = 0;i < preFormula.size();i++){
        if(preFormula[i] == '!')pre.append("¬");
        else if(preFormula[i] == '&')pre.append("∧");
        else if(preFormula[i] == '|')pre.append("∨");
        else if(preFormula[i] == '#')pre.append("↓");
        else if(preFormula[i] == '$')pre.append("↑");
        else if(preFormula[i] == '>')pre.append("→");
        else if(preFormula[i] == '=')pre.append("↔");
        else pre.append(preFormula[i]);
    }
    ui->lineEdit_2->setText(pre);
}

void Dialog::showBackFormula(){
    QString back;
    for(int i = 0;i < backFormula.size();i++){
        if(backFormula[i] == '!')back.append("¬");
        else if(backFormula[i] == '&')back.append("∧");
        else if(backFormula[i] == '|')back.append("∨");
        else if(backFormula[i] == '#')back.append("↓");
        else if(backFormula[i] == '$')back.append("↑");
        else if(backFormula[i] == '>')back.append("→");
        else if(backFormula[i] == '=')back.append("↔");
        else back.append(backFormula[i]);
    }
    ui->lineEdit_3->setText(back);
}

void Dialog::calcuBackFormula(){
    //创建表格
    createTable();
    //构建表头
    QStringList hheader;
    for(int i = 0;i < varNum;i ++){
        hheader<<QString(varList[i]);
    }
    ui->tableWidget->setHorizontalHeaderLabels(hheader);
    //真值指派
    for(int i = 0;i < (1<<varNum);i ++){
        setVarMap(i);
        QStack<bool> var;
        for(int j = 0;j < backFormula.size();j++){
            if(isLetter(backFormula[j])){
                var.push_back(varMap[backFormula[j]]);
            }else{
                if(backFormula[j] == '!'){
                    bool temp = var.pop();
                    var.push_back(!temp);
                }else{
                    bool temp1 = var.pop();
                    bool temp2 = var.pop();
                    if(backFormula[j] == '&')var.push_back(temp1&temp2);
                    else if(backFormula[j] == '|')var.push_back(temp1|temp2);
                    else if(backFormula[j] == '>')var.push_back((!temp2)|temp1);
                    else if(backFormula[j] == '=')var.push_back(temp1 == temp2);
                    else if(backFormula[j] == '#')var.push_back(!(temp1|temp2));
                    else if(backFormula[j] == '$')var.push_back(!(temp1&temp2));
                }
            }
        }
        qDebug()<<var[0];
        for(int j = 0;j < varNum;j++){
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(varMap[varList[j]])));
        }
        ui->tableWidget->setItem(i, varNum, new QTableWidgetItem(QString::number(var[0])));
    }
    ui->tableWidget->show();
}

void Dialog::showConjunctiveForm(){
    QString conjunctive;
    conjunctive.append("∧(");
    maxItem.clear();
    for(int i = 0;i < (1<<varNum);i ++){
        if(!minItem.contains(i)){
            maxItem.append(i);
        }
    }
    if(maxItem.size() == 0){
        ui->lineEdit_5->setText("None");
        return;
    }
    for(int i = 0;i < maxItem.size();i ++){
        maxItem[i] = (1<<varNum) - 1 - maxItem[i];
    }
    std::sort(maxItem.begin(),maxItem.end());
    for(int i = 0;i < maxItem.size();i++){
        conjunctive.append(QString::number(maxItem[i]) + ',');
    }
    conjunctive = conjunctive.left(conjunctive.size() - 1);
    conjunctive.append(")");
    ui->lineEdit_5->setText(conjunctive);
}

void Dialog::showFormula()
{
    mid_formula_cal.clear();
    mid_formula_show.clear();
    bool flag = (minItem.size() <= maxItem.size())?true:false;
    if(flag){
        if(minItem.size() == 0){
            ui->lineEdit->setText("F");
            return;
        }
        QString formula;
        for(int i = 0;i < minItem.size();i++){
            QString _min;
            if(varNum > 1){
                _min.append("(");
                mid_formula_cal.append("(");
            }
            QStack<int> bin;
            int temp = minItem[i];
            while(temp){
                bin.push_back(temp & 1);
                temp >>= 1;
            }
            while(bin.size() < varNum){
                bin.push_front(0);
            }
            qDebug()<<temp<<bin;
            int j = 0;
            while(!bin.isEmpty()){
                int m = bin.pop();
                qDebug()<<m;
                if(m == 0){
                    _min.append("¬");
                    _min.append(charList[j]);
                    mid_formula_cal.append("!");
                    mid_formula_cal.append(charList[j++]);
                }else if(m == 1){
                    _min.append(charList[j]);
                    mid_formula_cal.append(charList[j++]);
                }
                _min.append("∧");
                mid_formula_cal.append("&");
            }
            _min = _min.left(_min.size() - 1);
            mid_formula_cal = mid_formula_cal.left(mid_formula_cal.size() - 1);
            if(varNum > 1){
                _min.append(")");
                mid_formula_cal.append(")");
            }
            formula.append(_min + "∨");
            mid_formula_cal.append("|");
        }
        formula = formula.left(formula.size() - 1);
        mid_formula_cal = mid_formula_cal.left(mid_formula_cal.size() - 1);
        ui->lineEdit->setText(formula);
        mid_formula_show = formula;
    }else{
        if(maxItem.size() == 0){
            ui->lineEdit->setText("T");
            return;
        }
        QString formula;
        for(int i = 0;i < maxItem.size();i++){
            QString _min;
            if(varNum > 1){
                _min.append("(");
                mid_formula_cal.append("(");
            }
            QStack<int> bin;
            int temp = maxItem[i];
            while(temp){
                bin.push_back(temp & 1);
                temp >>= 1;
            }
            while(bin.size() < varNum){
                bin.push_front(0);
            }
            qDebug()<<temp<<bin;
            int j = 0;
            while(!bin.isEmpty()){
                int m = bin.pop();
                qDebug()<<m;
                if(m == 0){
                    _min.append("¬");
                    _min.append(charList[j]);
                    mid_formula_cal.append("!");
                    mid_formula_cal.append(charList[j++]);
                }else if(m == 1){
                    _min.append(charList[j]);
                    mid_formula_cal.append((charList[j++]));
                }
                _min.append("∨");
                mid_formula_cal.append("|");
            }
            _min = _min.left(_min.size() - 1);
            mid_formula_cal = mid_formula_cal.left(mid_formula_cal.size() - 1);
            if(varNum > 1){
                _min.append(")");
                mid_formula_cal.append(")");
            }
            formula.append(_min + "∧");
            mid_formula_cal.append("&");
        }
        formula = formula.left(formula.size() - 1);
        mid_formula_cal = mid_formula_cal.left(mid_formula_cal.size() - 1);
        ui->lineEdit->setText(formula);
        mid_formula_show = formula;
    }
}

bool Dialog::showDisjunctiveForm(){
    //检查是否有误
    QList<int> con;
    for(int i = 0;i < ui->tableWidget->rowCount();i++){
        int temp = 0;
        for(int j = 0;j < ui->tableWidget->columnCount() - 1;j ++){
            if(ui->tableWidget->item(0,0) == nullptr){
                QMessageBox::warning(this, "Wrong Input", "Please input a number 0 or 1 in the table!", QMessageBox::Ok, QMessageBox::Ok);
                return false;
            }else if(ui->tableWidget->item(i,j)->text() != "0" && ui->tableWidget->item(i, j)->text() != "1"){
                QMessageBox::warning(this, "Wrong Input", "Please input a number 0 or 1 in the table!", QMessageBox::Ok, QMessageBox::Ok);
                return false;
            }else{
                temp += ui->tableWidget->item(i ,j)->text().toInt() << (varNum - 1 - j);
            }
        }
        if(con.contains(temp)){
            QMessageBox::warning(this, "Wrong Input", "The input contains SAME conditions!", QMessageBox::Ok, QMessageBox::Ok);
            return false;
        }else{
            con.push_back(temp);
        }
    }
    //进行读入
    minItem.clear();
    for(int i = 0;i < ui->tableWidget->rowCount();i ++){
        QString test = ui->tableWidget->item(i, ui->tableWidget->columnCount() - 1)->text();
        if(test != "0" && test != "1"){
            QMessageBox::warning(this, "Wrong Input", "Please input a number 0 or 1 in the table!", QMessageBox::Ok, QMessageBox::Ok);
            return false;
        }
        int state = test.toInt();
        if(state == 1){
            int temp = 0;
            for(int j = 0;j < ui->tableWidget->columnCount() - 1;j ++){
                QString t = ui->tableWidget->item(i, j)->text();
                temp += t.toInt() << (varNum - j - 1);
            }
            this->minItem.append(temp);
        }
    }
    if(minItem.size() == 0){
        ui->lineEdit_4->setText("None");
        return true;
    }
    std::sort(minItem.begin(),minItem.end());
    QString disjunctive;
    disjunctive.append("∨(");
    for(int i = 0;i < minItem.size();i ++){
        disjunctive.append(QString::number(minItem[i]) + ',');
    }
    disjunctive = disjunctive.left(disjunctive.size() - 1);
    disjunctive.append(")");
    ui->lineEdit_4->setText(disjunctive);
    return true;
}

void Dialog::createTruthTable()
{
    varNum = ui->spinBox->value();
    if(varNum <= 0 || varNum > 9){
        QMessageBox::warning(this, "Number out of range", "Please input a number in [1,9]", QMessageBox::Ok, QMessageBox::Ok);
    }else{
        createTable();
        ui->pushButton->setEnabled(true);
    }
}

void Dialog::createTable()
{
    //创建表格
    ui->tableWidget->setRowCount((1<<varNum));
    ui->tableWidget->setColumnCount(varNum + 1);
    ui->tableWidget->clearContents();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    //构建表头
    QStringList hheader;
    for(int i = 0;i < varNum;i ++){
        hheader<<QString(charList[i]);
    }
    hheader<<"Re";
    ui->tableWidget->setHorizontalHeaderLabels(hheader);
}
