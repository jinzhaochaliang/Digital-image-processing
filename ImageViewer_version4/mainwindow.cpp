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
    filtersize(new FilterSize(this))
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
