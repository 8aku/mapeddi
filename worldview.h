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

class WorldView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WorldView(QWidget *parent = 0);
    void setGridSize(int gridSize);
    void addTile(int x, int y);
    void addTile(int x, int y, int index, bool isSolid);
    void addFloatingTile(int x, int y, int index, int floatHeight, int maxThrust);
    void removeTile(Tile *tile);
    void removeFloatingTile (FloatingTile *tile);
    int getPlayerX();
    int getPlayerY();
    void setPlayerX(int newX);
    void setPlayerY(int newY);
    friend MainWindow;
    void clearLevel();
    void refreshView();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    LevelScene *levelScene;
    WorldGrid *worldGrid;
    int snapToGrid;
    std::forward_list<Tile*> tile_list;
    std::forward_list<FloatingTile*> floating_tile_list;
    Player *player;
};

#endif // WORLDVIEW_H
