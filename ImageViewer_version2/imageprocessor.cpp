#include "imageprocessor.h"
#include <cmath>
#include <QDebug>

ImageProcessor::ImageProcessor()
{

}

QImage ImageProcessor::rgb2Gray(const QImage& img){
    QImage ret(img);
    int w = ret.width();
    int h = ret.height();

    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QRgb rgb = img.pixel(i,j);
            int red = qRed(rgb);
            int green = qGreen(rgb);
            int blue = qBlue(rgb);
            int gray = (red+green+blue)/3;
            ret.setPixel(i,j,qRgb(gray,gray,gray));
        }
    }

    return ret;
}

QImage ImageProcessor::reverse(const QImage& img){
    QImage ret(img);
    int w = ret.width();
    int h = ret.height();

    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QRgb rgb = img.pixel(i,j);
            int red = 255-qRed(rgb);
            int green = 255-qGreen(rgb);
            int blue = 255-qBlue(rgb);
            ret.setPixel(i,j,qRgb(red,green,blue));
        }
    }

    return ret;
}

QImage ImageProcessor::logTransform(const QImage& img,double c){
    QImage ret(img);
    int w = ret.width();
    int h = ret.height();

    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QRgb rgb = img.pixel(i,j);
            int gray = qGray(rgb);
            int newPixel = int(c*log(1+gray/255.0)*255);
            if(newPixel>=255) newPixel=255;
            ret.setPixel(i,j,qRgb(newPixel,newPixel,newPixel));
        }
    }

    return ret;
}

QImage ImageProcessor::ContrastTransform(const QImage& img,double m,double e){

    QImage ret(img);
    int w = ret.width();
    int h = ret.height();

    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QRgb rgb = img.pixel(i,j);
            double gray = qGray(rgb)/255.0;
            int newPixel = int(1/(1+pow(m/gray,e))*255);
            if(newPixel>=255) newPixel=255;
            ret.setPixel(i,j,qRgb(newPixel,newPixel,newPixel));
        }
    }

    return ret;
}

QImage ImageProcessor::hisbalance(const QImage& img){

    QImage ret(img);
    int w = ret.width();
    int h = ret.height();
    double size = w*h;
    int his[256] = {0};
    double p[256] = {0.0};
    double psum[256] = {0.0};
    int hisn[256] = {0};

    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QRgb rgb = img.pixel(i,j);
            int gray = qGray(rgb);
            his[gray]++;
        }
    }

    for(int i=0;i<256;i++){
       p[i] = his[i]/size;
    }

    psum[0] = p[0];
    for(int i=1;i<256;i++){
        psum[i] = p[i] + psum[i-1];
//        qDebug()<<psum[i];
    }

    for(int i=0;i<256;i++){
        hisn[i] = int(psum[i]*256);
//        qDebug()<<hisn[i];
    }

    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QRgb rgb = img.pixel(i,j);
            int gray = qGray(rgb);
            ret.setPixel(i,j,qRgb(hisn[gray],hisn[gray],hisn[gray]));
        }
    }

    return ret;
}
void ImageProcessor::rgb2hsi(double r,double g,double b,double *h,double *s,double *i){
    double temp = sqrt((r-g)*(r-g)+(r-b)*(g-b));
    temp = temp > 0?temp:0.01;
    if(b<=g){
        *h = acos(((r-g+r-b)/2.0)/temp);
    }else{
        *h = 2*pi - acos(((r-g+r-b)/2.0)/temp);
    }
    temp = r+g+b>0?r+g+b:0.01;
    double mint = 0;
    mint = r<g?r:g;
    mint = mint<b?mint:b;
    *s = 1.0-(3.0/temp)*mint;
    *i = (r+g+b)/3.0;
}

void ImageProcessor::hsi2rgb(double h,double s,double i,double *r,double *g,double *b){
    if(h>=0&&h<2*pi/3){
        *b = i*(1.0-s);
        *r = i*(1.0+(s*cos(h))/cos(pi/3.0-h));
        *g = 3.0*i-*b-*r;
    }else if(h>=2*pi/3&&h<4*pi/3){
        *r = i*(1.0-s);
        *g = i*(1.0+(s*cos(h-2*pi/3))/cos(pi-h));
        *b = 3.0*i-*g-*r;
    }else{
        *g = i*(1.0-s);
        *b = i*(1.0+(s*cos(h-4*pi/3))/cos(5*pi/6.0-h));
        *r = 3.0*i-*b-*g;
    }
}

QImage ImageProcessor::hisrgbbalance(const QImage& img){

    QImage ret(img);
    int w = ret.width();
    int h = ret.height();

    typedef struct HSI{
        double h;
        double s;
        double i;
    }hsi;

    hsi **p = new hsi*[w];
    for(int i = 0;i < w;i++)
        p[i] = new hsi[h];

//    qDebug()<<"2";

    double maxi = 0;
    for(int i = 0;i < w;i++)
    {
        for(int j = 0;j < h;j ++)
        {
            QRgb rgb = img.pixel(i,j);
            rgb2hsi(qRed(rgb),qGreen(rgb),qBlue(rgb),&p[i][j].h,&p[i][j].s,&p[i][j].i);
            maxi = maxi > p[i][j].i?maxi:p[i][j].i;
        }
    }
    //qDebug()<<max;

//    qDebug()<<"1";

    int n = int(maxi+0.5);

    int *hisi = new int[n+1];
    double *hisp = new double[n+1];
    double *hispsum = new double[n+1];
    double *hisn = new double[n+1];

    for(int i = 0;i <= n;i++)
        hisi[i] = 0;

    for(int i = 0;i < w;i++)
    {
        for(int j = 0;j < h;j ++)
        {
            hisi[int(p[i][j].i+0.5)]++;
        }
    }

    for(int i = 0;i <= n;i++)
    {
        hisp[i] = (hisi[i]*1.0)/(w*h);
    }

    hispsum[0] = hisp[0];
    for(int i = 1;i <= n;i++)
    {
        hispsum[i] = hispsum[i-1]+hisp[i];
        hisn[i]= n*hispsum[i];
    }

    for(int i=0;i<w;i++)
    {

        for(int j=0;j<h;j++)
        {
            p[i][j].i = hisn[int(p[i][j].i+0.5)];
            double r,g,b;
            hsi2rgb(p[i][j].h,p[i][j].s,p[i][j].i,&r,&g,&b);
            r = r > 255?255:r+0.5;
            g = g > 255?255:g+0.5;
            b = b > 255?255:b+0.5;
            ret.setPixel(i,j,qRgb(int(r),int(g),int(b)));
         }
     }

    return ret;
}
