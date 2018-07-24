#ifndef DEATHSPOT_H
#define DEATHSPOT_H

#include "gameobject.h"

class DeathSpot : public GameObject
{
public:
    DeathSpot();
    DeathSpot( int x, int y, WorldView *worldView );

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

};

#endif // DEATHSPOT_H
