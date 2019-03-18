#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "mypixmapitem.h"
#include "dialogt.h"
#include "contrastc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileDialog *fd;
    QGraphicsScene *scene;
//    QGraphicsPixmapItem *pitem;
    MyPixmapItem *pitem;
    QFileInfoList imgs;
    int idx;
    void showImage();
    void showImage(QImage img);
    void reset();
    QImage getCurrentImage() const;

    DialogT *dialog;
    ContrastC *contrast;


public slots:
    void on_openButton_clicked();
    void on_resetButton_clicked();
    void on_lastButton_clicked();
    void on_nextButton_clicked();
    void on_actionrgb2gray_triggered();
    void on_actionlog_triggered();
    void on_actionreverse_triggered();
    void on_actioncontrast_triggered();
    void on_actionhisbalance_triggered();
    void on_actionhisrgbbalance_triggered();

    void on_DialogT_confirmed(double);
    void on_ContrastC_getparaContrast(double,double);
};

#endif // MAINWINDOW_H
