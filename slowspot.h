#ifndef SLOWSPOT_H
#define SLOWSPOT_H
#include "gameobject.h"

class SlowSpot : public GameObject
{
public:
    SlowSpot();
    SlowSpot( int x, int y, WorldView *worldView );

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

};

#endif // SLOWSPOT_H
