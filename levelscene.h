#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <QGraphicsScene>
class QGraphicsSceneMouseEvent;
class QLabel;

class LevelScene : public QGraphicsScene
{
public:
    LevelScene(QWidget *parent);

private:
    int mouseX;
    int mouseY;
    QLabel *mouseLabel;

protected:
    void mouseMoveEvent (QGraphicsSceneMouseEvent *event);


};

#endif // LEVELSCENE_H
