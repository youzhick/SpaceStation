#-------------------------------------------------
#
# Project created by QtCreator 2019-02-21T14:10:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceStation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    WorldDrawerWidget.cpp \
    World.cpp \
    YTools/Geometry/YLine.cpp \
    YTools/Geometry/YPoint.cpp \
    YTools/Geometry/YSegment.cpp \
    YTools/Geometry/YTransform.cpp \
    YTools/Geometry/YVector.cpp \
    LifeCycle.cpp

HEADERS += \
        MainWindow.h \
    WorldDrawerWidget.h \
    World.h \
    YTools/YtGeometry.h \
    YTools/YTools.h \
    YTools/Utils/YConstants.h \
    YTools/Geometry/YLine.h \
    YTools/Geometry/YPoint.h \
    YTools/Geometry/YSegment.h \
    YTools/Geometry/YTransform.h \
    YTools/Geometry/YVector.h \
    LifeCycle.h

FORMS += \
        MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
