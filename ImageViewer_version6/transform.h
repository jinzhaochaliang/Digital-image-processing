#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QDialog>
#include "matrix.h"

namespace Ui {
class Transform;
}

class Transform : public QDialog
{
    Q_OBJECT

public:
    explicit Transform(QWidget *parent = nullptr);
    ~Transform();

public slots:
    void accept();

signals:
    void confirmed(Matrix<double>);

private slots:
    void on_pushButton_clicked();

private:
    Matrix<double> temp;
    double pinyix,pinyiy;
    double xuanzhuan;
    double suofangx,suofangy;
    double xieqiana,xieqianb;
    Ui::Transform *ui;
};

#endif // TRANSFORM_H
