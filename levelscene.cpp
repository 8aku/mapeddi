#include "levelscene.h"
#include "tile.h"
#include <QDebug>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>

LevelScene::LevelScene(QWidget *parent)
{
    mouseLabel = new QLabel(tr("<%1 xxxxxxx %2>").arg("x").arg("x"));

    addWidget(mouseLabel);
}

void LevelScene::setLabel (QString labelString)
{
    mouseLabel->setText(labelString);
}
