#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H
#include <vector>
#include <QImage>

//holds images for the tile map
namespace ImageContainer
{
    void loadImages();

    extern std::vector<QImage*> tileImages;

    extern QImage* playerImage;

    extern std::vector<QImage*> monsterImages;
}

#endif // IMAGECONTAINER_H
