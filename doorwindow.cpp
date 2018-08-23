#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QToolTip>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QIntValidator>
#include "doorwindow.h"
#include "door.h"

DoorWindow::DoorWindow(QWidget *parent) : QWidget(parent)
{
    ;
}

DoorWindow::~DoorWindow()
{
    qDebug() << "Window deleted\n";
    delete validator;
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

    validator = new QIntValidator();
    //destination level --------------------------------------------------------
   QLineEdit *levelBox = new QLineEdit(this);
   levelBox->setPlaceholderText(QString::number(door->getDest()));
    levelBox->move(32, 32);
    QLabel *levelLabel = new QLabel(tr("Destination Level"), this);
    levelLabel->move(32, 16);
    levelBox->setValidator(validator);
    connect(levelBox, SIGNAL(textChanged(const QString &)), this, SLOT(setDest(const QString &)));

   //destination x coord --------------------------------------------------------

   QLineEdit *xBox = new QLineEdit(this);
    xBox->move(32, 72);
    QLabel *xLabel = new QLabel(tr("Destination X"), this);
    xBox->setPlaceholderText(QString::number(door->getDestX()));
    xLabel->move(32, 56);
    xBox->setValidator(validator);
   connect(xBox, SIGNAL(textChanged(const QString &)), this, SLOT(setDestX(const QString &)));

    //destination y coord --------------------------------------------------------------
   QLineEdit *yBox = new QLineEdit(this);
   yBox->move(32, 112);
   yBox->setPlaceholderText(QString::number(door->getDestY()));
   QLabel *yLabel = new QLabel(tr("Destination Y"), this);
   yLabel->move(32, 96);
    yBox->setValidator(validator);
   connect(yBox, SIGNAL(textChanged(const QString &)), this, SLOT(setDestY(const QString &)));

    //locked? --------------------------------------------------------------------------
   QCheckBox *isLocked = new QCheckBox(this);
   isLocked->move(32, 152);
   isLocked->setChecked(door->getLocked());
   QLabel *lockedLabel = new QLabel(tr("Locked Door"), this);
   lockedLabel->move(64,152);

   connect(isLocked, SIGNAL(stateChanged(int)), this, SLOT(toggleLocked()));

    show();
}

void DoorWindow::toggleLocked()
{
    door->toggleLocked();
}


void DoorWindow::setDest(const QString &dest)
{
     door->setDest(dest.toInt());

    QPoint point(0, 0);
    QToolTip::showText(this->mapToGlobal(point), dest, this);
}

void DoorWindow::setDestX(const QString &destX)
{
     door->setDestX(destX.toInt());

    QPoint point(0, 0);
    QToolTip::showText(this->mapToGlobal(point), destX, this);
}

void DoorWindow::setDestY(const QString &destY)
{
     door->setDestY(destY.toInt());

    QPoint point(0, 0);
    QToolTip::showText(this->mapToGlobal(point), destY, this);
}
