#include "save.h"
#include "imagecontainer.h"

Save::Save()
{
     image = ImageContainer::saveImage;
}

Save::Save(int x, int y, WorldView *worldView) : GameObject(x, y, ImageContainer::saveImage->width(), ImageContainer::saveImage->height(),true, worldView)
{
      image = ImageContainer::saveImage;
}

void Save::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    painter->drawImage(boundingRect(), *(ImageContainer::saveImage), QRectF(0.0, 0.0, getW(), getH()));
    /*QColor brushColour(200, 30, 90, 200);
    painter->setBrush(QBrush(brushColour));
    painter->drawRect(boundingRect());*/

}


QRectF Save::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}
