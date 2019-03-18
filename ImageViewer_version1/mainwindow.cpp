#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fd(new QFileDialog(this)),
    scene(nullptr),pitem(nullptr)
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

    if(pitem){
        delete pitem;
        pitem = nullptr;
    }

    scene = new QGraphicsScene(this);
    QImage image(imgs[idx].absoluteFilePath());
    pitem = new MyPixmapItem();
    pitem->setPixmap(QPixmap::fromImage(image));
    scene->addItem(pitem);

    ui->graphicsView->setScene(scene);

    reset();
}
