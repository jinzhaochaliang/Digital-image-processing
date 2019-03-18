#include "dialogt.h"
#include "ui_dialogt.h"
#include <QDebug>

DialogT::DialogT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogT)
{
    ui->setupUi(this);
}

DialogT::~DialogT()
{
    delete ui;
}

void DialogT::accept(){
    qDebug()<<"accept";
    bool ok;
    double c = ui->lineEdit->text().toDouble(&ok);
    if(ok){
        emit confirmed(c);
    }
    close();
}
