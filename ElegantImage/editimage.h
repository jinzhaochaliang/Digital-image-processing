#ifndef EDITIMAGE_H
#define EDITIMAGE_H

#include <QDialog>
#include <QImage>
#include <QSlider>
#include <opencv2/opencv.hpp>
using namespace cv;

namespace Ui {
class editimage;
}

class editimage : public QDialog
{
    Q_OBJECT

public:
    explicit editimage(QWidget *parent = nullptr);
    Mat editmat;
    Mat edittempmat;
    void updateeditimage();
    float averagel(Mat &src);
    ~editimage();
public slots:
    void updateslot();
    void okbuttonslot();
    void cancelbuttonslot();

    void editbrightnessslot();
    void saturabilityslot();
    void xuhuaslot();
    void ruiduslot();
    void brightpartslot();
    void darkpartslot();
    void colortempslot();

private:
    Ui::editimage *ui;   
signals:
    void sendMat(Mat);
};

#endif // EDITIMAGE_H
