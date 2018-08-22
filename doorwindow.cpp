#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QToolTip>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>

#include "doorwindow.h"
#include "door.h"

DoorWindow::DoorWindow(QWidget *parent) : QWidget(parent)
{
    ;
}

DoorWindow::~DoorWindow()
{
    qDebug() << "Window deleted\n";
    disconnect();
}

DoorWindow::DoorWindow(Door *door, QWidget *parent) : DoorWindow(parent) {
    setAttribute(Qt::WA_DeleteOnClose);

    this->door = door;

    setWindowFlags(Qt::Dialog);
    resize(256, 250);
    setMaximumSize(256, 250);
    setMinimumSize(256, 250);
    setWindowTitle("door parameters");

   QSlider *destSlider = new QSlider(Qt::Horizontal, this);
   destSlider->resize(250, 32);
   destSlider->setMinimum(0);
   destSlider->setMaximum(64);
   destSlider->move(0, 15);
   destSlider->setValue(door->getDest());
   QLabel *destLabel = new QLabel(tr("dest"), this);


   connect(destSlider, SIGNAL(valueChanged(int)), this, SLOT(setDest(int)));


   QSlider *destXSlider = new QSlider(Qt::Horizontal, this);
   destXSlider->resize(250, 32);
   destXSlider->setMinimum(0);
   destXSlider->setMaximum(20000);
   destXSlider->move(0, 45);
    destXSlider->setValue(door->getDestX());
   QLabel *destXLabel = new QLabel(tr("destX"), this);
    destXLabel->move(0,40);

   connect(destXSlider, SIGNAL(valueChanged(int)), this, SLOT(setDestX(int)));



   QSlider *destYSlider = new QSlider(Qt::Horizontal, this);
   destYSlider->resize(250, 32);
   destYSlider->setMinimum(0);
   destYSlider->setMaximum(20000);
   destYSlider->move(0, 75);
    destYSlider->setValue(door->getDestY());
   QLabel *destYLabel = new QLabel(tr("destY"), this);
   destYLabel->move(0,70);

   connect(destYSlider, SIGNAL(valueChanged(int)), this, SLOT(setDestY(int)));


   QCheckBox *isLocked = new QCheckBox(this);
   isLocked->move(0, 100);
   isLocked->setChecked(door->getLocked());

   connect(isLocked, SIGNAL(stateChanged(int)), this, SLOT(toggleLocked()));

    show();
}

void DoorWindow::toggleLocked()
{
    door->toggleLocked();
}


void DoorWindow::setDest(int dest)
{
     door->setDest(dest);

    QPoint point(0, 0);
    QToolTip::showText(this->mapToGlobal(point), QString::number(dest), this);
}

void DoorWindow::setDestX(int destX)
{
     door->setDestX(destX);

    QPoint point(0, 0);
    QToolTip::showText(this->mapToGlobal(point), QString::number(destX), this);
}

void DoorWindow::setDestY(int destY)
{
     door->setDestY(destY);

    QPoint point(0, 0);
    QToolTip::showText(this->mapToGlobal(point), QString::number(destY), this);
}
