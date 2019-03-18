#include "editimage.h"
#include "ui_editimage.h"

editimage::editimage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editimage)
{
    ui->setupUi(this);
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(okbuttonslot()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(cancelbuttonslot()));
    connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(xuhuaslot()));
    connect(ui->horizontalSlider_2,SIGNAL(sliderReleased()),this,SLOT(editbrightnessslot()));
    connect(ui->horizontalSlider_3,SIGNAL(sliderReleased()),this,SLOT(editbrightnessslot()));
     connect(ui->horizontalSlider_4,SIGNAL(sliderReleased()),this,SLOT(saturabilityslot()));
    connect(ui->horizontalSlider_6,SIGNAL(sliderReleased()),this,SLOT(brightpartslot()));
    connect(ui->horizontalSlider_7,SIGNAL(sliderReleased()),this,SLOT(darkpartslot()));
    connect(ui->horizontalSlider_8,SIGNAL(sliderReleased()),SLOT(colortempslot()));

}

editimage::~editimage()
{
    delete ui;
}
void editimage::ruiduslot(){

}
void editimage::xuhuaslot(){
    editmat = edittempmat.clone();
    int a = ui->horizontalSlider->value();
    blur(editmat,editmat,Size(a,a));
    updateeditimage();
}
void editimage::editbrightnessslot(){
    /*
     *
     * g(x) = af(x)+b 增益与偏置
     *
     */
    editmat = edittempmat.clone();
    double a = (ui->horizontalSlider_3->value())*0.01;
    int b = ui->horizontalSlider_2->value()-100;
    for(int x=0;x<editmat.rows;x++){
        for(int y=0;y<editmat.cols;y++){
            for(int c=0;c<3;c++){
               editmat.at<Vec3b>(x,y)[c] = saturate_cast<uchar>(a * (editmat.at<Vec3b>(x,y)[c])+b);
            }
        }
    }
    updateeditimage();
}
void editimage::saturabilityslot()
{
    editmat=edittempmat.clone();
    double s=ui->horizontalSlider_4->value()-50;
    for(int x=0;x<editmat.rows;x++){
        for(int y=0;y<editmat.cols;y++){
            for(int c=0;c<3;c++){
                if(editmat.at<Vec3b>(x,y)[c]<128){
                     editmat.at<Vec3b>(x,y)[c] = saturate_cast<uchar>(editmat.at<Vec3b>(x,y)[c]-s);
                }
                else
                    editmat.at<Vec3b>(x,y)[c] = saturate_cast<uchar>(editmat.at<Vec3b>(x,y)[c]+s);
            }
        }
    }
    updateeditimage();
}
void editimage::brightpartslot()
{
    editmat=edittempmat.clone();
     int b = ui->horizontalSlider_6->value()-50;
     double a = (ui->horizontalSlider_3->value())*0.01;
    Mat src;
    cvtColor(editmat,src,COLOR_BGR2HLS);
    float flag=averagel(src)/2;
    for(int i=0;i<editmat.rows;i++){
        for(int j=0;j<editmat.cols;j++){
            if(src.at<Vec3b>(i,j)[1]>flag){
                for(int c=0;c<3;c++){
                   editmat.at<Vec3b>(i,j)[c] = saturate_cast<uchar>(a*(editmat.at<Vec3b>(i,j)[c])-b);
                }
            }
        }
    }
    updateeditimage();
}
void editimage::darkpartslot()
{

    editmat=edittempmat.clone();
     int b = ui->horizontalSlider_7->value()-50;
     double a = (ui->horizontalSlider_3->value())*0.01;
    Mat src;
    cvtColor(editmat,src,COLOR_BGR2HLS);
     float flag=averagel(src)/2;
    for(int i=0;i<editmat.rows;i++){
        for(int j=0;j<editmat.cols;j++){
            if(src.at<Vec3b>(i,j)[1]<flag){
                for(int c=0;c<3;c++){
                   editmat.at<Vec3b>(i,j)[c] = saturate_cast<uchar>(a * (editmat.at<Vec3b>(i,j)[c])+b);
                }
            }
        }
    }
    updateeditimage();
}
void editimage::colortempslot(){
    editmat=edittempmat.clone();
   float c=ui->horizontalSlider_8->value()-50;
   for(int i=0;i<editmat.rows;i++){
       for(int j=0;j<editmat.cols;j++){
                  editmat.at<Vec3b>(i,j)[0] = saturate_cast<uchar>( (editmat.at<Vec3b>(i,j)[0])+c);
       }
   }
   updateeditimage();
}
float editimage::averagel(Mat &src){
    float sum=0;
    for(int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            sum=sum+src.at<Vec3b>(i,j)[1];
        }
    }
    return sum/(src.rows*src.cols);
}
static QImage cvMat_to_QImage(const cv::Mat &mat ) {
  switch ( mat.type() )
  {
     // 8-bit, 4 channel
     case CV_8UC4:
     {
        QImage image( mat.data, mat.cols, mat.rows, int(mat.step), QImage::Format_RGB32 );
        return image;
     }

     // 8-bit, 3 channel
     case CV_8UC3:
     {
        QImage image( mat.data, mat.cols, mat.rows, int(mat.step), QImage::Format_RGB888 );
        return image.rgbSwapped();
     }

     // 8-bit, 1 channel
     case CV_8UC1:
     {
        static QVector<QRgb>  sColorTable;
        // only create our color table once
        if ( sColorTable.isEmpty() )
        {
           for ( int i = 0; i < 256; ++i )
              sColorTable.push_back( qRgb( i, i, i ) );
        }
        QImage image( mat.data, mat.cols, mat.rows, int(mat.step), QImage::Format_Indexed8 );
        image.setColorTable( sColorTable );
        return image;
     }

     default:
        qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
        break;
  }
  return QImage();
}
void editimage::updateeditimage(){
    QImage img = cvMat_to_QImage(editmat);
    QPixmap pixmap = QPixmap::fromImage(img);
    pixmap = pixmap.scaled(ui->editimagelabel->width(),
                           ui->editimagelabel->height(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    ui->editimagelabel->setPixmap(pixmap);
}
void editimage::updateslot(){
    QImage img = cvMat_to_QImage(editmat);
    QPixmap pixmap = QPixmap::fromImage(img);
    pixmap = pixmap.scaled(ui->editimagelabel->width(),
                           ui->editimagelabel->height(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    ui->editimagelabel->setPixmap(pixmap);
}
void editimage::okbuttonslot(){
    emit sendMat(editmat);
    this->close();
}
void editimage::cancelbuttonslot(){
    this->close();
}
