#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T10:55:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BoxGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    groundrect.cpp \
    common.cpp \
    circleobject.cpp \
    lightable.cpp \
    shadowable.cpp \
    scene.cpp

HEADERS  += mainwindow.h \
    groundrect.h \
    common.h \
    circleobject.h \
    lightable.h \
    shadowable.h \
    scene.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/./ -lbox2dLib

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./box2dLib.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/./libbox2dLib.a
