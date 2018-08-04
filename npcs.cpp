#include "npcs.h"

#include "imagecontainer.h"
#include <QPainter>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

Npcs::Npcs()
{
    ;
}

Npcs::Npcs( int x, int y, int type, WorldView *worldView)
    : GameObject(x, y, ImageContainer::npcImages.at(type)->width(), ImageContainer::npcImages.at(type)->height(),true, worldView)
{
    this->type = type;

}


void Npcs::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    painter->drawImage(boundingRect(), *(ImageContainer::npcImages.at(type)), QRectF(0.0, 0.0, getW(), getH()));

    GameObject::paint(painter, option, widget);

}


QRectF Npcs::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}

void Npcs::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        MapEddi::selectedIndex = type;
        deletable = false;
        MapEddi::currentlyAdding = NpcObject;
    }

    GameObject::mousePressEvent(event);
}

int Npcs::getType()
{
    return type;
}

void Npcs::setDeletable(bool deletable)
{
   this->deletable = deletable;
}
