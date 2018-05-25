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

class WorldView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WorldView(QWidget *parent = 0);
    void setGridSize(int gridSize);
    void addTile(int x, int y);
    void addTile(int x, int y, int index, bool isSolid, int layer);
    void addMonster(int x, int y, int type, bool facingRight);
    void addFloatingTile(int x, int y, int index, int floatHeight, int maxThrust);
    void addLight(int x, int y);
    void addLight(int x, int y, int radius, int r, int g, int b, int a);
    void removeTile(Tile *tile);
    void removeFloatingTile (FloatingTile *tile);
    void removeLight (Light *light);
    void removeMonsters(Monsters *monster);
    int getPlayerX();
    int getPlayerY();
    void setPlayerX(int newX);
    void setPlayerY(int newY);
    friend MainWindow;
    void clearLevel();
    void refreshView();

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
    Player *player;
};

#endif // WORLDVIEW_H
