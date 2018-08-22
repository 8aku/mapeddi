#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "utils.h"
#include <QGraphicsObject>
class WorldView;

class QGraphicsSceneMouseEvent;

class GameObject : public QGraphicsObject
{
public:
    GameObject();
    GameObject(int x, int y, int width, int height, bool deletable, WorldView *worldView);
    virtual ~GameObject();
    bool isDeletable() const;
    bool isSelected() const;
    void toggleSelected();
    void select();
    void deselect();
    int getW() const;
    int getH() const;
    void setX(int position);
    void setY(int position);
    void setLayer(int layer);
    int getX() const;
    int getY() const;
    int getLayer();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);

protected:
    WorldView *worldView;
     bool deletable;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool selected;
    int layer;
    int width;
    int height;
    Point pos;
};

#endif // GAMEOBJECT_H
