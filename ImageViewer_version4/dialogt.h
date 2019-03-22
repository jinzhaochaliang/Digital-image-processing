#ifndef DIALOGT_H
#define DIALOGT_H

#include <QDialog>

namespace Ui {
class DialogT;
}

class DialogT : public QDialog
{
    Q_OBJECT

public:
    explicit DialogT(QWidget *parent = nullptr);
    ~DialogT();

public slots:
    void accept();

signals:
    void confirmed(double);

private:
    Ui::DialogT *ui;
};

#endif // DIALOGT_H
