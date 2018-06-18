#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <QGraphicsScene>
class QGraphicsSceneMouseEvent;

class LevelScene : public QGraphicsScene
{
public:
    LevelScene(QWidget *parent);
};

#endif // LEVELSCENE_H
