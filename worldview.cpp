#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>

#include "bouncer.h"
#include "floatingtile.h"
#include "light.h"
#include "levelscene.h"
#include "mapeddi.h"
#include "monsters.h"
#include "spike.h"
#include "tile.h"
#include "player.h"
#include "worldview.h"
#include "worldgrid.h"

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
            //change these default values to be editable
            addFloatingTile(p.x(), p.y(), MapEddi::selectedIndex, p.y(), 10);
            levelScene->update();
        }
        else if (MapEddi::currentlyAdding == LightObject && event->modifiers() != Qt::ShiftModifier)
        {
            addLight(p.x(), p.y());
        }
        else if (MapEddi::currentlyAdding == MonsterObject)
        {
            addMonster(p.x(), p.y(), MapEddi::selectedIndex, false);
        }
        else if (MapEddi::currentlyAdding == SpikeObject)
        {
            addSpike(p.x(), p.y());
        }
        else if (MapEddi::currentlyAdding == BouncerObject)
        {
            addBouncer(MapEddi::selectedIndex, p.x(), p.y());
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

    addTile(snappedX, snappedY, MapEddi::selectedIndex, MapEddi::solidSelected, MapEddi::selectedLayer);
}

void WorldView::addTile(int x, int y, int index, bool isSolid, int layer)
{
    Tile *tile = new Tile(index, x, y, true, isSolid, layer, (MainWindow*)parentWidget(), this);
    levelScene->addItem(tile);

    tile_list.push_front(tile);
}

void WorldView::addSpike(int x, int y)
{
    int snappedX = x - (x%snapToGrid);
    int snappedY = y - (y%snapToGrid);

    Spike *spike = new Spike(snappedX, snappedY, this);
    levelScene->addItem(spike);

    spike_list.push_front(spike);
}

void WorldView::addBouncer(int index, int x, int y)
{
    int snappedX = x - (x % snapToGrid);
    int snappedY = y - (y % snapToGrid);

    Bouncer *bouncer = new Bouncer(index, snappedX, snappedY, this);
    levelScene->addItem(bouncer);
    bouncer_list.push_front(bouncer);
}

void WorldView::addMonster(int x, int y, int type, bool facingRight)
{
    Monsters *monster = new Monsters (x, y, type, facingRight, this);

    int snappedX = x - (x%snapToGrid);
    int snappedY = y - (y%snapToGrid);

    levelScene->addItem(monster);

    monsters_list.push_front(monster);
}

void WorldView::addFloatingTile(int x, int y, int index, int floatHeight, int maxThrust)
{
    int snappedX = x - (x%snapToGrid);
    int snappedY = y - (y%snapToGrid);

    FloatingTile *floatingTile = new FloatingTile(snappedX, snappedY, snappedY, index, maxThrust, this);

    levelScene->addItem(floatingTile);

    floating_tile_list.push_front(floatingTile);
}

void WorldView::addLight(int x, int y)
{
    Light *light = new Light(x, y, this);
    levelScene->addItem(light);

    light_list.push_front(light);
}

void WorldView::addLight(int x, int y, int radius, int r, int g, int b, int a)
{
    Light *light = new Light(x, y, radius, r, g, b, a, this);
    levelScene->addItem(light);

    light_list.push_front(light);
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
    while (!light_list.empty())
    {
        removeLight(light_list.front());
    }
    while (!monsters_list.empty())
    {
        removeMonsters(monsters_list.front());
    }
    while (!spike_list.empty())
    {
        removeSpike(spike_list.front());
    }
}

void WorldView::removeTile(Tile *tile)
{
    levelScene->removeItem(tile);
    tile_list.remove(tile);
}

void WorldView::removeSpike(Spike *spike)
{
    levelScene->removeItem(spike);
    spike_list.remove(spike);
}

void WorldView::removeBouncer(Bouncer *bouncer)
{
    levelScene->removeItem(bouncer);
    bouncer_list.remove(bouncer);
}

void WorldView::removeFloatingTile(FloatingTile *tile)
{
    levelScene->removeItem(tile);
    floating_tile_list.remove(tile);
}

void WorldView::removeMonsters(Monsters *monster)
{
    levelScene->removeItem(monster);
    monsters_list.remove(monster);
}

void WorldView::removeLight(Light *light)
{
    levelScene->removeItem(light);
    light_list.remove(light);
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

void WorldView::mouseMoveEvent (QMouseEvent *event)
{
    QPointF p = event->pos();

    levelScene->setLabel(tr("x: %1 y: %2").arg(p.x()).arg(p.y()));
}
