#include <QPainter>
#include <QBrush>
#include "deathspot.h"

#define DEATHSPOT_WIDTH 16
#define DEATHSPOT_HEIGHT 16

DeathSpot::DeathSpot()
{
    ;
}

DeathSpot::DeathSpot(int x, int y, WorldView *worldView) : GameObject(x, y, DEATHSPOT_WIDTH, DEATHSPOT_HEIGHT, true, worldView)
{
    ;
}

void DeathSpot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor brushColour(180, 10, 180, 200);
    painter->setBrush(QBrush(brushColour));
    painter->drawRect(boundingRect());
}

QRectF DeathSpot::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}

