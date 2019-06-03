#include "transform.h"
#include "ui_transform.h"
const double PI = 3.1415926;

Transform::Transform(QWidget *parent) :
    QDialog(parent),temp(3,3,0),
    ui(new Ui::Transform)
{
    ui->setupUi(this);
}

Transform::~Transform()
{
    delete ui;
}

void Transform::accept(){

    emit confirmed(temp);
    close();
}

void Transform::on_pushButton_clicked()
{
    bool ok;
    pinyix = ui->lineEdit->text().toDouble(&ok);
    pinyiy = ui->lineEdit_2->text().toDouble(&ok);
    xuanzhuan = ui->lineEdit_3->text().toDouble(&ok);
    suofangx = ui->lineEdit_4->text().toDouble(&ok);
    suofangy = ui->lineEdit_5->text().toDouble(&ok);
    xieqiana = ui->lineEdit_6->text().toDouble(&ok);
    xieqianb = ui->lineEdit_7->text().toDouble(&ok);
    if(ok){
        Matrix<double> m1(3,3,0);
        m1(0,0) = 1;m1(0,1) = 0;m1(0,2) = 0;
        m1(1,0) = 0;m1(1,1) = 1;m1(1,2) = 0;
        m1(2,0) = pinyix;m1(2,1) = pinyiy;m1(2,2) = 1;
        Matrix<double> m2(3,3,0);
        m2(0,0) = cos(xuanzhuan*PI/180);m2(0,1) = sin(xuanzhuan*PI/180);m2(0,2) = 0;
        m2(1,0) = -sin(xuanzhuan*PI/180);m2(1,1) = cos(xuanzhuan*PI/180);m2(1,2) = 0;
        m2(2,0) = 0;m2(2,1) = 0;m2(2,2) = 1;
        Matrix<double> m3(3,3,0);
        m3(0,0) = suofangx;m3(0,1) = 0;m3(0,2) = 0;
        m3(1,0) = 0;m3(1,1) = suofangy;m3(1,2) = 0;
        m3(2,0) = 0;m3(2,1) = 0;m3(2,2) = 1;
        Matrix<double> m4(3,3,0);
        m4(0,0) = 1;m4(0,1) = xieqianb;m4(0,2) = 0;
        m4(1,0) = xieqiana;m4(1,1) = 1;m4(1,2) = 0;
        m4(2,0) = 0;m4(2,1) = 0;m4(2,2) = 1;
        cout<<m1;
        cout<<m2;
        cout<<m3;
        cout<<m4;
        temp = m1 * m2 * m3 * m4;
        cout<<temp;
        ui->textEdit->setText(QString::number(temp(0,0)));
        ui->textEdit_2->setText(QString::number(temp(0,1)));
        ui->textEdit_3->setText(QString::number(temp(0,2)));
        ui->textEdit_4->setText(QString::number(temp(1,0)));
        ui->textEdit_5->setText(QString::number(temp(1,1)));
        ui->textEdit_6->setText(QString::number(temp(1,2)));
        ui->textEdit_7->setText(QString::number(temp(2,0)));
        ui->textEdit_8->setText(QString::number(temp(2,1)));
        ui->textEdit_9->setText(QString::number(temp(2,2)));
    }
}
