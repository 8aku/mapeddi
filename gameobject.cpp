#include "gameobject.h"
#include "mapeddi.h"
#include "worldview.h"
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#define DEFAULT_WIDTH 32
#define DEFAULT_HEIGHT 32

GameObject::GameObject()
{
    qDebug() << "Calling null";
}

 GameObject::GameObject(int x, int y, int width, int height, bool deletable, WorldView *worldView)
 {
     pos.x = x;
     pos.y = y;
     this->width = width;
     this->height = height;
     this->deletable = deletable;
     layer = MapEddi::selectedLayer;
     this->worldView = worldView;
 }

 GameObject::~GameObject()
 {
     ;
 }


 //Returns the width of a Game Object.
 int GameObject::getW() const
 {
     return width;
 }

 //Returns the height of a Game Object.
 int GameObject::getH() const
 {
     return height;
 }

 //Returns the X position of a Game Object.
 int GameObject::getX() const
 {
     return pos.x;
 }

 //Returns the Y position of a Game Object.
 int GameObject::getY() const
 {
     return pos.y;
 }

 //Sets the X position of a Game Object.
 int GameObject::setX(int position)
 {
     pos.x = position;
 }

 //Sets the Y position of a Game Object.
 int GameObject::setY(int position)
 {
     pos.y = position;
 }

 //Returns the value of Deletable for a Game Object.
 bool GameObject::isDeletable() const
 {
     return deletable;
 }

 //Draws a Game Object.
 void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
 {
     ;
 }

 //Places or deletes the selected tile.
 void GameObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
 {
     if (event->button() == Qt::RightButton && isDeletable())
     {
         delete this;
     }
 }
