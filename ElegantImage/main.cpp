#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString qss;
    QFile qssFile(":/qss/css.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen()){
     qss = QLatin1String(qssFile.readAll());
     qApp->setStyleSheet(qss);
     qssFile.close();
    }
    MainWindow w;
    w.setWindowTitle("ElegantImage");
    w.show();

    return a.exec();
}
