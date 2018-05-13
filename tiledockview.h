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

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QGraphicsScene *tileScene;
    void init();
};

#endif // TILEDOCKVIEW_H
