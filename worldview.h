#ifndef WORLDVIEW_H
#define WORLDVIEW_H
#include <QGraphicsView>
#include "levelscene.h"
#include "mainwindow.h"
#include "worldgrid.h"
#include <forward_list>
#include "selectionrect.h"

class QWheelEvent;
class Player;
class Tile;
class GameObject;
class FloatingTile;
class Light;
class Monsters;
class Rope;
class Spike;
class Bouncer;
class Door;

class WorldView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WorldView(QWidget *parent = 0);
    void setGridSize(int gridSize);
    void addTile(int x, int y);
    void addTile(int x, int y, int index, bool isSolid, int layer);
    void addSpike(int x, int y);
    void addRope(int x, int y);
    void addMonster(int x, int y, int type, bool facingRight);
    void addFloatingTile(int x, int y, int index, int floatHeight, int maxThrust);
    void addLight(int x, int y);
    void addLight(int x, int y, int radius, int r, int g, int b, int a);
    void addBouncer(int index, int x, int y);
    void addDoor(int dest, int x, int y);
    void removeTile(Tile *tile);
    void removeFloatingTile (FloatingTile *tile);
    void removeLight (Light *light);
    void removeMonsters(Monsters *monster);
    void removeSpike(Spike *spike);
    void removeRope(Rope *rope);
    void removeBouncer(Bouncer *bouncer);
    void removeDoor(Door *door);
    int getPlayerX();
    int getPlayerY();
    void setPlayerX(int newX);
    void setPlayerY(int newY);
    void clearLevel();
    void refreshView();
    void wheel ( QWheelEvent* event );
    void scalingTime(qreal x);
    void animFinished();

    friend MainWindow;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    int _numScheduledScalings;
    LevelScene *levelScene;
    WorldGrid *worldGrid;
    int snapToGrid;
    std::forward_list<Tile*> tile_list;
    std::forward_list<FloatingTile*> floating_tile_list;
    std::forward_list<Light*>light_list;
    std::forward_list<Monsters*>monsters_list;
    std::forward_list<Spike*> spike_list;
    std::forward_list<Rope*> rope_list;
    std::forward_list<Bouncer*> bouncer_list;
    std::forward_list<Door*> door_list;
    Player *player;
    SelectionRect *selectionRect;
};

#endif // WORLDVIEW_H
