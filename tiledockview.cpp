#include "tiledockview.h"
#include "monsters.h"
#include "tile.h"
#include "imagecontainer.h"
#include "item.h"
#include "npcs.h"
#include <QDebug>

TileDockView::TileDockView(QWidget *parent)
    : QGraphicsView(parent)
{
     setMouseTracking(true);
     tileScene = new QGraphicsScene(this);
     tileScene->setBackgroundBrush(Qt::white);
     setScene(tileScene);

     setCacheMode(CacheBackground);
     setViewportUpdateMode(BoundingRectViewportUpdate);
     setRenderHint(QPainter::Antialiasing);
     setTransformationAnchor(AnchorUnderMouse);
     scale(qreal(1.0), qreal(1.0));
}

//Initializes the selected tile set within the left tile dock.
void TileDockView::initTiles()
{
    for (unsigned int i = 0; i < ImageContainer::tileImages.size(); i++)
    {
        Tile *tile = new Tile(i, (i % 2) * 34, (i/2) * 34, false, false, 0, (MainWindow*)parentWidget(), NULL);
        tileScene->addItem(tile);
    }
}

void TileDockView::initMonsters()
{
    bool facingRight = false;
    for (unsigned int i = 0; i < ImageContainer::monsterImages.size(); i++)
    {
        Monsters *m1 = new Monsters((i % 2) * 34, (i/2) * 34, i/2, facingRight, NULL);
        facingRight = !facingRight;
        m1->setDeletable(false);
        tileScene->addItem(m1);
    }
}

    void TileDockView::initItems()
    {
        for (unsigned int i = 0; i < ImageContainer::itemImages.size(); i++)
        {
            Item *item = new Item((i % 2) * 34, (i/2) * 34, i, NULL);
            item->setDeletable(false);
            tileScene->addItem(item);
        }
    }

    void TileDockView::initNpcs()
    {
        for (unsigned int i = 0; i < ImageContainer::npcImages.size(); i++)
        {
           Npcs *npc = new Npcs((i % 2) * 34, (i/2) * 34, i, NULL);
            npc->setDeletable(false);
            tileScene->addItem(npc);
        }
    }

void TileDockView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
