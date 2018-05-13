#include "player.h"
#include "imagecontainer.h"
#include <QPainter>
#include <QBrush>

Player::Player() : GameObject(0, 0, 32, 64, true, NULL)
{
    image = ImageContainer::playerImage;
}

//Draws the player.
void Player:: paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    painter->setBrush(brush);

    painter->drawImage(boundingRect(), *image, QRectF(0.0, 0.0, getW(), getH()));

}

//Pure virtual method needed for implementation (QT specific).
QRectF Player::boundingRect() const
{
    return QRectF(getX(), getY(), getW(), getH());
}
