#ifndef DOORWINDOW_H
#define DOORWINDOW_H

#include <QWidget>

class Door;

class DoorWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DoorWindow(QWidget *parent = 0);
    DoorWindow (Door *door, QWidget *parent);
    ~DoorWindow();
signals:

public slots:
    void setDest(int dest);
    void setDestX(int destX);
    void setDestY(int destY);
    void toggleLocked();

private:
    Door *door;
};


#endif // DOORWINDOW_H
