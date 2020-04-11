#-------------------------------------------------
#
# Project created by QtCreator 2020-03-10T20:39:36
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

OBJECTS_DIR  = tmp
MOC_DIR      = tmp

INCLUDEPATH +=/usr/include/phonon
DEPENDPATH += /usr/include/phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pan_man
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
        big_score_ball.cpp \
        const_data.cpp \
        game_map.cpp \
        game_map_door.cpp \
        game_mes.cpp \
        game_text_option.cpp \
        game_view.cpp \
        main.cpp \
        game_widget.cpp \
        main_ball.cpp \
        monster.cpp \
        small_score_ball.cpp

HEADERS += \
        big_score_ball.h \
        const_data.h \
        game_map.h \
        game_map_door.h \
        game_mes.h \
        game_text_option.h \
        game_view.h \
        game_widget.h \
        main_ball.h \
        monster.h \
        small_score_ball.h

FORMS += \
        game_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
