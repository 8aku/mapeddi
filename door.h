#ifndef DOOR_H
#define DOOR_H

#include "gameobject.h"

class MainWindow;
class WorldView;
class QWidget;

class Door : public GameObject
{
    Q_OBJECT
public:
    Door();
    Door(int destX, int destY, int dest, int x, int y, WorldView *worldView);
    virtual ~Door();
    QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getDest();
    int getDestX();
    int getDestY();
    bool getLocked();
    void setLocked(bool locked);

    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);

public slots:
    void setDest(int dest);
    void setDestX(int destX);
    void setDestY(int destY);
    void toggleLocked();


private:
    bool locked;
    int destX;
    int destY;
    int dest;              //destination level
    QWidget *doorParameters;
};
#endif // DOOR_H
