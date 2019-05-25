#include "gauss.h"
#include "ui_gauss.h"
#include <QDebug>

Gauss::Gauss(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gauss)
{
    ui->setupUi(this);
}

Gauss::~Gauss()
{
    delete ui;
}

void Gauss::accept(){
    qDebug()<<"accept";
    bool ok;
    int l = ui->lineEdit->text().toInt(&ok);
    double s = ui->lineEdit_2->text().toDouble(&ok);
    if(ok){
        emit confirmed(l,s);
    }
    close();
}
