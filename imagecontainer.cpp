#include "imagecontainer.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <QString>
#define NUMBER_OF_TILES 45

namespace ImageContainer
{
    std::vector<QImage*> tileImages;

    QImage* playerImage;

    //Loads images from a file.
    void loadImages()
    {
        std::ostringstream path;

        for (int i = 0; i < NUMBER_OF_TILES; i++)
        {
            path.str("");
            path.clear();

            path << "tile_test/" << i + 1 << ".png";

            tileImages.push_back(new QImage(QString::fromStdString(path.str())));
        }

        playerImage = new QImage(QString::fromStdString("3.png"));
    }
}

