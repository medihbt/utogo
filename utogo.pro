# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

TARGET = utogo-bin

QT = core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS = \
   $$PWD/src/include/err.h \
   $$PWD/src/include/multilist.h \
   $$PWD/src/include/utask_io.h \
   $$PWD/src/include/utask_struct.h \
   $$PWD/src/include/utask_timer.h \
   $$PWD/src/libunilist/unilist.h \
   $$PWD/src/ui/mainwindow.h \
   $$PWD/src/ui/singletaskviewer.h \
   src/ui/qt_gui.h

SOURCES = \
   $$PWD/src/os/timer.c \
   $$PWD/src/scene/multilist.c \
   $$PWD/src/udata/utask_io.c \
   $$PWD/src/udata/utask_struct.c \
   $$PWD/src/libunilist/ulist_read.c \
   $$PWD/src/ui/qt_gui_main.cpp \
   $$PWD/src/ui/mainwindow.cpp \
   $$PWD/src/ui/singletaskviewer.cpp \
   $$PWD/src/main.c

FORMS = \
   $$PWD/src/ui/mainwindow.ui \
   $$PWD/src/ui/singletaskviewer.ui

RESOURCES = \
   $$PWD/src/ui/icons.qrc

INCLUDEPATH = \
    $$PWD/src/include \
    $$PWD/src/ui

#DEFINES = 

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

