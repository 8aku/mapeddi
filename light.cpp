#include "light.h"
#include "gameobject.h"
#include "worldview.h"
#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QWindow>
#include <QGraphicsSceneMouseEvent>
#include <QHBoxLayout>
#include <QToolTip>
#define DEFAULT_RADIUS 64

Light::Light()
{
    qDebug() << "Calling null";
}

Light::Light(int x, int y, WorldView *worldView) : Light(x, y, DEFAULT_RADIUS, 255, 255, 255, 200, worldView)
{

}

Light::Light (int x, int y, int radius, int r, int g, int b, int a, WorldView *worldView) : GameObject(x, y, radius, radius, true, worldView)
{
    this->radius = radius;
    colour.r = r;
    colour.g = g;
    colour.b = b;
    colour.a = a;
}

void Light::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor brushColour(colour.r, colour.g, colour.b, colour.a);
    painter->setBrush(QBrush(brushColour));
    painter->drawEllipse(boundingRect());
}

QRectF Light::boundingRect() const
{
    return QRectF(getX() - (radius / 2), getY() - (radius / 2), radius, radius);
}

void Light::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ShiftModifier)
    {
        lightParameters = new QWidget(worldView);
        lightParameters->setWindowFlags(Qt::Dialog);
        lightParameters->resize(256, 250);
        lightParameters->setMaximumSize(256, 250);
        lightParameters->setMinimumSize(256, 250);
        lightParameters->setWindowTitle("Light Parameters");

       QSlider *radiusSlider = new QSlider(Qt::Horizontal, lightParameters);
       radiusSlider->resize(250, 32);
       radiusSlider->setMinimum(8);
       radiusSlider->setMaximum(512);
       radiusSlider->move(0, 15);

       QLabel *radiusLabel = new QLabel(tr("RADIUS"), lightParameters);

       QLabel *redLabel = new QLabel(tr("RED"), lightParameters);
       redLabel->move(0, 40);

       QLabel *greenLabel = new QLabel(tr("GREEN"), lightParameters);
       greenLabel->move(0, 95);

       QLabel *blueLabel = new QLabel(tr("BLUE"), lightParameters);
       blueLabel->move(0, 145);

       QLabel *alphaLabel = new QLabel(tr("ALPHA"), lightParameters);
       alphaLabel->move(0, 195);


       QSlider *redSlider = new QSlider(Qt::Horizontal, lightParameters);
       redSlider->resize(250, 32);
       redSlider->setMaximum(255);
       redSlider->setMinimum(0);
       redSlider->setMinimum(0);
       redSlider->move(0, 60);

       QSlider *greenSlider = new QSlider(Qt::Horizontal, lightParameters);
       greenSlider->resize(250, 32);
       greenSlider->setMaximum(255);
       greenSlider->setMinimum(0);
       greenSlider->setMinimum(0);
       greenSlider->move(0, 110);

       QSlider *blueSlider = new QSlider(Qt::Horizontal, lightParameters);
       blueSlider->resize(250, 32);
       blueSlider->setMaximum(255);
       blueSlider->setMinimum(0);
       blueSlider->setMinimum(0);
       blueSlider->move(0, 160);

       QSlider *alphaSlider = new QSlider(Qt::Horizontal, lightParameters);
       alphaSlider->resize(250, 32);
       alphaSlider->setMaximum(255);
       alphaSlider->setMinimum(0);
       alphaSlider->setMinimum(0);
       alphaSlider->move(0, 210);

       connect(radiusSlider, SIGNAL(valueChanged(int)), this, SLOT(setRadius(int)));

       connect(redSlider, SIGNAL(valueChanged(int)), this, SLOT(setRed(int)));
       connect(greenSlider, SIGNAL(valueChanged(int)), this, SLOT(setGreen(int)));
       connect(blueSlider, SIGNAL(valueChanged(int)), this, SLOT(setBlue(int)));
       connect(alphaSlider, SIGNAL(valueChanged(int)), this, SLOT(setAlpha(int)));

        lightParameters->show();
    }

    GameObject::mousePressEvent(event);
}

void Light::setRadius(int radius)
{
    this->radius = radius;

    QPoint point(0, 0);
    QToolTip::showText(lightParameters->mapToGlobal(point), QString::number(radius), lightParameters);

    worldView->refreshView();

    qDebug() << radius << "\n";
}

void Light::setRed (int value)
{
    colour.r = value;

    QPoint point(0, 0);
    QToolTip::showText(lightParameters->mapToGlobal(point), QString::number(colour.r), lightParameters);

    worldView->refreshView();
}

void Light::setGreen (int value)
{
    colour.g = value;

    QPoint point(0, 0);
    QToolTip::showText(lightParameters->mapToGlobal(point), QString::number(colour.g), lightParameters);

    worldView->refreshView();
}

void Light::setBlue(int value)
{
    colour.b = value;

    QPoint point(0, 0);
    QToolTip::showText(lightParameters->mapToGlobal(point), QString::number(colour.b), lightParameters);

    worldView->refreshView();
}

void Light::setAlpha (int value)
{
    colour.a = value;

    QPoint point(0, 0);
    QToolTip::showText(lightParameters->mapToGlobal(point), QString::number(colour.a), lightParameters);

    worldView->refreshView();
}

int Light::getRadius()
{
    return radius;
}

int Light::getRed()
{
    return colour.r;
}

int Light::getGreen()
{
    return colour.g;
}

int Light::getBlue()
{
    return colour.b;
}

int Light::getAlpha()
{
    return colour.a;
}
