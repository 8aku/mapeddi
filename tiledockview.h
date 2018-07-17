#ifndef TILEDOCKVIEW_H
#define TILEDOCKVIEW_H
#include <QGraphicsScene>
#include <QGraphicsView>
class QMouseEvent;


class TileDockView : public QGraphicsView    
{
    Q_OBJECT
public:
    explicit TileDockView(QWidget *parent = 0);
    void initMonsters();
    void initTiles();
    void initItems();
    void initNpcs();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QGraphicsScene *tileScene;
    //void init();

};

#endif // TILEDOCKVIEW_H
