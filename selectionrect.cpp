#include "selectionrect.h"
#include <QPen>
#include <QPainter>
#include <QDebug>

SelectionRect::SelectionRect()
{
    w = 32;
    h = 32;
}

SelectionRect::SelectionRect(int x, int y)
{
    pos.x = x;
    pos.y = y;
    w = 32;
    h = 32;
}

SelectionRect::~SelectionRect()
{
    ;
}

//Pure virtual method needed for implementation (QT specific).
QRectF SelectionRect::boundingRect() const
{
    return QRectF(pos.x, pos.y, w, h);
}

//Draws a tile. If solid, a border will appear around the tile.
void SelectionRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor brushColour(60, 20, 150, 100);
    painter->fillRect(boundingRect(), QBrush(brushColour));
}

void SelectionRect::setWidth(int w)
{
    this->w = w;
}

void SelectionRect::setHeight(int h)
{
    this->h = h;
}

void SelectionRect::setPos(int x, int y)
{
    this->pos.x = x;
    this->pos.y = y;
}

int SelectionRect::getX()
{
    return pos.x;
}

int SelectionRect::getY()
{
    return pos.y;
}

int SelectionRect::getW()
{
    return w;
}

int SelectionRect::getH()
{
    return h;
}
