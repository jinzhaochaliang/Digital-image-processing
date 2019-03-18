#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QToolButton>

using namespace cv;

namespace Ui {
class drawWindow;
}

class drawWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit drawWindow(QWidget *parent = nullptr);
    Mat drawmat;
    Mat drawtempmat;
    void draw();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void updatedraw();
    void createtools();
    int cvAdd4cMat_q(cv::Mat &dst, cv::Mat &scr, double scale);

    ~drawWindow();


public slots:
    void okbuttonslot();
    void cancelbuttonslot();
    void updateslot();

    void normalslot();
    void mosaicslot();
    void rectslot();
signals:
    void sendMat(Mat);

private:
    Ui::drawWindow *ui;

    QImage img;
    QPixmap pixmap;
    QPoint lastPos;
    QPoint endPos;
    bool isDrawing;

    bool face[13];
    double scale;

    QToolButton *normalButton;
    QToolButton *mosaicButton;
    QToolButton *rectButton;

    int drawchoice = 0;
};

#endif // DRAWWINDOW_H
