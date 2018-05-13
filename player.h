#ifndef PLAYER_H
#define PLAYER_H
#include "gameobject.h"
#include <QGraphicsObject>
#include <QPainterPath>
#include "utils.h"
class QImage;


class Player : public GameObject
{
public:
    Player();
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QImage* image;
};

#endif // PLAYER_H
