#ifndef WORLDGRID_H
#define WORLDGRID_H
#include <QGraphicsItem>


class WorldGrid : public QGraphicsItem
{
public:
    WorldGrid();
    WorldGrid(int width, int height);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QRectF boundingRect() const;

    void resize(int width, int height);
    void setScale (int newScale);

private:
    int width, height, scale;

};

#endif // WORLDGRID_H
