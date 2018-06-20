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
    int tileNumber = 60;
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


        playerImage = new QImage(QString::fromStdString("3.png"));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/Serg/1.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/Serg/1r.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/crab1.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/crab1.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/puff1.png")));
        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/puff1.png")));

        monsterImages.push_back(new QImage(QString::fromStdString("Monsters/jelly1.png")));
         monsterImages.push_back(new QImage(QString::fromStdString("Monsters/jelly1.png")));

         monsterImages.push_back(new QImage(QString::fromStdString("Monsters/edoleft.png")));
          monsterImages.push_back(new QImage(QString::fromStdString("Monsters/edoright.png")));

          monsterImages.push_back(new QImage(QString::fromStdString("Monsters/skullleft.png")));
           monsterImages.push_back(new QImage(QString::fromStdString("Monsters/skulllright.png")));

           monsterImages.push_back(new QImage(QString::fromStdString("Monsters/shroom.png")));
           monsterImages.push_back(new QImage(QString::fromStdString("Monsters/shroom.png")));

           monsterImages.push_back(new QImage(QString::fromStdString("Monsters/walker1.png")));
           monsterImages.push_back(new QImage(QString::fromStdString("Monsters/walker1.png")));

           monsterImages.push_back(new QImage(QString::fromStdString("Monsters/xeleft.png")));
           monsterImages.push_back(new QImage(QString::fromStdString("Monsters/xeright.png")));

         lightImage = new QImage(QString::fromStdString("light.png"));
         spikeImage = new QImage(QString::fromStdString("spike.png"));
         bouncerImage = new QImage(QString::fromStdString("images/bouncer.png"));
    }
}

