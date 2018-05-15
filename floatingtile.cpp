#include <QPainter>
#include <QBrush>
#include "floatingtile.h"
#include "imagecontainer.h"
#include "worldview.h"
#define DEFAULT_WIDTH 32
#define DEFAULT_HEIGHT 32

FloatingTile::FloatingTile()
{

}

FloatingTile::FloatingTile(int x, int y, int floatHeight, int index, int maxThrust, WorldView *worldview) : GameObject(x, y, DEFAULT_WIDTH, DEFAULT_HEIGHT, true, worldview)
{
   this->floatHeight = floatHeight;
   this->maxThrust = maxThrust;
   this->index = index;
}

FloatingTile::~FloatingTile() {
    if (worldView)
        worldView->removeFloatingTile(this);
}

//Pure virtual method needed for implementation (QT specific).
QRectF FloatingTile::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}

//Draws a tile. If solid, a border will appear around the tile.
void FloatingTile::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    painter->drawImage(boundingRect(), *(ImageContainer::tileImages.at(index)), QRectF(0.0, 0.0, getW(), getH()));

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(255, 0, 100, 255));
    painter->setPen(pen);

    QRectF cell (QRectF(getX(), floatHeight, getW(), getH()));
    painter->drawRect(cell);
}

int FloatingTile::getFloatHeight()
{
    return floatHeight;
}

int FloatingTile::getIndex()
{
    return index;
}

int FloatingTile::getMaxThrust()
{
    return maxThrust;
}
