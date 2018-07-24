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
    int tileset;
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *layerMenu;
    QMenu *addMenu;
    QMenu *addMonsterMenu;
    QMenu *tilesetMenu;

    QAction *addNpcs;
    QAction *addItem;
    QAction *addMonster;
    QAction *addTile;
    QAction *addBouncer;
    QAction *addDoor;
    QAction *addLight;
    QAction *addPlayer;
    QAction *addFloatingTile;
    QAction *addSpike;
    QAction *addRope;
    QAction *addSave;
    QAction *addDeathSpot;

    /*QAction *addSerg;
    QAction *addPuff;
    QAction *addJelly;
    QAction *addCrabber;
    QAction *addEdo;
    QAction *addShroom;
    QAction *addSkull;
    QAction *addWalker;
    QAction *addXe;*/

    QAction *tileset1;
    QAction *tileset2;
    QAction *tileset3;

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

    QDockWidget *tileDock;
    QDockWidget *monsterDock;
    QDockWidget *itemDock;
    QDockWidget *npcsDock;

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
    void setTileset(int tileset);
};

#endif // MAINWINDOW_H
