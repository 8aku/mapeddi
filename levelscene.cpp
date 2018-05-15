#include "levelscene.h"
#include "tile.h"
#include <QDebug>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>

LevelScene::LevelScene(QWidget *parent)
{
    mouseLabel = new QLabel(tr("<%1, %2>").arg(mouseX, mouseY));

    addWidget(mouseLabel);
}

void LevelScene::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->pos();

    mouseX = p.x();
    mouseY = p.y();

    mouseLabel->setText(tr("%1").arg(mouseX));
}
