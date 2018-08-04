#include <QDebug>
#include <QBrush>
#include <QPainter>


#include "worldview.h"
#include "bouncer.h"
#include "imagecontainer.h"

#define DEFAULT_WIDTH (32)
#define DEFAULT_HEIGHT (32)

Bouncer::Bouncer()
{
    qDebug() << "Calling null constructor for bouncer";
}

Bouncer::Bouncer(int index, int x, int y, WorldView *worldView) : GameObject(x, y, DEFAULT_WIDTH, DEFAULT_HEIGHT, true, worldView)
{
    this->index = index;
}

Bouncer::~Bouncer()
{
    if (worldView)
        worldView->removeBouncer(this);
}

//Pure virtual method needed for implementation (QT specific).
QRectF Bouncer::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}

//Draws a tile. If solid, a border will appear around the tile.
void Bouncer::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    painter->drawImage(boundingRect(), *(ImageContainer::bouncerImage), QRectF(0.0, 0.0, getW(), getH()));

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(30, 60, 220, 200));
    painter->setPen(pen);

    QRectF cell (QRectF(getX(), getY(), getW(), getH()));
    painter->drawRect(cell);

    GameObject::paint(painter, option, widget);
}

int Bouncer::getIndex()
{
    return index;
}

