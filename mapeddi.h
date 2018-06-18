#ifndef MAPEDDI_H
#define MAPEDDI_H
class QImage;
#include "gameobject.h"
#include <QString>

enum ObjectType
{
    PlayerObject,
    TileObject,
    MonsterObject,
    SceneryObject,
    ItemObject,
    FloatingTileStart,
    FloatingTileEnd,
    SpikeObject,
    LightObject,
    BouncerObject,
    DoorObject,
    NUM_OBJECT_TYPES
};

namespace MapEddi
{
    extern int selectedIndex;
    extern int selectedLayer;
    extern bool solidSelected;
    extern QImage *currentObjectImage;
    extern ObjectType currentlyAdding;
    extern QString currentFile;
    extern int levelWidth;
    extern int levelHeight;
    extern int mouse_x;
    extern int mouse_y;
}

#endif // MAPEDDI_H
