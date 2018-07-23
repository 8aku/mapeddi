#ifndef SAVE_H
#define SAVE_H

#include <QPainterPath>

#include "gameobject.h"

class Save : public GameObject
{
public:
    Save();
    Save(int x, int y, WorldView *worldView);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;


private:
    QImage* image;
};

#endif // SAVE_H
