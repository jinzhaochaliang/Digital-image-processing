#include "drawwindow.h"
#include "ui_drawwindow.h"
#include <QDebug>
drawWindow::drawWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::drawWindow)
{
    ui->setupUi(this);
    isDrawing = false;
    for(int i=0;i<13;i++){
        face[i]=false;
    }
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(okbuttonslot()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(cancelbuttonslot()));
    createtools();
}

drawWindow::~drawWindow()
{
    delete ui;
}
void drawWindow::createtools(){
    normalButton = new QToolButton(this);
    normalButton->setText(tr("normal"));
    connect(normalButton,SIGNAL(clicked()),this,SLOT(normalslot()));
    ui->toolBar->addWidget(normalButton);

    mosaicButton = new QToolButton(this);
    mosaicButton->setText(tr("mosaic"));
    connect(mosaicButton,SIGNAL(clicked()),this,SLOT(mosaicslot()));
    ui->toolBar->addWidget(mosaicButton);

    rectButton = new QToolButton(this);
    rectButton->setText(tr("rect"));
    connect(rectButton,SIGNAL(clicked()),this,SLOT(rectslot()));
    ui->toolBar->addWidget(rectButton);
}
void drawWindow::normalslot(){
    drawchoice = 0;
}
void drawWindow::mosaicslot(){
    drawchoice = 1;
}
void drawWindow::rectslot(){
    drawchoice = 2;
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
void drawWindow::updatedraw(){
    img = cvMat_to_QImage(drawmat);
    pixmap = QPixmap::fromImage(img);
    pixmap = pixmap.scaled(ui->drawlabel->width(),
                           ui->drawlabel->height(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    ui->drawlabel->setPixmap(pixmap);
}
void drawWindow::updateslot(){
    img = cvMat_to_QImage(drawmat);
    pixmap = QPixmap::fromImage(img);
    pixmap = pixmap.scaled(ui->drawlabel->width(),
                           ui->drawlabel->height(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    ui->drawlabel->setPixmap(pixmap);
    scale = double(img.width())/double(pixmap.size().width());
}
void drawWindow::draw(){
    Point p1,p2;
    p1.x = (lastPos.x()-150)*scale-4;
    p1.y = (lastPos.y()-50-(500-pixmap.rect().height())/2)*scale-30;
    p2.x = (endPos.x()-150)*scale-4;
    p2.y = (endPos.y()-50-(500-pixmap.rect().height())/2)*scale-30;

    switch(drawchoice){
    case 2:
        rectangle(drawmat,Point(p1.x,p1.y),Point(p2.x,p2.y),Scalar(0,0,255),2,8);
        break;
    case 1:
        Mat imageSourceCopy = drawmat.clone();
        Mat imageSource = drawmat.clone();
        int randomNum;
        RNG rng;
        int neightbourHood = 5;
        for (int i = 0; i < p2.y - p1.y; i += neightbourHood)
        {
            for (int j = 0; j < p2.x - p1.x; j += neightbourHood)
            {
                randomNum = rng.uniform(-neightbourHood / 2, neightbourHood / 2);
                Rect rect = Rect(j + neightbourHood + p1.x, i + neightbourHood + p1.y, neightbourHood, neightbourHood);
                Mat roi = imageSourceCopy(rect);
                Scalar sca = Scalar(
                    imageSource.at<Vec3b>(i + randomNum + p1.y, j + randomNum + p1.x)[0],
                    imageSource.at<Vec3b>(i + randomNum + p1.y, j + randomNum + p1.x)[1],
                    imageSource.at<Vec3b>(i + randomNum + p1.y, j + randomNum + p1.x)[2]);
                Mat roiCopy = Mat(rect.size(), CV_8UC3, sca);
                roiCopy.copyTo(roi);
            }
        }
        drawmat = imageSourceCopy.clone();
        break;
    }

    updatedraw();
}
void drawWindow::mousePressEvent(QMouseEvent *event){
    lastPos = event->pos();
    if(lastPos.x()>ui->label_1->x()&&lastPos.x()<ui->label_1->x()+94&&lastPos.y()>ui->label_1->y()&&lastPos.y()<ui->label_1->y()+94){
        face[0] = true;
    }
    if(lastPos.x()>ui->label_2->x()&&lastPos.x()<ui->label_2->x()+94&&lastPos.y()>ui->label_2->y()&&lastPos.y()<ui->label_2->y()+94){
        face[1] = true;
    }
    if(lastPos.x()>ui->label_3->x()&&lastPos.x()<ui->label_3->x()+94&&lastPos.y()>ui->label_3->y()&&lastPos.y()<ui->label_3->y()+94){
        face[2] = true;
    }
    if(lastPos.x()>ui->label_4->x()&&lastPos.x()<ui->label_4->x()+94&&lastPos.y()>ui->label_4->y()&&lastPos.y()<ui->label_4->y()+94){
        face[3] = true;
    }
    if(lastPos.x()>ui->label_5->x()&&lastPos.x()<ui->label_5->x()+94&&lastPos.y()>ui->label_5->y()&&lastPos.y()<ui->label_5->y()+94){
        face[4] = true;
    }
    if(lastPos.x()>ui->label_6->x()&&lastPos.x()<ui->label_6->x()+94&&lastPos.y()>ui->label_6->y()&&lastPos.y()<ui->label_6->y()+94){
        face[5] = true;
    }
    if(lastPos.x()>ui->label_7->x()&&lastPos.x()<ui->label_7->x()+94&&lastPos.y()>ui->label_7->y()&&lastPos.y()<ui->label_7->y()+94){
        face[6] = true;
    }
    if(lastPos.x()>ui->label_8->x()&&lastPos.x()<ui->label_8->x()+94&&lastPos.y()>ui->label_8->y()&&lastPos.y()<ui->label_8->y()+94){
        face[7] = true;
    }
    if(lastPos.x()>ui->label_9->x()&&lastPos.x()<ui->label_9->x()+94&&lastPos.y()>ui->label_9->y()&&lastPos.y()<ui->label_9->y()+94){
        face[8] = true;
    }
    if(lastPos.x()>ui->label_10->x()&&lastPos.x()<ui->label_10->x()+94&&lastPos.y()>ui->label_10->y()&&lastPos.y()<ui->label_10->y()+94){
        face[9] = true;
    }
    if(lastPos.x()>ui->label_11->x()&&lastPos.x()<ui->label_11->x()+94&&lastPos.y()>ui->label_11->y()&&lastPos.y()<ui->label_11->y()+94){
        face[10] = true;
    }
    if(lastPos.x()>ui->label_12->x()&&lastPos.x()<ui->label_12->x()+94&&lastPos.y()>ui->label_12->y()&&lastPos.y()<ui->label_12->y()+94){
        face[11] = true;
    }
    if(lastPos.x()>ui->label_13->x()&&lastPos.x()<ui->label_13->x()+94&&lastPos.y()>ui->label_13->y()&&lastPos.y()<ui->label_13->y()+94){
        face[12] = true;
    }
}
void drawWindow::mouseMoveEvent(QMouseEvent *event){
    if(face[0]==true){
        ui->label_1->move(event->pos().x(),event->pos().y());
    }
    if(face[1]==true){
        ui->label_2->move(event->pos().x(),event->pos().y());
    }
    if(face[2]==true){
        ui->label_3->move(event->pos().x(),event->pos().y());
    }
    if(face[3]==true){
        ui->label_4->move(event->pos().x(),event->pos().y());
    }
    if(face[4]==true){
        ui->label_5->move(event->pos().x(),event->pos().y());
    }
    if(face[5]==true){
        ui->label_6->move(event->pos().x(),event->pos().y());
    }
    if(face[6]==true){
        ui->label_7->move(event->pos().x(),event->pos().y());
    }
    if(face[7]==true){
        ui->label_8->move(event->pos().x(),event->pos().y());
    }
    if(face[8]==true){
        ui->label_9->move(event->pos().x(),event->pos().y());
    }
    if(face[9]==true){
        ui->label_10->move(event->pos().x(),event->pos().y());
    }
    if(face[10]==true){
        ui->label_11->move(event->pos().x(),event->pos().y());
    }
    if(face[11]==true){
        ui->label_12->move(event->pos().x(),event->pos().y());
    }
    if(face[12]==true){
        ui->label_13->move(event->pos().x(),event->pos().y());
    }
}
void drawWindow::mouseReleaseEvent(QMouseEvent *event){
    endPos = event->pos();
    draw();
    qDebug()<<endPos.x();
    qDebug()<<endPos.y();
//    qDebug()<<pixmap.size().width();
//    qDebug()<<pixmap.size().height();
//    qDebug()<<"            ";
//    qDebug()<<img.width();
//    qDebug()<<img.height();
//    qDebug()<<"            ";
//    qDebug()<<scale;
    Mat temp = drawmat.clone();
    if(face[0]==true){
//        Mat face = imread("face/face1.png");
//        Mat mask;
//        cvtColor(face,mask,COLOR_BGR2GRAY);
//        Mat ROI = temp(Rect(endPos.x()-150,endPos.y()-50-(500-pixmap.rect().height())/2,face.cols,face.rows));
//        face.copyTo(ROI,mask);
        Mat face = imread("face/face1.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_1->move(750,60);
    }
    if(face[1]==true){
        Mat face = imread("face/face2.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_2->move(900,60);
    }
    if(face[2]==true){
        Mat face = imread("face/face3.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_3->move(1050,60);
    }
    if(face[3]==true){
        Mat face = imread("face/face4.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_4->move(1200,60);
    }
    if(face[4]==true){
        Mat face = imread("face/face5.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_5->move(750,210);
    }
    if(face[5]==true){
        Mat face = imread("face/face6.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_6->move(900,210);
    }
    if(face[6]==true){
        Mat face = imread("face/face7.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_7->move(1050,210);
    }
    if(face[7]==true){
        Mat face = imread("face/face8.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_8->move(1200,210);
    }
    if(face[8]==true){
        Mat face = imread("face/face9.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_9->move(750,360);
    }
    if(face[9]==true){
        Mat face = imread("face/face10.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_10->move(900,360);
    }
    if(face[10]==true){
        Mat face = imread("face/face11.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_11->move(1050,360);
    }
    if(face[11]==true){
        Mat face = imread("face/face12.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_12->move(1200,360);
    }
    if(face[12]==true){
        Mat face = imread("face/face1.png",-1);
        cv::resize(face,face,Size(70,70));
        Mat ROI = temp(Rect((endPos.x()-150)*scale,(endPos.y()-50-(500-pixmap.rect().height())/2)*scale,face.cols,face.rows));
//        Mat ROI = temp(Rect(100,100,face.cols,face.rows));
        cvAdd4cMat_q(ROI,face,1.0);
        drawmat = temp.clone();
        updatedraw();
        ui->label_13->move(750,510);
    }
    for(int i=0;i<13;i++){
        face[i]=false;
    }
}
int drawWindow::cvAdd4cMat_q(cv::Mat &dst, cv::Mat &scr, double scale){

    if (dst.channels() != 3 || scr.channels() != 4)
    {
        return true;
    }
    if (scale < 0.01)
        return false;
    std::vector<cv::Mat>scr_channels;
    std::vector<cv::Mat>dstt_channels;
    split(scr, scr_channels);
    split(dst, dstt_channels);
    CV_Assert(scr_channels.size() == 4 && dstt_channels.size() == 3);

    if (scale < 1)
    {
        scr_channels[3] *= scale;
        scale = 1;
    }
    for (int i = 0; i < 3; i++)
    {
        dstt_channels[i] = dstt_channels[i].mul(255.0 / scale - scr_channels[3], scale / 255.0);
        dstt_channels[i] += scr_channels[i].mul(scr_channels[3], scale / 255.0);
    }
    merge(dstt_channels, dst);
    return true;
}
void drawWindow::okbuttonslot(){
    emit sendMat(drawmat);
    this->close();
}
void drawWindow::cancelbuttonslot(){
    this->close();
}
