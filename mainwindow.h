#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QComboBox>
#include <QCheckBox>
#include <QFile>
#include <QGroupBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QWindow>
#include <QAction>
#include <QMenuBar>
#include <QPushButton>
#include "mapeddi.h"
class WorldView;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void selectTile();

//protected:
    //void mouseMoveEvent (QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *layerMenu;
    QMenu *addMenu;
    QMenu *addMonsterMenu;

    QAction *addLight;
    QAction *addPlayer;
    QAction *addFloatingTile;
    QAction *addSerg;
    QAction *addPuff;
    QAction *addJelly;
    QAction *addCrabber;
    QAction *addSpike;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;

    QAction *layer0;
    QAction *layer1;
    QAction *layer2;
    QAction *layer3;
    QAction *layer4;
    QAction *layer5;
    QAction *layer6;
    WorldView *worldView;
    QLabel *currentLayer;
    QLabel *currentObject;

    void createDockWindows();
    void createActions();
    void createMenus();
    void loadPlayer();
    void loadTile();
    void loadLevelHeader();

private slots:
    void newFile();
    void open();
    void save();
    void saveas();
    void setGridSize(int gridSize);
    void selectLayer(int layer);
    void setSolid();
    void setAdding(int newType);
};

#endif // MAINWINDOW_H
