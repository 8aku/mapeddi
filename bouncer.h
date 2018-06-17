#ifndef BOUNCER_H
#define BOUNCER_H

#include "gameobject.h"

class MainWindow;
class WorldView;

class Bouncer : public GameObject
{
public:
    Bouncer();
    Bouncer(int index, int x, int y, WorldView *worldView);
    virtual ~Bouncer();
    QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getIndex();

private:
    int index;              //index mainly just determines what image and size the bouncer will use
};

#endif // BOUNCER_H
