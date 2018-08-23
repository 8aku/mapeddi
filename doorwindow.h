#ifndef DOORWINDOW_H
#define DOORWINDOW_H

#include <QWidget>

class QIntValidator;
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
    void setDest(const QString &dest);
    void setDestX(const QString &dest);
    void setDestY(const QString &dest);
    void toggleLocked();

private:
    QIntValidator* validator;
    Door *door;
};


#endif // DOORWINDOW_H
