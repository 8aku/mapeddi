#ifndef WORLDVIEW_H
#define WORLDVIEW_H
#include <QGraphicsView>
#include "levelscene.h"
#include "mainwindow.h"
#include "worldgrid.h"
#include <forward_list>

class Player;
class Tile;
class GameObject;
class FloatingTile;
class Light;
class Monsters;
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
    void removeBouncer(Bouncer *bouncer);
    void removeDoor(Door *door);
    int getPlayerX();
    int getPlayerY();
    void setPlayerX(int newX);
    void setPlayerY(int newY);
    void clearLevel();
    void refreshView();

    friend MainWindow;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent *event);

private:
    LevelScene *levelScene;
    WorldGrid *worldGrid;
    int snapToGrid;
    std::forward_list<Tile*> tile_list;
    std::forward_list<FloatingTile*> floating_tile_list;
    std::forward_list<Light*>light_list;
    std::forward_list<Monsters*>monsters_list;
    std::forward_list<Spike*> spike_list;
    std::forward_list<Bouncer*> bouncer_list;
    std::forward_list<Door*> door_list;
    Player *player;
};

#endif // WORLDVIEW_H
