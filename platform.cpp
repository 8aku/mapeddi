#include <QPainter>
#include <QBrush>

#include "platform.h"
#include "imagecontainer.h"

Platform::Platform()
{
    ;
}

Platform::Platform(int x, int y, WorldView *worldView) : GameObject(x, y, 32, 32, true, worldView)
{
    ;
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    painter->drawImage(boundingRect(), *(ImageContainer::platformImage), QRectF(0.0, 0.0, getW(), getH()));
}

QRectF Platform::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}
