#include "filtersize.h"
#include "ui_filtersize.h"

FilterSize::FilterSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterSize)
{
    ui->setupUi(this);
}

FilterSize::~FilterSize()
{
    delete ui;
}
void FilterSize::accept(){
    bool ok;
    int c = ui->lineEdit->text().toInt(&ok);
    if(ok){
        emit confirmed(c);
    }
    close();
}
