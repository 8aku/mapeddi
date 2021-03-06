#include <QDebug>
#include <QFileDialog>
#include <QDockWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSignalMapper>

#include "npcs.h"
#include "item.h"
#include "mainwindow.h"
#include "bouncer.h"
#include "deathspot.h"
#include "door.h"
#include "tiledockview.h"
#include "ui_mainwindow.h"
#include "worldview.h"
#include "mapeddi.h"
#include "rope.h"
#include "spike.h"
#include "gameobject.h"
#include "imagecontainer.h"
#include "floatingtile.h"
#include "tile.h"
#include "light.h"
#include "monsters.h"
#include "platform.h"
#include "save.h"
#include "slowspot.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDir>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    worldView = new WorldView(this);
    setCentralWidget(worldView);
    createActions();
    createMenus();
    createDockWindows();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    worldView->clearLevel();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files(*.*)"));

    if (fileName != NULL)
    {
        worldView->clearLevel();
        MapEddi::currentFile = fileName;

        //should clear existing map here
        std::string fileNameStr = fileName.toUtf8().constData();
        std::fstream inputFile (fileNameStr.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

        if (inputFile.is_open())
        {
            bool done = false;
            int currentType;
            int size = inputFile.tellg();
            int *input;
            input = new int[size];

            inputFile.seekg (0, std::ios::beg);
            inputFile.read ((char*)input, size * sizeof (int));
            inputFile.close();

            while(!done)
            {
                currentType = *input;

                if (currentType == 0)
                {
                    qDebug() << "adding environment settings\n";

                    //level width/level height
                    MapEddi::levelWidth = input[3];
                    MapEddi::levelHeight = input[4];
                    worldView->resize(MapEddi::levelWidth, MapEddi::levelHeight);
                    worldView->resizeGrid(MapEddi::levelWidth, MapEddi::levelHeight);

                    input += 5;
                    qDebug() << "map width: " << MapEddi::levelWidth << "\n";
                }
                else if (currentType == 1)
                {
                    qDebug() << "adding player\n";
                    worldView->setPlayerX(input[1]);
                    worldView->setPlayerY(input[2]);
                    input += 3;
                }
                else if (currentType == 2)
                {
                    worldView->addTile(input[1], input[2], input[3], input[4], input[5]);
                    input +=6;
                }
                else if (currentType == 3)
                {
                    worldView->addFloatingTile(input[1], input[2], input[3], input[4], input[5]);

                    input +=6;
                }
                else if (currentType == 4)
                {
                    worldView->addLight(input[1], input[2], input[3], input[4], input[5], input[6], input[7]);

                    input += 8;
                }
                else if (currentType == 5)
                {
                    if (input[3] < 10 && input[3] >= 0)
                        worldView->addMonster(input[1], input[2], input[3], input[4]);

                    input += 5;
                }
                else if (currentType == 6)
                {
                    worldView->addSpike(input[1], input[2]);

                    input += 3;
                }
                else if (currentType == 7)
                {
                    worldView->addBouncer(input[1], input[2], input[3]);
                    input += 4;
                }
                else if (currentType == 8)
                {
                    worldView->addDoor(input[1], input[2], input[3], input[4], input[5], (bool)input[6]);
                    input += 7;
                }
                else if (currentType == 9)
                {
                    worldView->addRope(input[1], input[2]);

                    input += 3;
                }
                else if (currentType == 10)
                {
                    if (input[3] >= 0 && input[3] <= 3)
                    {
                        worldView->addItem(input[1], input[2], input[3]);
                    }
                    input += 4;
                }
                else if (currentType == 11)
                {
                    if (input[3] < 0 || input[3] > 3)
                        qDebug() << "Invalid NPC type: " << input[3] << "\n";
                    else
                        worldView->addNpcs(input[1], input[2], input[3]);
                    input += 4;
                }
                else if (currentType == 12)
                {
                    worldView->addSave(input[1], input[2]);
                    input += 3;
                }
                else if (currentType == 13)
                {
                    worldView->addDeathSpot(input[1], input[2]);
                    input += 3;
                }
                else if (currentType == 14)
                {
                    worldView->addPlatform(input[1], input[2], input[3]);
                    input += 4;
                }
                else if (currentType == 15)
                {
                    worldView->addSlowSpot(input[1], input[2]);
                    input += 3;
                }
                else if (currentType == -1)
                {
                    done = true;
                }
            }
        }
    }
}

void MainWindow::save()
{
    QFile outFile(MapEddi::currentFile);

    if (!outFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not open file to be written";
    }
    else
    {
        QDataStream out (&outFile);
        out.setByteOrder(QDataStream::LittleEndian);

        //save level header 0
        out << 0;
        //background 1
        out << 0;
        //tile set 2
        out << tileset;
        //level width 3
        out << MapEddi::levelWidth;
        qDebug() << "saved width: " << MapEddi::levelWidth;
        //level height 4
        out << MapEddi::levelHeight;

        out << 1;
        //save player X 4
        out << worldView->getPlayerX();
        //save player Y 5
        out <<worldView->getPlayerY();

        //save tiles
        for (auto tile : worldView->tile_list)
        {
            out << (int)2;
            out << tile->getX();
            out << tile->getY();
            out << tile->getTileIndex();
            out << (int)tile->isSolid();
            out << tile->getLayer();
        }

        for (auto tile : worldView->floating_tile_list)
        {
            out << (int)3;
            out << tile->getX();
            out << tile->getY();
            out << tile->getIndex();
            out << tile->getFloatHeight();
            out << tile->getMaxThrust();
        }

        for (auto light = worldView->light_list.begin(); light != worldView->light_list.end(); ++light)
        {
            out << (int)4;
            out << (*light)->getX();
            out << (*light)->getY();
            out << (*light)->getRadius();
            out << (*light)->getRed();
            out << (*light)->getGreen();
            out << (*light)->getBlue();
            out << (*light)->getAlpha();
        }
        for (auto monster : worldView->monsters_list)
        {
            if (monster->getType() <= 10) {
                out << (int)5;
                out << monster->getX();
                out << monster->getY();
                out << monster->getType();
                out << (int)monster->getFacingRight();
            }
            else
                qDebug() << "not writing invalid monster: " << monster->getType() << "\n";
        }
        for (auto spike : worldView->spike_list)
        {
            out << (int)6;
            out << spike->getX();
            out << spike->getY();
        }
        for (auto bouncer : worldView->bouncer_list)
        {
            out << (int)7;
            out << bouncer->getIndex();
            out << bouncer->getX();
            out << bouncer->getY();
        }
        for (auto door : worldView->door_list)
        {
            out << (int)8;
            out << door->getDestX();
            out << door->getDestY();
            out << door->getDest();
            out << door->getX();
            out << door->getY();
            out << (int)door->getLocked();
        }
        for (auto rope : worldView->rope_list)
        {
            out << (int)9;
            out << rope->getX();
            out << rope->getY();
        }
        for (auto item : worldView->item_list)
        {
            out << (int)10;
            out << item->getX();
            out << item->getY();
            out << item->getType();
        }
        for (auto npcs : worldView->npcs_list)
        {
            out << (int)11;
            out << npcs->getX();
            out << npcs->getY();
            out << npcs->getType();
        }
        for (auto save : worldView->save_list)
        {
            out << (int)12;
            out << save->getX();
            out << save-> getY();
        }
        for (auto deathspot : worldView->deathspot_list)
        {
            out << (int)13;
            out << deathspot->getX();
            out << deathspot->getY();
        }
        for (auto p : worldView->platform_list)
        {
            out << (int)14;
            out << p->getX();
            out << p->getY();
            out << p->getDx();
        }
        for (auto slowspot: worldView->slowspot_list)
        {
            out << (int)15;
            out << slowspot->getX();
            out << slowspot->getY();
        }
        out << -1;
        outFile.flush();
        outFile.close();
    }
}

void MainWindow::saveas()
{
    QString selFilter = "AllFiles (*.*)";

    MapEddi::currentFile = QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath(), "AllFiles(*.*)", &selFilter);
    save();
}

//Creates actions for drop-down menu.
void MainWindow::createActions()
{
    levelSettings = new QAction(tr("&Level Size"), this);
    connect(levelSettings, SIGNAL(triggered()), this, SLOT(editSettings()));

    newAction = new QAction(tr("&New"), this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new level file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a level file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save current level"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("&Save As"), this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save current level as..."));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveas()));

    layer0 = new QAction(tr("Layer &0"), this);
    layer1 = new QAction(tr("Layer &1"), this);
    layer2 = new QAction(tr("Layer &2"), this);
    layer3 = new QAction(tr("Layer &3"), this);
    layer4 = new QAction(tr("Layer &4"), this);
    layer5 = new QAction(tr("Layer &5"), this);
    layer6 = new QAction(tr("Layer &6"), this);

     QSignalMapper *signalMapper = new QSignalMapper(this);

    connect(layer0, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(layer1, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(layer2, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(layer3, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(layer4, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(layer5, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(layer6, SIGNAL(triggered()), signalMapper, SLOT(map()));

    signalMapper->setMapping(layer0, 0);
    signalMapper->setMapping(layer1, 1);
    signalMapper->setMapping(layer2, 2);
    signalMapper->setMapping(layer3, 3);
    signalMapper->setMapping(layer4, 4);
    signalMapper->setMapping(layer5, 5);
    signalMapper->setMapping(layer6, 6);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(selectLayer(int)));

    //adding menu
    addPlayer = new QAction(tr("Player"), this);
    addFloatingTile = new QAction(tr("Floating Tile"), this);
    addLight = new QAction(tr("Light"), this);
    addSpike = new QAction(tr("Spike"), this);
    addRope = new QAction(tr("Rope"), this);
    addBouncer = new QAction(tr("Bouncer"), this);
    addPlatform = new QAction(tr("Platform"), this);
    addDoor = new QAction(tr("Door"), this);
    addSave = new QAction(tr("Save"), this);
    addDeathSpot = new QAction(tr("Death Spot :E"), this);
    addSlowSpot = new QAction(tr("slooooow spot"), this);

    addMonster = new QAction(tr("Monster"), this);
    addTile = new QAction(tr("Tile"), this);
    addItem = new QAction(tr("Item"), this);
    addNpcs = new QAction(tr("Npc :)"), this);

    QSignalMapper *addingMapper = new QSignalMapper(this);

    connect(addPlayer, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect(addFloatingTile, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addLight, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addSpike, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addSave, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addRope, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addBouncer, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addPlatform, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addDoor, SIGNAL(triggered()), addingMapper, SLOT(map()));

    connect (addTile, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addMonster, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addItem, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addNpcs, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addDeathSpot, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect (addSlowSpot, SIGNAL(triggered()), addingMapper, SLOT(map()));

    addingMapper->setMapping(addDeathSpot, DeathSpotObject);
    addingMapper->setMapping(addPlayer, PlayerObject);
    addingMapper->setMapping(addFloatingTile, FloatingTileStart);
    addingMapper->setMapping(addLight, LightObject);
    addingMapper->setMapping(addSpike, SpikeObject);
    addingMapper->setMapping(addSave, SaveObject);
    addingMapper->setMapping(addRope, RopeObject);
    addingMapper->setMapping(addBouncer, BouncerObject);
    addingMapper->setMapping(addPlatform, PlatformObject);
    addingMapper->setMapping(addDoor, DoorObject);

    addingMapper->setMapping(addTile, TileObject);
    addingMapper->setMapping(addMonster, MonsterObject);
    addingMapper->setMapping(addItem, ItemObject);
    addingMapper->setMapping(addNpcs, NpcObject);
    addingMapper->setMapping(addSlowSpot, SlowSpotObject);

    //monsters
    /*addSerg = new QAction(tr("Serg"), this);
    addCrabber = new QAction(tr("Crabber"), this);
    addPuff = new QAction(tr("Puff"), this);
    addJelly = new QAction(tr("Jelly"), this);
    addEdo = new QAction(tr("Edo"), this);
    addSkull = new QAction(tr("Skull"), this);
    addShroom = new QAction(tr("Shroom"), this);
    addWalker = new QAction(tr("Walker"), this);
    addXe = new QAction(tr("Xe"), this);

    connect (addSerg, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addSerg, 100);

    connect (addCrabber, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addCrabber, 101);

    connect (addPuff, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addPuff, 102);

    connect (addJelly, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addJelly, 103);

    connect (addEdo, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addEdo, 104);

    connect (addSkull, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addSkull, 105);

    connect (addShroom, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addShroom, 106);

    connect (addWalker, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addWalker, 107);

    connect (addXe, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addXe, 108);*/

    connect(addingMapper, SIGNAL(mapped(int)), this, SLOT(setAdding(int)));

    //tileset
     QSignalMapper *tileMapper = new QSignalMapper(this);

    tileset1 = new QAction(tr("tileset 1"), this);
    tileset2 = new QAction(tr("tileset 2"), this);
    tileset3 = new QAction(tr("tileset 3"), this);

    connect (tileset1, SIGNAL(triggered()), tileMapper, SLOT(map()));
    tileMapper->setMapping(tileset1, 1);

    connect (tileset2, SIGNAL(triggered()), tileMapper, SLOT(map()));
    tileMapper->setMapping(tileset2, 2);

    connect (tileset3, SIGNAL(triggered()), tileMapper, SLOT(map()));
    tileMapper->setMapping(tileset3, 3);

    connect(tileMapper, SIGNAL(mapped(int)), this, SLOT(setTileset(int)));
}

void MainWindow::editSettings()
{
    QWidget *levelParameters = new QWidget(this);
    levelParameters ->setWindowFlags(Qt::Dialog);
    levelParameters->resize(256, 250);
    levelParameters->setMaximumSize(256, 250);
    levelParameters->setMinimumSize(256, 250);
    levelParameters->setWindowTitle("level parameters");

   QSlider *levelWidth = new QSlider(Qt::Horizontal, levelParameters);
   levelWidth->resize(250, 32);
   levelWidth->setMinimum(160);
   levelWidth->setMaximum(160000);
   levelWidth->move(0, 15);
   levelWidth->setValue(MapEddi::levelWidth);

    QLabel *widthLabel = new QLabel(tr("Width"), levelParameters);

   connect(levelWidth, SIGNAL(valueChanged(int)), this, SLOT(setLevelWidth(int)));

   QSlider *levelHeight = new QSlider(Qt::Horizontal, levelParameters);
   levelHeight->resize(250, 32);
   levelHeight->setMinimum(160);
   levelHeight->setMaximum(160000);
   levelHeight->move(0, 45);
    levelHeight->setValue(MapEddi::levelHeight);

   QLabel *heightLabel = new QLabel(tr("Height"), levelParameters);
    heightLabel->move(0,40);

   connect(levelHeight, SIGNAL(valueChanged(int)), this, SLOT(setLevelHeight(int)));

    QSlider *background = new QSlider(Qt::Horizontal, levelParameters);
    background->resize(250, 32);
    background->setMinimum(0);
    background->setMaximum(3);
    background->move(0, 75);
     levelHeight->setValue(MapEddi::levelHeight);
    QLabel *backgroundLabel = new QLabel(tr("Background"), levelParameters);
    backgroundLabel->move(0,70);

    connect(background, SIGNAL(valueChanged(int)), this, SLOT(setBackground(int)));

    levelParameters->show();
}

void MainWindow::setLevelHeight(int height)
{
    MapEddi::levelHeight = height;

    worldView->resize(MapEddi::levelWidth, MapEddi::levelHeight);
    worldView->resizeGrid(MapEddi::levelWidth, MapEddi::levelHeight);
}

void MainWindow::setLevelWidth(int width)
{
    MapEddi::levelWidth = width;

    worldView->resize(MapEddi::levelWidth, MapEddi::levelHeight);
    worldView->resizeGrid(MapEddi::levelWidth, MapEddi::levelHeight);
}

void MainWindow::setBackground(int bg)
{
    MapEddi::background = bg;
}

//Creates drop-down menus.
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    layerMenu = menuBar()->addMenu(tr("&Layer"));
    tilesetMenu = menuBar()->addMenu(tr("&Tileset"));


    addMenu = menuBar()->addMenu(tr("&Add"));
    addMenu->addAction(addPlayer);
    addMenu->addAction(addFloatingTile);
    addMenu->addAction(addLight);
    addMenu->addAction(addSpike);
    addMenu->addAction(addSave);
    addMenu->addAction(addRope);
    addMenu->addAction(addBouncer);
    addMenu->addAction(addPlatform);
    addMenu->addAction(addDoor);
    addMenu->addAction(addDeathSpot);
    addMenu->addAction(addSlowSpot);

    addMenu->addAction(addTile);
    addMenu->addAction(addMonster);
    addMenu->addAction(addItem);
    addMenu->addAction(addNpcs);

   /* addMonsterMenu->addAction(addSerg);
    addMonsterMenu->addAction(addCrabber);
    addMonsterMenu->addAction(addPuff);
    addMonsterMenu->addAction(addJelly);
    addMonsterMenu->addAction(addEdo);
    addMonsterMenu->addAction(addSkull);
    addMonsterMenu->addAction(addShroom);
    addMonsterMenu->addAction(addWalker);
    addMonsterMenu->addAction(addXe);*/

    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(levelSettings);

    layerMenu->addAction(layer0);
    layerMenu->addAction(layer1);
    layerMenu->addAction(layer2);
    layerMenu->addAction(layer3);
    layerMenu->addAction(layer4);
    layerMenu->addAction(layer5);
    layerMenu->addAction(layer6);

    tilesetMenu->addAction(tileset1);
    tilesetMenu->addAction(tileset2);
    tilesetMenu->addAction(tileset3);
}

//Creates dock windows.
void MainWindow::createDockWindows()
{
    //top dock------------------------------------------------------------------------------

   QDockWidget *topDock = new QDockWidget(this);

    topDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    QGroupBox *topDockGroup = new QGroupBox(topDock);

    QHBoxLayout *topDockLayout = new QHBoxLayout;
    topDockGroup->setFlat(true);
    topDockGroup->setLayout(topDockLayout);

    QGroupBox *gridSizeGroup = new QGroupBox(tr("Grid Sizes"), topDockGroup);

    //solid checkbox added to top dock
    QCheckBox *solidCheckBox = new QCheckBox(tr("Solid"));
    topDockLayout->addWidget(solidCheckBox);

    topDockLayout->addWidget(gridSizeGroup, 0, Qt::AlignCenter);

    connect(solidCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setSolid()));

    //grid size group box
    QRadioButton *small = new QRadioButton(tr("8px"));
    QRadioButton *medium = new QRadioButton(tr("16px"));
    QRadioButton *large = new QRadioButton(tr("32px"));

    QHBoxLayout *radioLayout = new QHBoxLayout;

    radioLayout->addWidget(small);
    radioLayout->addWidget(medium);
    radioLayout->addWidget(large);

    QSignalMapper *signalMapper = new QSignalMapper(this);

    connect(small, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(medium, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(large, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper->setMapping(small, 8);
    signalMapper->setMapping(medium, 16);
    signalMapper->setMapping(large, 32);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setGridSize(int)));

    radioLayout->addStretch(1);

    gridSizeGroup->setFlat(true);
    gridSizeGroup->setLayout(radioLayout);

    //currently selected group box
    currentLayer = new QLabel(tr("Current Layer: %1").arg(MapEddi::selectedLayer));

    topDockLayout->addWidget(currentLayer, 0, Qt::AlignRight);

    currentObject = new QLabel;

    MapEddi::currentObjectImage = ImageContainer::tileImages.at(0);

    currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));

    topDockLayout->addWidget(currentObject, 0, Qt::AlignRight);

    topDock->setWidget(topDockGroup);

    addDockWidget(Qt::TopDockWidgetArea, topDock);

    //tile dock-----------------------------------------------------------------------------
    tileDock = new QDockWidget(tr("Tile Dock"), this);

    TileDockView *tileDockView = new TileDockView(this);

    tileDockView->initTiles();

    tileDock->setWidget(tileDockView);
    tileDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    tileDock->setMinimumWidth(128);

    addDockWidget(Qt::LeftDockWidgetArea, tileDock);

    //monster dock--------------------------------------------------------------------------

    monsterDock = new QDockWidget(tr("Monster Dock"), this);


    TileDockView *monsterDockView = new TileDockView(this);
    monsterDockView->initMonsters();
    monsterDock->setWidget(monsterDockView);
    monsterDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    monsterDock->setMinimumWidth(128);

    addDockWidget(Qt::LeftDockWidgetArea, monsterDock);

    monsterDock->setHidden(true);


    //item dock-----------------------------------------------------------------------------

    itemDock = new QDockWidget(tr("Item Dock"), this);

    TileDockView *itemDockView = new TileDockView(this);
    itemDockView->initItems();
    itemDock->setWidget(itemDockView);
    itemDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    itemDock ->setMinimumWidth(128);

    addDockWidget(Qt::LeftDockWidgetArea, itemDock);

    itemDock->setHidden(true);


    //npcs dock-----------------------------------------------------------------------------

    npcsDock = new QDockWidget(tr("Npc Dock"), this);

    TileDockView *npcsDockView = new TileDockView(this);
    npcsDockView->initNpcs();
    npcsDock->setWidget(npcsDockView);

    npcsDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    npcsDock ->setMinimumWidth(128);

    addDockWidget(Qt::LeftDockWidgetArea, npcsDock);

}

//Determines whether or not a tile is solid.
void MainWindow::setSolid()
{
    MapEddi::solidSelected = !MapEddi::solidSelected;
}

//Sets the grid size.
void MainWindow::setGridSize(int gridSize)
{
    worldView->setGridSize(gridSize);
}

//Sets current layer.
void MainWindow::selectLayer(int layer)
{
    MapEddi::selectedLayer = layer;

    currentLayer->setText(tr("Current Layer: %1").arg(MapEddi::selectedLayer));
}

//Chooses the currently selected tile to display in the UI.
void MainWindow::selectTile()
{
    MapEddi::currentObjectImage = ImageContainer::tileImages.at(MapEddi::selectedIndex);

    currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));
}

void MainWindow::setAdding(int newType)
{
    MapEddi::currentlyAdding = (ObjectType)newType;

    if (MapEddi::currentlyAdding == PlayerObject)
    {
        MapEddi::currentObjectImage = ImageContainer::playerImage;

        currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));
    }
    else if (MapEddi::currentlyAdding == TileObject)
    {
        tileDock->setHidden(false);
        monsterDock->setHidden(true);
        itemDock->setHidden(true);
        npcsDock->setHidden(true);

        MapEddi::currentObjectImage = ImageContainer::tileImages.at(MapEddi::selectedIndex);

        currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));
    }
    else if (MapEddi::currentlyAdding == MonsterObject)
    {
        tileDock->setHidden(true);
        itemDock->setHidden(true);
        npcsDock->setHidden(true);
        monsterDock->setHidden(false);
    }
    else if (MapEddi::currentlyAdding == ItemObject)
    {
        itemDock->setHidden(false);
        monsterDock->setHidden(true);
        tileDock->setHidden(true);
        npcsDock->setHidden(true);
    }
    else if (MapEddi::currentlyAdding == NpcObject)
    {
        npcsDock->setHidden(false);
        monsterDock->setHidden(true);
        tileDock->setHidden(true);
        itemDock->setHidden(true);
    }
    else if (MapEddi::currentlyAdding == SpikeObject)
    {
        MapEddi::currentObjectImage = ImageContainer::spikeImage;
        currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));
        MapEddi::selectedIndex = 0;
    }
    else if (MapEddi::currentlyAdding == SaveObject)
    {
        MapEddi::currentObjectImage = ImageContainer::saveImage;
        currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));
        MapEddi::selectedIndex = 0;
    }
    else if (MapEddi::currentlyAdding == BouncerObject)
    {
        MapEddi::currentObjectImage = ImageContainer::bouncerImage;
        currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));
        MapEddi::selectedIndex = 0;
    }
    else if (MapEddi::currentlyAdding == PlatformObject)
    {
        MapEddi::currentObjectImage = ImageContainer::platformImage;
        currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));
    }
    else if (MapEddi::currentlyAdding == DoorObject)
    {
        MapEddi::selectedIndex = 0;
    }
    else if (MapEddi::currentlyAdding == LightObject)
    {
        MapEddi::currentObjectImage = ImageContainer::lightImage;
        currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));
        MapEddi::selectedIndex = 0;
    }
}

void MainWindow::setTileset(int newTileset)
{
    qDebug() << "Loading tile set " << newTileset << "\n";
    tileset = newTileset;
    ImageContainer::imageContainerTileset = tileset;
    ImageContainer::loadTextures();
    worldView->update();
}
