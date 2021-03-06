#include "monsters.h"
#include "imagecontainer.h"
#include <QPainter>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

Monsters::Monsters()
{
    ;
}

Monsters::Monsters( int x, int y, int type, bool facingRight, WorldView *worldView)
    : GameObject(x, y, ImageContainer::monsterImages.at(type * 2)->width(), ImageContainer::monsterImages.at(type * 2)->height(), true, worldView)
{
    this->type = type;
    this->facingRight = facingRight;

}

int Monsters::getType()
{
    return type;
}

bool Monsters::getFacingRight()
{
    return facingRight;
}

//Draws the monster
void Monsters::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    painter->drawImage(boundingRect(), *(ImageContainer::monsterImages.at((type * 2 )+ facingRight)), QRectF(0.0, 0.0, getW(), getH()));

    GameObject::paint(painter, option, widget);
}

//Pure virtual method needed for implementation (QT specific).
QRectF Monsters::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}

void Monsters::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        MapEddi::selectedIndex = type;
        deletable = false;
        MapEddi::currentlyAdding = MonsterObject;
        MapEddi::facingRight = facingRight;
    }

    GameObject::mousePressEvent(event);
}

void Monsters::setDeletable(bool deletable)
{
   this->deletable = deletable;
}
