#include "tiledockview.h"
#include "tile.h"
#include "imagecontainer.h"
#include <QDebug>

TileDockView::TileDockView(QWidget *parent)
    : QGraphicsView(parent)
{
     setMouseTracking(true);
     tileScene = new QGraphicsScene(this);

     setScene(tileScene);

     init();

     setCacheMode(CacheBackground);
     setViewportUpdateMode(BoundingRectViewportUpdate);
     setRenderHint(QPainter::Antialiasing);
     setTransformationAnchor(AnchorUnderMouse);
     scale(qreal(1.0), qreal(1.0));
}

//Initializes the selected tile set within the left tile dock.
void TileDockView::init()
{
    for (unsigned int i = 0; i < ImageContainer::tileImages.size(); i++)
    {
        Tile *tile = new Tile(i, 0, i * 32, false, false, (MainWindow*)parentWidget(), NULL);
        tileScene->addItem(tile);
    }
}

void TileDockView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
