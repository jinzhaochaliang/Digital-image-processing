#ifndef FILTERSIZE_H
#define FILTERSIZE_H

#include <QDialog>

namespace Ui {
class FilterSize;
}

class FilterSize : public QDialog
{
    Q_OBJECT

public:
    explicit FilterSize(QWidget *parent = nullptr);
    ~FilterSize();
public slots:
    void accept();

signals:
    void confirmed(int);
private:
    Ui::FilterSize *ui;
};

#endif // FILTERSIZE_H
