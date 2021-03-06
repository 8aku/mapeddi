#include <QDebug>
#include <QPainter>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "mapeddi.h"
#include "tile.h"
#include "imagecontainer.h"
#include "mainwindow.h"
#include "worldview.h"

#define DEFAULT_WIDTH 16

#define DEFAULT_HEIGHT 16


Tile::Tile()
    :Tile(0,0,0, true, true, 0, NULL, NULL)
{
    qDebug() << "Calling null";
}

Tile::Tile(int x, int y) : Tile(0, x, y, true, true, 0, NULL, NULL)
{
     qDebug() << "Calling null";
}

Tile::Tile(int index, int x, int y, bool isDeletable, bool isSolid, int layer, MainWindow *mainWindow, WorldView *worldView) :
        GameObject(x, y,
                   ImageContainer::tileImages.at(index)->width(),
                   ImageContainer::tileImages.at(index)->height(),
                   isDeletable, worldView)
{
    setLayer(layer);
    solid = isSolid;
    tileIndex = index;
    this->mainWindow = mainWindow;
}

Tile::~Tile()
{
    if (worldView)
        worldView->removeTile(this);
}

//Pure virtual method needed for implementation (QT specific).
QRectF Tile::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}

//Draws a tile. If solid, a border will appear around the tile.
void Tile::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    painter->drawImage(boundingRect(), *(ImageContainer::tileImages.at(tileIndex)), QRectF(0.0, 0.0, getW(), getH()));

    if (solid)
    {
        QPen pen;
        pen.setWidth(1);
        pen.setColor(QColor(0, 255, 100, 255));
        painter->setPen(pen);

        QRectF cell (QRectF(getX(), getY(), getW(), getH()));
        painter->drawRect(cell);
    }

    GameObject::paint(painter, option, widget);
}

//Places or deletes the selected tile.
void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        MapEddi::selectedIndex = tileIndex;

        MapEddi::currentlyAdding = TileObject;

        mainWindow->selectTile();
    }

    GameObject::mousePressEvent(event);
}

int Tile::getTileIndex()
{
    return tileIndex;
}

bool Tile::isSolid()
{
    return solid;
}
