#include <QPainter>
#include <QBrush>

#include "rope.h"

#define ROPE_WIDTH (16)
#define ROPE_HEIGHT (16)

Rope::Rope()
{
    ;
}

Rope::Rope(int x, int y, WorldView *worldView) : GameObject(x, y, ROPE_WIDTH, ROPE_HEIGHT, true, worldView)
{
    ;
}

void Rope::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor brushColour(50, 130, 200, 200);
    painter->setBrush(QBrush(brushColour));
    painter->drawRect(boundingRect());

    GameObject::paint(painter, option, widget);
}


QRectF Rope::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}
