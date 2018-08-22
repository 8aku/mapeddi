#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QToolTip>
#include "worldview.h"
#include "door.h"
#include "doorwindow.h"
#include "imagecontainer.h"

#define DEFAULT_WIDTH (16)
#define DEFAULT_HEIGHT (32)

Door::Door()
{
    qDebug() << "Calling null constructor for Door";
}

Door::Door(int destX, int destY, int dest, int x, int y, WorldView *worldView) : GameObject(x, y, DEFAULT_WIDTH, DEFAULT_HEIGHT, true, worldView)
{
    this->destX = destX;
    this->destY = destY;
    this->dest = dest;
    locked = false;
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

    QColor brushColour(50, 130, 400, 200);

    QRectF cell (QRectF(getX(), getY(), getW(), getH()));
    painter->drawRect(cell);

    if (locked)
        painter->fillRect(cell, QBrush(brushColour));

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

bool Door::getLocked()
{
    return locked;
}

void Door::setLocked(bool locked)
{
    this->locked = locked;
}

void Door::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    //if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ShiftModifier)
    {
        qDebug() << "this: " << this << "\n";
        doorParameters = new DoorWindow(this, worldView);
    }

   // if (event->button() == Qt::LeftButton)
    //    qDebug() << "left click: " << this << "\n";

    GameObject::mousePressEvent(event);
}

void Door::toggleLocked()
{
    locked = !locked;
}

void Door::setDest(int dest)
{
    this->dest = dest;

    QPoint point(0, 0);
    //QToolTip::showText(doorParameters->mapToGlobal(point), QString::number(dest), doorParameters);
}

void Door::setDestX(int destX)
{
    this->destX = destX;

    QPoint point(0, 0);
    //QToolTip::showText(doorParameters->mapToGlobal(point), QString::number(destX), doorParameters);
}

void Door::setDestY(int destY)
{
    this->destY = destY;

    QPoint point(0, 0);
    //QToolTip::showText(doorParameters->mapToGlobal(point), QString::number(destY), doorParameters);
}
