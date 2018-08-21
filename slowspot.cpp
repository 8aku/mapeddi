#include "slowspot.h"
#include <QPainter>
#include <QBrush>

SlowSpot::SlowSpot()
{
    ;
}

SlowSpot::SlowSpot(int x, int y, WorldView *worldView) : GameObject(x, y, 16, 16, true, worldView)
{
    ;
}

void SlowSpot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor brushColour(100, 200, 150, 200);
    painter->setBrush(QBrush(brushColour));
    painter->drawRect(boundingRect());

    GameObject::paint(painter, option, widget);
}

QRectF SlowSpot::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}
