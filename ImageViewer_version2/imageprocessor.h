#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>
static const double pi = 3.1415926;


class ImageProcessor
{
public:
    ImageProcessor();
    static QImage rgb2Gray(const QImage& img); //节省时间,避免修改
    static QImage reverse(const QImage& img); //节省时间,避免修改
    static QImage logTransform(const QImage& img,double c);
    static QImage ContrastTransform(const QImage& img,double m,double e);
    static QImage hisbalance(const QImage& img); //节省时间,避免修改
    static QImage hisrgbbalance(const QImage& img); //节省时间,避免修改

    static void rgb2hsi(double r,double g,double b,double *h,double *s,double *i);
    static void hsi2rgb(double h,double s,double i,double *r,double *g,double *b);
};

#endif // IMAGEPROCESSOR_H
