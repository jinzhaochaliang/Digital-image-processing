#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QMessageBox>
#include <QStack>
#include <opencv2/opencv.hpp>

#include "editimage.h"
#include "drawwindow.h"
#include "colortransfer.h"

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    editimage *editimagewindow;
    drawWindow *drawwindow;

    void createMenus();
    void createActions();
    void updateimage();
    void balancecolor(Mat &bitmap,int value);

public slots:
    void receiveMat(Mat data);

    void openfileslot();
    void clearimageslot();
    void laststepslot();
    void nextstepslot();
    void saveslot();
    void exitslot();

    void rotateslot();
    void brightnessslot();
    void sharpenslot();
    void awbslot();
    void colortranslot();

    void blackandwhiteslot();
    void reminiscenceslot();
    void relievoslot();
    void binaryzationslot();
    void sketchslot();
    void lineslot();
    void glassslot();
    void corrosionslot();
    void swellslot();
    void cartoonizeslot();

    void buffingslot();
    void thinfaceslot();
    void skinwhiteningslot();
    void eyeslot();
    void cuteslot();
    void Christmasslot();

    void paintslot();

    void ShowLabelslot();
    void AddButtonHideslot();

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *clearAction;
    QAction *laststepAction;
    QAction *nextstepAction;

    QMenu *editMenu;
    QAction *rotateAction;
    QAction *brightnessAction;
    QAction *sharpenAction;//锐化
    QAction *awbAction;//白平衡
    QAction *colortranAction; //颜色转移

    QMenu *filterMenu;
    QAction *blackandwhiteAction;
    QAction *relievoAction; //浮雕
    QAction *reminiscenceAction; //怀旧
    QAction *binaryzationAction; //木刻，二值化
    QAction *sketchAction;
    QAction *lineAction;
    QAction *glassAction;//毛玻璃
    QAction *corrosionAction;//腐蚀-暗变大，亮变小
    QAction *swellAction;//膨胀-亮变大，暗变小
    QAction *cartoonAction;

    QMenu *beautyMenu;
    QAction *buffingAction; //磨皮
    QAction *thinfaceAction;
    QAction *skinwhiteningAction;
    QAction *eyeAction;
    QAction *cuteAction;
    QAction *ChristmasAction;
    QMenu *drawMenu;
    QAction *paintAction;

    Mat image;
    Mat imagetemp;

    QStack<Mat> matstack;
    QStack<Mat> mattempstack;
    String facePath="haarcascade_frontalface_alt2.xml";
    String eyePath="haarcascade_eye_tree_eyeglasses.xml";
};

#endif // MAINWINDOW_H
