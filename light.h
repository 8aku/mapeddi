#ifndef LIGHT_H
#define LIGHT_H
#include "gameobject.h"
class WorldView;
class QWidget;

struct g_colour {unsigned char r; unsigned char g; unsigned char b; unsigned char a;};

class Light : public GameObject
{
    Q_OBJECT

public:
    Light();
    Light (int x, int y, WorldView *worldView);
    Light (int x, int y, int radius, int r, int g, int b, int a, WorldView *worldView);
    QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getRadius();
    int getRed();
    int getGreen();
    int getBlue();
    int getAlpha();

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);

private:
   g_colour colour;
   int radius;
   QWidget *lightParameters;

private slots:
   void setRadius(int radius);
   void setRed (int vaue);
   void setGreen (int value);
   void setBlue (int value);
   void setAlpha (int value);
};

#endif // LIGHT_H
