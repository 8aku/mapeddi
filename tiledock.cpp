#include "tiledock.h"
#include "imagecontainer.h"
#include "tile.h"
#include <QGraphicsScene>
#include <QGraphicsView>

TileDock::TileDock()
{
    ;
}

TileDock::TileDock(QString title, QWidget *parent) : QDockWidget(title, parent)
{
    QGraphicsView *tileView = new QGraphicsView(this);
    setWidget(tileView);
    tileScene = new QGraphicsScene(tileView);

    initialize();
}

void TileDock::initialize()
{
    for(unsigned int i; i < ImageContainer::tileImages.size(); i++)
    {
        Tile *tile = new Tile(i, 0, i * 32);

        tileScene->addItem(tile);

    }
}
