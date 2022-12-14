# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = utogo

QT = core gui widgets

HEADERS = \
   $$PWD/src/include/err.h \
   $$PWD/src/include/multilist.h \
   $$PWD/src/include/utask_io.h \
   $$PWD/src/include/utask_struct.h \
   $$PWD/src/include/utask_timer.h \
   $$PWD/src/ui/mainwindow.h \
   $$PWD/src/ui/singletaskviewer.h \
   $$PWD/src/ui/ui_mainwindow.h \
   $$PWD/src/ui/ui_singletaskviewer.h

SOURCES = \
   $$PWD/src/os/timer.c \
   $$PWD/src/scene/multilist.c \
   $$PWD/src/udata/ulist_parse.c \
   $$PWD/src/udata/utask_io.c \
   $$PWD/src/udata/utask_struct.c \
   $$PWD/src/ui/asset/icons/icon1.png \
   $$PWD/src/ui/icons.qrc \
   $$PWD/src/ui/main.cpp \
   $$PWD/src/ui/mainwindow.cpp \
   $$PWD/src/ui/mainwindow.ui \
   $$PWD/src/ui/singletaskviewer.cpp \
   $$PWD/src/ui/singletaskviewer.ui \
   $$PWD/src/main.c

INCLUDEPATH = \
    $$PWD/src/include \
    $$PWD/src/ui

#DEFINES = 

