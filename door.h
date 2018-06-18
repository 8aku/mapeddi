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
    Door(int dest, int x, int y, WorldView *worldView);
    virtual ~Door();
    QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getDest();

private slots:
    void setDest(int dest);

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);

private:
    int dest;              //destination level
    QWidget *doorParameters;
};
#endif // DOOR_H
