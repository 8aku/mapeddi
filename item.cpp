#include "item.h"
#include "imagecontainer.h"
#include <QPainter>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

Item::Item()
{

}

Item::Item( int x, int y, int type, WorldView *worldView)
    : GameObject(x, y, ImageContainer::itemImages.at(type)->width(), ImageContainer::itemImages.at(type)->height(),true, worldView)
{
    this->type = type;

}


void Item::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    painter->drawImage(boundingRect(), *(ImageContainer::itemImages.at(type)), QRectF(0.0, 0.0, getW(), getH()));

    GameObject::paint(painter, option, widget);

}


QRectF Item::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        MapEddi::selectedIndex = type;
        deletable = false;
        MapEddi::currentlyAdding = ItemObject;
    }

    GameObject::mousePressEvent(event);
}

int Item::getType()
{
    return type;
}

void Item::setDeletable(bool deletable)
{
   this->deletable = deletable;
}
