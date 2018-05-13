#include "mapeddi.h"
#define DEFAULT_WIDTH (32 * 200)
#define DEFAULT_HEIGHT (32 * 100)

namespace MapEddi
{
    int levelWidth = DEFAULT_WIDTH;
    int levelHeight = DEFAULT_HEIGHT;
    int selectedIndex;
    int selectedLayer;
    bool solidSelected;
    QImage *currentObjectImage;
    ObjectType currentlyAdding = TileObject;
    QString currentFile = QString::fromStdString("newlevel.lvl");
}
