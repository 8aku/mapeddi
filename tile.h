#ifndef TILE_H
#define TILE_H
#include <QGraphicsObject>
#include <QPainterPath>
#include "utils.h"
#include "gameobject.h"
class MainWindow;
class WorldView;

class QGraphicsSceneMouseEvent;

class Tile : public GameObject
{
public:
    Tile();
    Tile(int index, int x, int y, bool isDeletable, bool isSolid, int layer, MainWindow *mainWindow, WorldView *worldView);
    Tile(int x, int y);
    virtual ~Tile();
    QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getTileIndex();
    bool isSolid();

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);

private:
    MainWindow *mainWindow;
    bool solid;
    int tileIndex;
};

#endif // TILE_H
