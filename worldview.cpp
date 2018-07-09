#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>
#include <QToolTip>

#include "bouncer.h"
#include "door.h"
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

     selectionRect = nullptr;
}

void WorldView::mousePressEvent(QMouseEvent *event)
{
     QPointF p = mapToScene(event->pos());

    if (event->button() == Qt::LeftButton && event->modifiers() != Qt::ControlModifier)
    {
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
            addMonster(p.x(), p.y(), MapEddi::selectedIndex, MapEddi::facingRight);
        }
        else if (MapEddi::currentlyAdding == SpikeObject)
        {
            addSpike(p.x(), p.y());
        }
        else if (MapEddi::currentlyAdding == BouncerObject)
        {
            addBouncer(MapEddi::selectedIndex, p.x(), p.y());
        }
        else if (MapEddi::currentlyAdding == DoorObject && event->modifiers() != Qt::ShiftModifier)
        {
            addDoor(MapEddi::selectedIndex, p.x(), p.y());
        }
    }
    else if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier)
    {
        if (selectionRect == nullptr)
        {
            qDebug() << "selection rect is nullptr";

            selectionRect = new SelectionRect(p.x(), p.y());
            levelScene->addItem(selectionRect);
            selectionRect->update();
            levelScene->update();
        }
    }
}

void WorldView::mouseReleaseEvent(QMouseEvent *event)
{
    if (selectionRect != nullptr)
    {
        if (event->modifiers() == Qt::ShiftModifier)
        {
            int startX = (int)selectionRect->getX() - ((int)selectionRect->getX() % snapToGrid);
            int startY = (int)selectionRect->getY() - ((int)selectionRect->getY() % snapToGrid);

            for (int i = 0; i < selectionRect->getW(); i+= snapToGrid)
            {
                for (int j = 0; j < selectionRect->getH(); j += snapToGrid)
                {
                    addTile(startX + i, startY + j);
                }
            }
        }
        else
        {
            for (auto t : tile_list)
            {
                if (t->getX() >= selectionRect->getX() &&
                        t->getX() <= selectionRect->getX() + selectionRect->getW() &&
                        t->getY() >= selectionRect->getY() &&
                        t->getY() <= selectionRect->getY() + selectionRect->getH())
                {
                    t->select();
                }
                else
                {
                    t->deselect();
                }
            }

            delete selectionRect;
            selectionRect = nullptr;
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

void WorldView::addDoor(int dest, int x, int y)
{
    int snappedX = x - (x % snapToGrid);
    int snappedY = y - (y % snapToGrid);

    Door *door = new Door(dest, snappedX, snappedY, this);

    levelScene->addItem(door);
    door_list.push_front(door);
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
    while (!door_list.empty())
    {
        removeDoor(door_list.front());
    }
    while (!bouncer_list.empty())
    {
        removeBouncer(bouncer_list.front());
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

void WorldView::removeDoor(Door *door)
{
    levelScene->removeItem(door);
    door_list.remove(door);
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
    QPointF p = mapToScene(event->pos());

    MapEddi::mouse_x = p.x();
    MapEddi::mouse_y = p.y();

    QString pos_tooltip( tr("x:%1, y:%2").arg(p.x()).arg(p.y()));
    QToolTip::showText(QPoint(x(), y()), pos_tooltip, this, QRect(x(), y(), width(), height()));

    if (selectionRect != nullptr)
    {
        selectionRect->setWidth(p.x() - selectionRect->getX());
        selectionRect->setHeight(p.y() - selectionRect->getY());

        levelScene->update();
    }
}

void WorldView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        std::forward_list<Tile*> selectedTiles;

        for (auto t : tile_list)
        {
            if (t->isSelected())
            {
                selectedTiles.push_front(t);
            }
        }

        for (auto t : selectedTiles)
        {
             removeTile(t);
             delete t;
        }

        selectedTiles.clear();
    }
}

