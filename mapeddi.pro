#-------------------------------------------------
#
# Project created by QtCreator 2018-04-27T12:25:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mapeddi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    levelscene.cpp \
    worldview.cpp \
    worldgrid.cpp \
    imagecontainer.cpp \
    tiledockview.cpp \
    mapeddi.cpp \
    gameobject.cpp \
    player.cpp \
    floatingtile.cpp \
    light.cpp \
    monsters.cpp

HEADERS  += mainwindow.h \
    tile.h \
    levelscene.h \
    worldview.h \
    utils.h \
    worldgrid.h \
    imagecontainer.h \
    tiledockview.h \
    mapeddi.h \
    gameobject.h \
    player.h \
    floatingtile.h \
    light.h \
    monsters.h

FORMS    += mainwindow.ui