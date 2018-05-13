#include "worldview.h"
#include "levelscene.h"
#include "worldgrid.h"
#include "mapeddi.h"
#include "tile.h"
#include "floatingtile.h"
#include "player.h"
#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>

WorldView::WorldView(QWidget *parent)
    : QGraphicsView(parent)
{
     setMouseTracking(true);
     levelScene = new LevelScene(this);
     setFrameStyle(Sunken | StyledPanel);

     levelScene->setBackgroundBrush(Qt::black);
     levelScene->setItemIndexMethod(QGraphicsScene::NoIndex);
     levelScene->setSceneRect(0, 0, MapEddi::levelWidth, MapEddi::levelHeight);

     setScene(levelScene);

     worldGrid = new WorldGrid(MapEddi::levelWidth, MapEddi::levelHeight);

     levelScene->addItem(worldGrid);

     setCacheMode(CacheBackground);
     setViewportUpdateMode(BoundingRectViewportUpdate);
     setRenderHint(QPainter::Antialiasing);
     setTransformationAnchor(AnchorUnderMouse);
     scale(qreal(1.0), qreal(1.0));
     setMinimumSize(480, 350);

     snapToGrid = 32;

     player = new Player;

     levelScene->addItem(player);
}

void WorldView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF p = mapToScene(event->pos());

        if (MapEddi::currentlyAdding == TileObject)
        {
            addTile(p.x(), p.y());
        }
        else if (MapEddi::currentlyAdding == PlayerObject)
        {
            player->setX(p.x());
            player->setY(p.y());
            levelScene->update();
        }
        else if (MapEddi::currentlyAdding == FloatingTileStart)
        {
            addFloatingTile(p.x(), p.y(), MapEddi::selectedIndex, p.y(), 10);
            levelScene->update();
        }
    }
}

void WorldView::refreshView() {
       levelScene->update();
}

//Adds tile to grid at mouse press position.
void WorldView::addTile(int x, int y)
{
    int snappedX = x - (x%snapToGrid);
    int snappedY = y - (y%snapToGrid);

    addTile(snappedX, snappedY, MapEddi::selectedIndex, MapEddi::solidSelected);
}

void WorldView::addTile(int x, int y, int index, bool isSolid)
{
    Tile *tile = new Tile(index, x, y, true, isSolid, (MainWindow*)parentWidget(), this);
    levelScene->addItem(tile);

    tile_list.push_front(tile);
}

void WorldView::addFloatingTile(int x, int y, int index, int floatHeight, int maxThrust)
{
    int snappedX = x - (x%snapToGrid);
    int snappedY = y - (y%snapToGrid);

    FloatingTile *floatingTile = new FloatingTile(snappedX, snappedY, floatHeight, index, maxThrust, this);

    levelScene->addItem(floatingTile);
}

void WorldView::clearLevel()
{
    player->setX(0);
    player->setY(0);

    while (!tile_list.empty())
    {
        removeTile(tile_list.front());
    }
    while (!floating_tile_list.empty())
    {
        removeFloatingTile(floating_tile_list.front());
    }
}

void WorldView::removeTile(Tile *tile)
{
    levelScene->removeItem(tile);
    tile_list.remove(tile);
}

void WorldView::removeFloatingTile(FloatingTile *tile)
{
    levelScene->removeItem(tile);
    floating_tile_list.remove(tile);
}

//Sets the grid size.
void WorldView::setGridSize(int gridSize)
{
    worldGrid->setScale(gridSize);

    levelScene->update();

    snapToGrid = gridSize;
}

int WorldView::getPlayerX()
{
    return player->getX();
}

int WorldView::getPlayerY()
{
    return player->getY();
}

void WorldView::setPlayerX(int newX)
{
    player->setX(newX);
}

void WorldView::setPlayerY(int newY)
{
    player->setY(newY);
}
