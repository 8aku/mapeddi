#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "imagecontainer.h"

int main(int argc, char *argv[])
{
    ImageContainer::loadImages();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
