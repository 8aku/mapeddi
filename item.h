#ifndef ITEM_H
#define ITEM_H

#include "gameobject.h"


class Item : public GameObject
{
public:
    Item();
    Item( int x, int y, int type, WorldView *worldView );
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getType();
    void setDeletable(bool deletable);

private:
    int type;


protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);

};

#endif // ITEM_H

