#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QToolTip>
#include "worldview.h"
#include "door.h"
#include "imagecontainer.h"

#define DEFAULT_WIDTH (32)
#define DEFAULT_HEIGHT (64)

Door::Door()
{
    qDebug() << "Calling null constructor for Door";
}

Door::Door(int destX, int destY, int dest, int x, int y, WorldView *worldView) : GameObject(x, y, DEFAULT_WIDTH, DEFAULT_HEIGHT, true, worldView)
{
    this->destX = destX;
    this->destY = destY;
    this->dest = dest;
}

Door::~Door()
{
    if (worldView)
        worldView->removeDoor(this);
}

//Pure virtual method needed for implementation (QT specific).
QRectF Door::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}

//Draws a tile. If solid, a border will appear around the tile.
void Door::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(140, 60, 220, 250));
    painter->setPen(pen);

    QRectF cell (QRectF(getX(), getY(), getW(), getH()));
    painter->drawRect(cell);

    GameObject::paint(painter, option, widget);
}

int Door::getDest()
{
    return dest;
}

int Door::getDestX()
{
    return destX;
}

int Door::getDestY()
{
    return destY;
}

void Door::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ShiftModifier)
    {
        doorParameters = new QWidget(worldView);
        doorParameters->setWindowFlags(Qt::Dialog);
        doorParameters->resize(256, 250);
        doorParameters->setMaximumSize(256, 250);
        doorParameters->setMinimumSize(256, 250);
        doorParameters->setWindowTitle("door parameters");

       QSlider *destSlider = new QSlider(Qt::Horizontal, doorParameters);
       destSlider->resize(250, 32);
       destSlider->setMinimum(0);
       destSlider->setMaximum(64);
       destSlider->move(0, 15);

       QLabel *destLabel = new QLabel(tr("dest"), doorParameters);


       connect(destSlider, SIGNAL(valueChanged(int)), this, SLOT(setDest(int)));


       QSlider *destXSlider = new QSlider(Qt::Horizontal, doorParameters);
       destXSlider->resize(250, 32);
       destXSlider->setMinimum(0);
       destXSlider->setMaximum(20000);
       destXSlider->move(0, 45);

       QLabel *destXLabel = new QLabel(tr("destX"), doorParameters);
        destXLabel->move(0,40);

       connect(destXSlider, SIGNAL(valueChanged(int)), this, SLOT(setDestX(int)));



       QSlider *destYSlider = new QSlider(Qt::Horizontal, doorParameters);
       destYSlider->resize(250, 32);
       destYSlider->setMinimum(0);
       destYSlider->setMaximum(20000);
       destYSlider->move(0, 75);

       QLabel *destYLabel = new QLabel(tr("destY"), doorParameters);
       destYLabel->move(0,70);


       connect(destYSlider, SIGNAL(valueChanged(int)), this, SLOT(setDestY(int)));



        doorParameters->show();
    }

    GameObject::mousePressEvent(event);
}

void Door::setDest(int dest)
{
    this->dest = dest;

    QPoint point(0, 0);
    QToolTip::showText(doorParameters->mapToGlobal(point), QString::number(dest), doorParameters);
}

void Door::setDestX(int destX)
{
    this->destX = destX;

    QPoint point(0, 0);
    QToolTip::showText(doorParameters->mapToGlobal(point), QString::number(destX), doorParameters);
}

void Door::setDestY(int destY)
{
    this->destY = destY;

    QPoint point(0, 0);
    QToolTip::showText(doorParameters->mapToGlobal(point), QString::number(destY), doorParameters);
}
