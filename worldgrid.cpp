#include "worldgrid.h"
#include <QPainter>
#define DEFAULT_SCALE 32

WorldGrid::WorldGrid()
    : WorldGrid(0, 0)
{
    ;

}

WorldGrid::WorldGrid(int width, int height)
{
    this->width = width;
    this->height = height;
    this->scale = DEFAULT_SCALE;
}

void WorldGrid::setScale(int newScale)
{
    scale = newScale;
}

void WorldGrid::resize(int width, int height)
{
    this->width = width;
    this->height = height;
}

//Draws the World Grid.
void WorldGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(150, 150, 150, 100));
    painter->setPen(pen);

    for (int i = 0; i < width; i+= scale)
    {
        for (int j = 0; j < height; j+= scale)
        {
            QRectF cell (i, j, scale, scale);
            painter->drawRect(cell);
        }
    }
}

//Pure virtual method needed for implementation (QT specific).
QRectF WorldGrid::boundingRect() const
{
    return QRectF(0, 0, width, height);
}
