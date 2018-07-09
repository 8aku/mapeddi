#ifndef MONSTERS_H
#define MONSTERS_H
#include "gameobject.h"


class Monsters : public GameObject
{
public:
    Monsters();
    Monsters(int x, int y, int type, bool facingRight, WorldView *worldView);
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getType();
    bool getFacingRight();
    void setDeletable(bool deletable);

private:
    int type;
    bool facingRight;

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
};

#endif // MONSTERS_H
