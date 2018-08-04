#ifndef PLATFORM_H
#define PLATFORM_H

#include "gameobject.h"

class Platform : public GameObject
{
public:
    Platform();
    Platform(int x, int y, WorldView *worldView);
    Platform(int x, int y, int dx, WorldView *worldView);
    virtual ~Platform();
    QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getDx() const;

private:
    int dx;              //index mainly just determines what image and size the bouncer will use
};

#endif // PLATFORM_H
