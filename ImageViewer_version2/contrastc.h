#ifndef CONTRASTC_H
#define CONTRASTC_H

#include <QDialog>

namespace Ui {
class ContrastC;
}

class ContrastC : public QDialog
{
    Q_OBJECT

public:
    explicit ContrastC(QWidget *parent = nullptr);
    ~ContrastC();

signals:
    void getparaContrast(double,double);

public slots:
    void on_buttonBox_accepted();

private:
    Ui::ContrastC *ui;
};

#endif // CONTRASTC_H
