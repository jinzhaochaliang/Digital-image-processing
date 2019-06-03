#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "imageprocessor.h"

using std::vector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fd(new QFileDialog(this)),
    scene(nullptr),pitem(nullptr),
    dialog(new DialogT(this)),
    contrast(new ContrastC(this)),
    digLinear(new DigLinear(this)),
    gauss(new Gauss(this)),
    bilateral(new Bilateral(this)),
    filtersize(new FilterSize(this)),
    transform(new Transform(this))
{
    fd->setNameFilter("Images (*.png *.bmp *.jpg *.gif)");
    fd->setFileMode(QFileDialog::ExistingFile);
    ui->setupUi(this);

    ui->resetButton->setEnabled(false);
    ui->lastButton->setEnabled(false);
    ui->nextButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete transform;
    delete filtersize;
    delete bilateral;
    delete gauss;
    delete digLinear;
    delete contrast;
    delete dialog;
    delete pitem;
    delete scene;
    delete fd;
    delete ui;
}

void MainWindow::on_openButton_clicked(){
//    qDebug()<<"clicked";
    if(fd->exec()){

        QStringList files = fd->selectedFiles();
        qDebug()<<files[0];

        QDir dir = fd->directory();
        QStringList filters;
        filters<<"*.png"<<"*.bmp"<<"*.jpg"<<"*.gif";
        imgs = dir.entryInfoList(filters);
        for(int i=0;i<imgs.size();i++){
            if(imgs[i].absoluteFilePath()==files[0]){
                idx = i;
                break;
            }
        }

        if(imgs.size()>0){
            ui->resetButton->setEnabled(true);
            ui->lastButton->setEnabled(true);
            ui->nextButton->setEnabled(true);
        }

        showImage();
    }
}

void MainWindow::on_resetButton_clicked(){
//    qDebug()<<"clicked";
    reset();
}

void MainWindow::reset(){
    QRectF rect = pitem->boundingRect();
    pitem->reset();
    scene->setSceneRect(rect);
    ui->graphicsView->fitInView(pitem,Qt::KeepAspectRatio);
    ui->graphicsView->centerOn(pitem);
}

void MainWindow::on_nextButton_clicked(){
//    qDebug()<<"clicked";
    if(idx==imgs.size()-1) idx=-1;
    idx++;
    showImage();
}

void MainWindow::on_lastButton_clicked(){
//    qDebug()<<"clicked";
    if(idx==0) idx=imgs.size();
    idx--;
    showImage();
}

void MainWindow::showImage(){
    QImage image(imgs[idx].absoluteFilePath());
    showImage(image);
}

void MainWindow::showImage(QImage img){

    if(pitem){
        delete pitem;
        pitem = nullptr;
    }

    if(scene){
        delete scene;
        scene = nullptr;
    }
    scene = new QGraphicsScene(this);
    pitem = new MyPixmapItem();
    pitem->setPixmap(QPixmap::fromImage(img));
    scene->addItem(pitem);
    ui->graphicsView->setScene(scene);
    reset();
}

void MainWindow::on_actionrgb2gray_triggered(){
//    qDebug()<<"clicked";
    if(!pitem) return;
    QImage image = getCurrentImage();

    // rgb2gray
    image = ImageProcessor::rgb2Gray(image);
    showImage(image);
}

void MainWindow::on_actionreverse_triggered(){
    //    qDebug()<<"clicked";
    if(!pitem) return;
    QImage image = getCurrentImage();

    // rgb2gray
    image = ImageProcessor::reverse(image);
    showImage(image);
}

void MainWindow::on_actionhisbalance_triggered(){
    //    qDebug()<<"clicked";
    if(!pitem) return;
    QImage image = getCurrentImage();

    // rgb2gray
    image = ImageProcessor::hisbalance(image);
    showImage(image);
}

void MainWindow::on_actionhisrgbbalance_triggered(){
    //    qDebug()<<"clicked";
    if(!pitem) return;
    QImage image = getCurrentImage();

    // rgb2gray
    image = ImageProcessor::hisrgbbalance(image);
    showImage(image);
}

void MainWindow::on_actionlog_triggered(){
//    qDebug()<<"clicked";
    dialog->exec();
}

void MainWindow::on_actioncontrast_triggered(){
    contrast->exec();
}

void MainWindow::on_DialogT_confirmed(double c){
//    qDebug()<<c;

    if(!pitem) return;
    QImage image = getCurrentImage();

    // rgb2gray
    image = ImageProcessor::logTransform(image,c);
    showImage(image);
}

void MainWindow::on_ContrastC_getparaContrast(double m ,double e){
//    qDebug()<<m<<endl<<e;

    if(!pitem) return;
    QImage image = getCurrentImage();

    // contrast
    image = ImageProcessor::ContrastTransform(image,m,e);
    showImage(image);
}

QImage MainWindow::getCurrentImage() const{

    QList<QGraphicsItem*> items = ui->graphicsView->scene()->items();
    QGraphicsPixmapItem* item = (QGraphicsPixmapItem*)items.at(0);

    QImage image = item->pixmap().toImage();
    return image;
}

void MainWindow::on_actionLinear_triggered(){
    digLinear->exec();
}

void MainWindow::on_DigLinear_confirmed(vector<double> data,int nCol,int num1,int num2){
    qDebug()<<nCol;
    QImage img = getCurrentImage();
    normalizeKernal(data);
    img = ImageProcessor::linearFilter(img,data,nCol,num1,num2);
    showImage(img);
}

void MainWindow::normalizeKernal(vector<double>& data){
    double sum = 0;
    for(int i=0;i<data.size();i++){
        sum+=data[i];
    }
    if(sum==0||sum==1) return;
    else{
        for(int i=0;i<data.size();i++){
            data[i] = data[i]/sum;
        }
    }
}


void MainWindow::on_actionGauss_triggered(){
    gauss->exec();
}
void MainWindow::on_Gauss_confirmed(int l,double s){
    qDebug()<<l<<s;

    if(!pitem) return;
    QImage image = getCurrentImage();
    image = ImageProcessor::GaussTransform(image,l,s);
    showImage(image);
}
void MainWindow::on_actionBilateral_triggered(){
    bilateral->exec();
}
void MainWindow::on_Bilateral_confirmed(int l,double s,double s1){
    qDebug()<<l<<s<<s1;

    if(!pitem) return;
    QImage image = getCurrentImage();
    image = ImageProcessor::BilateralTransform(image,l,s,s1);
    showImage(image);
}

void MainWindow::on_actionMedian_triggered(){
    filtertype = "median";
    filtersize->exec();
}
void MainWindow::on_actionEroding_triggered(){
    filtertype = "eroding";
    filtersize->exec();
}
void MainWindow::on_actionDilating_triggered(){
    filtertype = "dilating";
    filtersize->exec();
}
void MainWindow::on_FilterSize_confirmed(int l){
//    qDebug()<<l;
    if(!pitem) return;
    QImage image = getCurrentImage();
//    image = ImageProcessor::BilateralTransform(image,l,s,s1);
    if(filtertype=="median"){
        qDebug()<<"1";
        image = ImageProcessor::MedianTransform(image,l);
    }else if(filtertype=="eroding"){
        qDebug()<<"2";
        image = ImageProcessor::ErodingTransform(image,l);
    }else if(filtertype=="dilating"){
        qDebug()<<"3";
        image = ImageProcessor::DilatingTransform(image,l);
    }
    showImage(image);
}


void MainWindow::on_actionfrequency_triggered(){
//    qDebug()<<"1";
    if(!pitem) return;
    QImage image = getCurrentImage();
    Matrix<int> mat1(1,1,0);
    mat1 = mat1.fromQImage(image,'y');
    Matrix<std::complex<double>> mat2 = fft2d(mat1,mat1.getNRow(),mat1.getNCol());
    Matrix<double> mat3(mat2.getNRow(),mat2.getNCol(),0);
    double maxmat = 0,minmat = 255;
    for(size_t i=0;i<mat2.getNRow();i++){
        for(size_t j=0;j<mat2.getNCol();j++){
            mat3(i,j) = abs(mat2(i,j));
            mat3(i,j) = log(1+mat3(i,j));
            if(maxmat<mat3(i,j)) maxmat = mat3(i,j);
            if(minmat>mat3(i,j)) minmat = mat3(i,j);
        }
    }
    mat3.fftshift();
    Matrix<int> mat4(mat3.getNRow(),mat3.getNCol(),0);
    for(size_t i=0;i<mat3.getNRow();i++){
        for(size_t j=0;j<mat3.getNCol();j++){
            mat4(i,j) = round((mat3(i,j)-minmat)/(maxmat-minmat)*255);
        }
    }
    image = mat4.toQImage(mat4);
    showImage(image);
}

void MainWindow::on_actionaffinetransform_triggered(){
    transform->exec();
}

void MainWindow::on_Transform_confirmed(Matrix<double> temp){
    cout<<temp;
//    cout<<temp.inverted(temp);
//    cout<<temp*temp.inverted(temp);

    Matrix<double> tempt = temp.inverted3(temp);
    cout<<tempt;
    cout<<temp*tempt;

    if(!pitem) return;
    QImage image = getCurrentImage();
    int h = image.height();
    int w = image.width();
    Matrix<double> mat1(1,3,0);
    mat1(0,0)=0;mat1(0,1)=0;
    Matrix<double> mat2(1,3,0);
    mat2(0,0)=w;mat2(0,1)=0;
    Matrix<double> mat3(1,3,0);
    mat3(0,0)=0;mat3(0,1)=h;
    Matrix<double> mat4(1,3,0);
    mat4(0,0)=w;mat4(0,1)=h;
    mat1 = mat1*temp;
    mat2 = mat2*temp;
    mat3 = mat3*temp;
    mat4 = mat4*temp;
    double minh = h,maxh = -h,minw = w,maxw = -w;
    if(mat1(0,0)<minw) minw = mat1(0,0);if(mat2(0,0)<minw) minw = mat2(0,0);
    if(mat3(0,0)<minw) minw = mat3(0,0);if(mat4(0,0)<minw) minw = mat4(0,0);
    if(mat1(0,0)>maxw) maxw = mat1(0,0);if(mat2(0,0)>maxw) maxw = mat2(0,0);
    if(mat3(0,0)>maxw) maxw = mat3(0,0);if(mat4(0,0)>maxw) maxw = mat4(0,0);
    if(mat1(0,1)<minh) minh = mat1(0,1);if(mat2(0,1)<minh) minh = mat2(0,1);
    if(mat3(0,1)<minh) minh = mat3(0,1);if(mat4(0,1)<minh) minh = mat4(0,1);
    if(mat1(0,1)>maxh) maxh = mat1(0,1);if(mat2(0,1)>maxh) maxh = mat2(0,1);
    if(mat3(0,1)>maxh) maxh = mat3(0,1);if(mat4(0,1)>maxh) maxh = mat4(0,1);
    int neww = maxw-minw;
    int newh = maxh-minh;
    Matrix<double> mat(1,3,0);
    QImage img(neww,newh,QImage::Format_RGB888);
    for(int i=0;i<neww;i++){
        for(int j=0;j<newh;j++){
            mat(0,0) = i+minw;
            mat(0,1) = j+minh;
            mat(0,2) = 0;
            mat = mat*tempt;
            if(mat(0,0)<0||mat(0,0)>w||mat(0,1)<0||mat(0,1)>h){
                img.setPixel(i,j,qRgb(0,0,0));
                continue;
            }
//            img.setPixel(i,j,image.pixel(floor(mat(0,0)),floor(mat(0,1))));
            Matrix<double> m1(2,2,0);
            double x = mat(0,0);
            double y = mat(0,1);
            double x1 = floor(mat(0,0));
            double x2 = ceil(mat(0,0));
            double y1 = floor(mat(0,1));
            double y2 = ceil(mat(0,1));
            QRgb q11 = image.pixel(x1,y1);
            QRgb q12 = image.pixel(x1,y2);
            QRgb q21 = image.pixel(x2,y1);
            QRgb q22 = image.pixel(x2,y2);
            m1(0,0) = qRed(q11);m1(0,1) = qRed(q12);
            m1(1,0) = qRed(q21);m1(1,1) = qRed(q22);
            double g1 =(y2-y)/(y2-y1)*((x2-x)/(x2-x1)*m1(0,0)+(x-x1)/(x2-x1)*m1(0,1))+(y-y1)/(y2-y1)*((x2-x)/(x2-x1)*m1(1,0)+(x-x1)/(x2-x1)*m1(1,1));
            m1(0,0) = qGreen(q11);m1(0,1) = qGreen(q12);
            m1(1,0) = qGreen(q21);m1(1,1) = qGreen(q22);
            double g2 =(y2-y)/(y2-y1)*((x2-x)/(x2-x1)*m1(0,0)+(x-x1)/(x2-x1)*m1(0,1))+(y-y1)/(y2-y1)*((x2-x)/(x2-x1)*m1(1,0)+(x-x1)/(x2-x1)*m1(1,1));
            m1(0,0) = qBlue(q11);m1(0,1) = qBlue(q12);
            m1(1,0) = qBlue(q21);m1(1,1) = qBlue(q22);
            double g3 =(y2-y)/(y2-y1)*((x2-x)/(x2-x1)*m1(0,0)+(x-x1)/(x2-x1)*m1(0,1))+(y-y1)/(y2-y1)*((x2-x)/(x2-x1)*m1(1,0)+(x-x1)/(x2-x1)*m1(1,1));

            img.setPixel(i,j,qRgb(g1,g2,g3));
        }
    }
    showImage(img);
}
