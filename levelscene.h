#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <QGraphicsScene>
class QGraphicsSceneMouseEvent;
class QLabel;

class LevelScene : public QGraphicsScene
{
public:
    LevelScene(QWidget *parent);
    void setLabel (QString labelString);

private:
    QLabel *mouseLabel;
};

#endif // LEVELSCENE_H
