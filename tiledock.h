#ifndef TILEDOCK_H
#define TILEDOCK_H
#include <QDockWidget>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>

class Tile;
class QWidget;


class TileDock : public QGraphicsView
{
public:
    void initialize();

private:
    QGraphicsScene *tileScene;
};

#endif // TILEDOCK_H
