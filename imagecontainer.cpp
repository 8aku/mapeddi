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

    std::vector<QImage*>itemImages;

    std::vector<QImage*>npcImages;

    QImage* playerImage;
    QImage* spikeImage;
    QImage* lightImage;
    QImage* bouncerImage;
    QImage* saveImage;
    QImage* platformImage;
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
            path << "images/tiles" << ImageContainer::imageContainerTileset << "/" << i+1 << ".png";
            tileImages.push_back(new QImage(QString::fromStdString(path.str())));
            path.clear();
            path.str("");
        }
    }

    //Loads images from a file.
    void loadImages()
    {
        loadTextures();


        playerImage = new QImage(QString::fromStdString("images/player1.png"));

        itemImages.push_back(new QImage(QString::fromStdString("images/Items/1.png")));
        itemImages.push_back(new QImage(QString::fromStdString("images/Items/2.png")));
        itemImages.push_back(new QImage(QString::fromStdString("images/Items/3.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/1.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/1r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/2.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/2r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/3.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/3r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/4.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/4r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/5.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/5r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/6.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/6r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/7.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/7r.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("images/Monsters/8.png")));

        npcImages.push_back(new QImage(QString::fromStdString("images/npcs/1.png")));

        platformImage = new QImage(QString::fromStdString("images/platforms/1.png"));

        lightImage = new QImage(QString::fromStdString("images/light.png"));
         spikeImage = new QImage(QString::fromStdString("images/spike.png"));
         bouncerImage = new QImage(QString::fromStdString("images/images/bouncer.png"));
         saveImage = new QImage(QString::fromStdString("images/save.png"));
    }
}

