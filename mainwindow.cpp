#include <QDebug>
#include <QFileDialog>
#include <QDockWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSignalMapper>
#include "tiledockview.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worldview.h"
#include "mapeddi.h"
#include "gameobject.h"
#include "imagecontainer.h"
#include "floatingtile.h"
#include "tile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files(*.lvl"));

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
                    input += 5;

                }
                else if (currentType == 1)
                {
                    worldView->setPlayerX(input[1]);
                    worldView->setPlayerY(input[2]);
                    input += 3;
                }
                else if (currentType == 2)
                {
                    worldView->addTile(input[1], input[2], input[3], input[4]);
                    input +=5;
                }
                else if (currentType == 3)
                {
                    worldView->addFloatingTile(input[1], input[2], input[3], input[4], input[5]);

                    input +=6;
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

        //save level header
        out << 0;
        //background 0
        out << 0;
        //tile set 1
        out << 0;
        //level width 2
        out << MapEddi::levelWidth;
        //level height 3
        out << MapEddi::levelHeight;

        out << 1;
        //save player X 4
        out << worldView->getPlayerX();
        //save player Y 5
        out <<worldView->getPlayerY();

        //save tiles
        for (auto tile = worldView->tile_list.begin(); tile != worldView->tile_list.end(); ++tile)
        {
            out << 2;
            out << (*tile)->getX();
            out << (*tile)->getY();
            out << (*tile)->getTileIndex();
            out << (int)(*tile)->isSolid();
        }

        for (auto tile = worldView->floating_tile_list.begin(); tile != worldView->floating_tile_list.end(); ++tile)
        {
            out << 3;
            out << (*tile)->getX();
            out << (*tile)->getY();
            out << (*tile)->getIndex();
            out << (*tile)->getFloatHeight();
            out << (*tile)->getMaxThrust();
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

    QSignalMapper *addingMapper = new QSignalMapper(this);

    connect(addPlayer, SIGNAL(triggered()), addingMapper, SLOT(map()));
    connect(addFloatingTile, SIGNAL(triggered()), addingMapper, SLOT(map()));
    addingMapper->setMapping(addPlayer, PlayerObject);
    addingMapper->setMapping(addFloatingTile, FloatingTileStart);
    connect(addingMapper, SIGNAL(mapped(int)), this, SLOT(setAdding(int)));

}

//Creates drop-down menus.
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    layerMenu = menuBar()->addMenu(tr("&Layer"));
    addMenu = menuBar()->addMenu(tr("&Add"));
    addMenu->addAction(addPlayer);
    addMenu->addAction(addFloatingTile);
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    layerMenu->addAction(layer0);
    layerMenu->addAction(layer1);
    layerMenu->addAction(layer2);
    layerMenu->addAction(layer3);
    layerMenu->addAction(layer4);
    layerMenu->addAction(layer5);
    layerMenu->addAction(layer6);
}

//Creates dock windows.
void MainWindow::createDockWindows()
{
    //top dock------------------------------------------------------------------------------
    QDockWidget *dockDock = new QDockWidget(this);

    dockDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    QGroupBox *topDockGroup = new QGroupBox(dockDock);

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

    dockDock->setWidget(topDockGroup);

    addDockWidget(Qt::TopDockWidgetArea, dockDock);

    //left dock-----------------------------------------------------------------------------
    dockDock = new QDockWidget(tr("Tile Dock"), this);

    TileDockView *tileDockView = new TileDockView(this);

    dockDock->setWidget(tileDockView);
    dockDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dockDock->setMinimumWidth(128);

    addDockWidget(Qt::LeftDockWidgetArea, dockDock);
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
        MapEddi::currentObjectImage = ImageContainer::tileImages.at(MapEddi::selectedIndex);

        currentObject->setPixmap(QPixmap::fromImage(*MapEddi::currentObjectImage, Qt::AutoColor));
    }
}
