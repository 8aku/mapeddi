#include <QPainter>
#include <QBrush>

#include "spike.h"

#define SPIKE_WIDTH (32)
#define SPIKE_HEIGHT (32)

Spike::Spike()
{
    ;
}

Spike::Spike(int x, int y, WorldView *worldView) : GameObject(x, y, SPIKE_WIDTH, SPIKE_HEIGHT, true, worldView)
{
    ;
}

void Spike::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor brushColour(200, 30, 90, 200);
    painter->setBrush(QBrush(brushColour));
    painter->drawRect(boundingRect());
}


QRectF Spike::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}
