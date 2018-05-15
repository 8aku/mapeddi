#ifndef FLOATINGTILE_H
#define FLOATINGTILE_H
#include "gameobject.h"

class WorldView;

class FloatingTile : public GameObject
{
public:
    FloatingTile();
    FloatingTile(int x, int y, int floatHeight, int index, int maxThrust, WorldView* worldview);
    virtual ~FloatingTile();
    QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getFloatHeight();
    int getIndex();
    int getMaxThrust();

private:
    int floatHeight;
    int index;
    int maxThrust;
};

#endif // FLOATINGTILE_H
