#ifndef PLATFORM_H
#define PLATFORM_H
#include "gameobject.h"

class WorldView;

class Platform : public GameObject
{
public:
    Platform();
    Platform( int x, int y, WorldView *worldView );
    QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // PLATFORM_H
