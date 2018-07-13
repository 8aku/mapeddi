#include "imagecontainer.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <QDebug>
#include <QString>
#include "mainwindow.h"

namespace ImageContainer
{
    std::vector<QImage*> tileImages;

    std::vector<QImage*> monsterImages;

    QImage* playerImage;
    QImage* spikeImage;
    QImage* lightImage;
    QImage* bouncerImage;
    std::ostringstream path;
    int tileNumber = 75;
    int imageContainerTileset = 1;

    //load textures
    void loadTextures()
    {
        for (auto img : tileImages)
        {
            delete img;
        }

        tileImages.clear();

        path.str("");
        path.clear();

        for (int i = 0; i < tileNumber; i++)
        {
            path << "tile_test" << ImageContainer::imageContainerTileset << "/" << i+1 << ".png";
            tileImages.push_back(new QImage(QString::fromStdString(path.str())));
            path.clear();
            path.str("");
        }
    }

    //Loads images from a file.
    void loadImages()
    {
        loadTextures();


        playerImage = new QImage(QString::fromStdString("player1.png"));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/1.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/1r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/2.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/2r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/3.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/3r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/4.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/4r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/5.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/5r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/6.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/6r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/7.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/7r.png")));

         lightImage = new QImage(QString::fromStdString("light.png"));
         spikeImage = new QImage(QString::fromStdString("spike.png"));
         bouncerImage = new QImage(QString::fromStdString("images/bouncer.png"));
    }
}

