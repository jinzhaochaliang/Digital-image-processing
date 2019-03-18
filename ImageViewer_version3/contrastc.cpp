#include "contrastc.h"
#include "ui_contrastc.h"
#include <QDebug>

ContrastC::ContrastC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContrastC)
{
    ui->setupUi(this);
}

ContrastC::~ContrastC()
{
    delete ui;
}

void ContrastC::on_buttonBox_accepted()
{
    qDebug()<<"accept";
    bool ok;
    double m = ui->lineEdit->text().toDouble(&ok);
    double e = ui->lineEdit_2->text().toDouble(&ok);
    if(ok){
        emit getparaContrast(m,e);
    }
    close();
}
