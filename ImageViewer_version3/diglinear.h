#ifndef DIGLINEAR_H
#define DIGLINEAR_H

#include <QDialog>
#include <vector>

namespace Ui {
class DigLinear;
}

class DigLinear : public QDialog
{
    Q_OBJECT

public:
    explicit DigLinear(QWidget *parent = nullptr);
    ~DigLinear();

public slots:
    void accept();

private:
    Ui::DigLinear *ui;
    bool parseRow(QString,std::vector<double>&,int&);

signals:
    void confirmed(std::vector<double>,int,int,int);
};

#endif // DIGLINEAR_H
