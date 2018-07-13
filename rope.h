#ifndef ROPE_H
#define ROPE_H


#include "gameobject.h"

class Rope : public GameObject
{
public:
    Rope();
    Rope(int x, int y, WorldView *worldView);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};


#endif // ROPE_H
