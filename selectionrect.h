#ifndef SELECTIONRECT_H
#define SELECTIONRECT_H
#include <QGraphicsObject>
#include "utils.h"


class SelectionRect : public QGraphicsObject
{
public:
    SelectionRect();
    virtual ~SelectionRect();
    SelectionRect(int x, int y);
    QRectF boundingRect() const;
    void setWidth(int w);
    void setHeight(int h);
    int getW();
    int getH();
    int getX();
    int getY();
    void setPos(int x, int y);
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int w, h;
    Point pos;

};

#endif // SELECTIONRECT_H
