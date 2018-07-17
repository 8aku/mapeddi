#ifndef NPCS_H
#define NPCS_H

#include "gameobject.h"


class Npcs : public GameObject
{
public:
    Npcs();
    Npcs( int x, int y, int type, WorldView *worldView );
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getType();
    void setDeletable(bool deletable);

private:
    int type;


protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
};

#endif // NPCS_H
