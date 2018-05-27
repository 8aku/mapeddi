#ifndef SPIKE_H
#define SPIKE_H

#include "gameobject.h"

class Spike : public GameObject
{
public:
    Spike();
    Spike(int x, int y, WorldView *worldView);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // SPIKE_H
