#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>
#include <QToolTip>
#include <QTimeLine>

#include "bouncer.h"
#include "deathspot.h"
#include "door.h"
#include "floatingtile.h"
#include "light.h"
#include "levelscene.h"
#include "mapeddi.h"
#include "monsters.h"
#include "platform.h"
#include "rope.h"
#include "spike.h"
#include "save.h"
#include "tile.h"
#include "player.h"
#include "worldview.h"
#include "worldgrid.h"
#include "item.h"
#include "npcs.h"

WorldView::WorldView(QWidget *parent)
    : QGraphicsView(parent)
{
     setMouseTracking(true);
     levelScene = new LevelScene(this);
     setFrameStyle(Sunken | StyledPanel);

     levelScene->setBackgroundBrush(Qt::white);
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
        int snappedX = (int)p.x() - ((int)p.x()%snapToGrid);
        int snappedY = (int)p.y() - ((int)p.y()%snapToGrid);

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
            addFloatingTile(snappedX, snappedY, MapEddi::selectedIndex, p.y(), 10);
            levelScene->update();
        }
        else if (MapEddi::currentlyAdding == LightObject && event->modifiers() != Qt::ShiftModifier)
        {
            addLight(p.x(), p.y());
        }
        else if (MapEddi::currentlyAdding == MonsterObject)
        {
            addMonster(snappedX, snappedY, MapEddi::selectedIndex, MapEddi::facingRight);
        }
        else if (MapEddi::currentlyAdding == ItemObject)
        {
            addItem(snappedX, snappedY, MapEddi::selectedIndex);
        }
        else if (MapEddi::currentlyAdding == DeathSpotObject)
        {
            addDeathSpot( snappedX, snappedY );
        }
        else if (MapEddi::currentlyAdding == NpcObject)
        {
            addNpcs(snappedX, snappedY, MapEddi::selectedIndex);
        }
        else if (MapEddi::currentlyAdding == SpikeObject)
        {
            addSpike(snappedX, snappedY);
        }
        else if (MapEddi::currentlyAdding == SaveObject)
        {
            addSave(snappedX, snappedY);
        }
        else if (MapEddi::currentlyAdding == RopeObject)
        {
            addRope(snappedX, snappedY);
        }
        else if (MapEddi::currentlyAdding == BouncerObject)
        {
            addBouncer(MapEddi::selectedIndex, snappedX, snappedY);
        }
        else if (MapEddi::currentlyAdding == PlatformObject)
        {
            addPlatform(snappedX, snappedY);
        }
        else if (MapEddi::currentlyAdding == DoorObject && event->modifiers() != Qt::ShiftModifier)
        {
            addDoor(0, 0, MapEddi::selectedIndex, snappedX, snappedY);
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
                    if (MapEddi::currentlyAdding == TileObject)
                        addTile(startX + i, startY + j);
                    else if (MapEddi::currentlyAdding == RopeObject)
                        addRope(startX + i, startY + j);
                    else if (MapEddi::currentlyAdding == DeathSpotObject)
                        addDeathSpot(startX + i, startY + j);
                }
            }
        }
        else
        {
            for (auto g : gameobject_list)
            {
                if (g->getX() >= selectionRect->getX() &&
                        g->getX() <= selectionRect->getX() + selectionRect->getW() &&
                        g->getY() >= selectionRect->getY() &&
                        g->getY() <= selectionRect->getY() + selectionRect->getH())
                {
                    g->select();
                }
                else
                {
                    g->deselect();
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
    Spike *spike = new Spike(x, y, this);
    levelScene->addItem(spike);

    spike_list.push_front(spike);
}

void WorldView::addSave(int x, int y)
{
    Save *save = new Save(x, y, this);
    levelScene->addItem(save);

    save_list.push_front(save);

    qDebug() << "adding save \n";

}

void WorldView::addDeathSpot( int x, int y )
{
    DeathSpot *deathspot = new DeathSpot( x, y, this );

    levelScene->addItem(deathspot);

    deathspot_list.push_front(deathspot);
}

void WorldView::addItem(int x, int y, int type)
{
    Item *item = new Item( x, y, type, this);

    levelScene->addItem(item);

   item_list.push_front(item);

}

void WorldView::addNpcs(int x, int y, int type)
{

    Npcs *npcs = new Npcs( x, y, type, this);

    levelScene->addItem(npcs);

   npcs_list.push_front(npcs);

}

void WorldView::addRope(int x, int y)
{

    Rope *rope = new Rope(x, y, this);
    levelScene->addItem(rope);

    rope_list.push_front(rope);
}

void WorldView::addBouncer(int index, int x, int y)
{

    Bouncer *bouncer = new Bouncer(index, x, y, this);
    levelScene->addItem(bouncer);
    bouncer_list.push_front(bouncer);
}

void WorldView::addPlatform(int x, int y)
{
    Platform *platform = new Platform(x, y, this);
    levelScene->addItem(platform);
    platform_list.push_front(platform);
}

void WorldView::addPlatform(int x, int y, int dx)
{
    Platform *platform = new Platform(x, y, dx, this);
    levelScene->addItem(platform);
    platform_list.push_front(platform);
}

void WorldView::addDoor(int destX, int destY, int dest, int x, int y)
{
    Door *door = new Door(destX, destY, dest, x, y, this);

    levelScene->addItem(door);
    door_list.push_front(door);
}

void WorldView::addMonster(int x, int y, int type, bool facingRight)
{
    Monsters *monster = new Monsters (x, y, type, facingRight, this);

    levelScene->addItem(monster);

    monsters_list.push_front(monster);
}

void WorldView::addFloatingTile(int x, int y, int index, int floatHeight, int maxThrust)
{
    FloatingTile *floatingTile = new FloatingTile(x, y, y, index, maxThrust, this);

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
    while (!rope_list.empty())
    {
        removeRope(rope_list.front());
    }
    while (!door_list.empty())
    {
        removeDoor(door_list.front());
    }
    while (!bouncer_list.empty())
    {
        removeBouncer(bouncer_list.front());
    }
    while (!platform_list.empty())
    {
        removePlatform(platform_list.front());
    }
    while (!item_list.empty())
    {
        removeItem(item_list.front());
    }
    while (!npcs_list.empty())
    {
        removeNpcs(npcs_list.front());
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

void WorldView::removeRope(Rope *rope)
{
    levelScene->removeItem(rope);
    rope_list.remove(rope);
}

void WorldView::removeBouncer(Bouncer *bouncer)
{
    levelScene->removeItem(bouncer);
    bouncer_list.remove(bouncer);
}

void WorldView::removePlatform(Platform *platform)
{
    levelScene->removeItem(platform);
    platform_list.remove(platform);
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

void WorldView::removeSave(Save *save)
{
    levelScene->removeItem(save);
    save_list.remove(save);
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

void WorldView::removeItem(Item *item)
{
    levelScene->removeItem(item);
    item_list.remove(item);
}

void WorldView::removeNpcs(Npcs *npcs)
{
    levelScene->removeItem(npcs);
    npcs_list.remove(npcs);
}
void WorldView::removeDeathSpot(DeathSpot *deathspot)
{
    levelScene->removeItem( deathspot );
    deathspot_list.remove( deathspot );
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
        std::forward_list<GameObject*> selectedObjects;

        for (auto t : gameobject_list)
        {
            if (t->isSelected())
            {
                selectedObjects.push_front(t);
            }
        }

        for (auto o : selectedObjects)
        {
            removeGameObject(o);

                //having destructors remove from appropriate lists automatically
                //would solve all of this dynamic casting...
            if (Tile *t = dynamic_cast<Tile*>(o))
                removeTile(t);
            else if (Bouncer *b = dynamic_cast<Bouncer*>(o))
                removeBouncer(b);
            else if (DeathSpot *d = dynamic_cast<DeathSpot*>(o))
                removeDeathSpot(d);
            else if (Door *d = dynamic_cast<Door*>(o))
                removeDoor(d);
            else if (FloatingTile* f = dynamic_cast<FloatingTile*>(o))
                removeFloatingTile(f);
            else if (Item *i = dynamic_cast<Item*>(o))
                removeItem(i);
            else if (Light *l = dynamic_cast<Light*>(o))
                removeLight(l);
            else if (Monsters *m = dynamic_cast<Monsters*>(o))
                removeMonsters(m);
            else if (Npcs *n = dynamic_cast<Npcs*>(o))
                removeNpcs(n);
            else if (Platform* p = dynamic_cast<Platform*>(o))
                removePlatform(p);
            else if (Rope* r = dynamic_cast<Rope*>(o))
                removeRope(r);
            else if (Save *s = dynamic_cast<Save*>(o))
                removeSave(s);
            else if (Spike * s = dynamic_cast<Spike*>(o))
                removeSpike(s);

             delete o;
        }

        selectedObjects.clear();
    }
}

void WorldView::animFinished()
{
 if (_numScheduledScalings > 0)
 _numScheduledScalings--;
 else
 _numScheduledScalings++;
 sender()->~QObject();
}


void WorldView::wheel ( QWheelEvent * event )
{
 int numDegrees = event->delta() / 8;
 int numSteps = numDegrees / 15; // see QWheelEvent documentation
 _numScheduledScalings += numSteps;
 if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
 _numScheduledScalings = numSteps;

 QTimeLine *anim = new QTimeLine(350, this);
 anim->setUpdateInterval(20);

 connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
 connect(anim, SIGNAL (finished()), SLOT (animFinished()));
 anim->start();
}

void WorldView::scalingTime(qreal x)
{
 qreal factor = 1.0+ qreal(_numScheduledScalings) / 300.0;
 scale(factor, factor);
}

void WorldView::addGameObject(GameObject *object)
{
    gameobject_list.push_front(object);
}

void WorldView::removeGameObject(GameObject *object)
{
    gameobject_list.remove(object);
}
