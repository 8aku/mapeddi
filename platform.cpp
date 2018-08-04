#include <QDebug>
#include <QBrush>
#include <QPainter>


#include "worldview.h"
#include "platform.h"
#include "imagecontainer.h"

#define DEFAULT_WIDTH (32)
#define DEFAULT_HEIGHT (8)
#define DEFAULT_DX (64)
Platform::Platform()
{
    qDebug() << "Calling null constructor for Platform";
}

Platform::Platform(int x, int y, WorldView *worldView) : Platform(x, y, DEFAULT_DX, worldView) { ; }

Platform::Platform(int x, int y, int dx, WorldView *worldView) : GameObject(x, y, DEFAULT_WIDTH, DEFAULT_HEIGHT, true, worldView)
{
    this->dx = dx;
}

Platform::~Platform()
{
    if (worldView)
        worldView->removePlatform(this);
}

//Pure virtual method needed for implementation (QT specific).
QRectF Platform::boundingRect() const
{
    return QRectF(getX(), getY(), getW() + getDx(), getH());
}

//Draws a tile. If solid, a border will appear around the tile.
void Platform::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    QRectF imageRect (getX(), getY(), getW(), getH());
    painter->drawImage(imageRect, *(ImageContainer::platformImage), QRectF(0.0, 0.0, getW(), getH()));

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(230, 180, 130, 200));
    painter->setPen(pen);

    QRectF cell (QRectF(getX(), getY(), getW() + getDx(), getH()));
    painter->drawRect(cell);

    GameObject::paint(painter, option, widget);
}

int Platform::getDx() const
{
    return dx;
}

