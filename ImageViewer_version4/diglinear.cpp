#include "diglinear.h"
#include "ui_diglinear.h"
#include <QDebug>
#include <QRegExp>

using std::vector;

DigLinear::DigLinear(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DigLinear)
{
    ui->setupUi(this);
}

DigLinear::~DigLinear()
{
    delete ui;
}


void DigLinear::accept(){
//    qDebug()<<ui->textEdit->toPlainText();
    QString str = ui->textEdit->toPlainText();
    int num1 = ui->comboBox->currentIndex();
    int num2 = ui->comboBox_2->currentIndex();
    QStringList rows = str.replace("\n","").trimmed().split(";");
    vector<double> data;
    int nCol = -1;
    for(int i=0;i<rows.size()-1;i++){
        if(rows[i].isEmpty()) continue;
        bool ok;
        int tmp;
        ok = parseRow(rows[i],data,tmp);
        if(nCol == -1) nCol = tmp;
        if(!ok || nCol != tmp){
            close();
            return;
        }
    }
    emit confirmed(data,nCol,num1,num2);
    close();
}

bool DigLinear::parseRow(QString row,vector<double>& data,int& nCol){
    nCol = 0;
    QStringList cols = row.trimmed().split(QRegExp("\\s+|\\s*,"));
    for(int i=0;i<cols.size();i++){
        if(cols[i].isEmpty()) continue;
        bool ok;
        double d = cols[i].toDouble(&ok);
        if(ok){
            data.push_back(d);
            nCol++;
        }else{
            return false;
        }
    }
    return true;
}
