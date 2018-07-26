#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H
#include <vector>
#include <QImage>
#include "mainwindow.h"

//holds images for the tile map
namespace ImageContainer
{
    void loadTextures();
    void loadImages();

    extern std::vector<QImage*> tileImages;

    extern QImage* playerImage;

    extern QImage* spikeImage;
    extern QImage* bouncerImage;
    extern QImage* lightImage;
    extern QImage* saveImage;
    extern  QImage* platformImage;
    extern std::vector<QImage*>npcImages;
    extern std::vector<QImage*> monsterImages;
    extern std::vector<QImage*>itemImages;
    extern std::ostringstream path;
    extern int imageContainerTileset;
}

#endif // IMAGECONTAINER_H
