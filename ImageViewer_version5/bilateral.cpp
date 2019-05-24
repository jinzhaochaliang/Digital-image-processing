#include "bilateral.h"
#include "ui_bilateral.h"

Bilateral::Bilateral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bilateral)
{
    ui->setupUi(this);
}

Bilateral::~Bilateral()
{
    delete ui;
}

void Bilateral::accept(){
    bool ok;
    int l = ui->lineEdit->text().toInt(&ok);
    double s = ui->lineEdit_2->text().toDouble(&ok);
    double s1 = ui->lineEdit_3->text().toDouble(&ok);
    if(ok){
        emit confirmed(l,s,s1);
    }
    close();
}
