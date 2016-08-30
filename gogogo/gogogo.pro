#-------------------------------------------------
#
# Project created by QtCreator 2016-07-24T12:37:23
#
# my first qt programn
#-------------------------------------------------

QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gogogo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamecontroller.cpp \
    hero.cpp \
    punchitem.cpp \
    blockitem.cpp \
    enemy.cpp \
    enemy_type_1.cpp \
    trap.cpp \
    hurt.cpp \
    jumpitem.cpp \
    map.cpp \
    trap_1.cpp \
    mybutton.cpp \
    startmenu.cpp \
    goondialog.cpp \
    itemdialog.cpp \
    itemlabel.cpp \
    stuffitem.cpp \
    statuslabel.cpp \
    fire.cpp \
    trap_2.cpp \
    trap_3.cpp \
    enemy_type_2.cpp \
    enemy_type_3.cpp \
    boss.cpp \
    omg.cpp

HEADERS  += mainwindow.h \
    constants.h \
    gamecontroller.h \
    hero.h \
    punchitem.h \
    blockitem.h \
    enemy.h \
    enemy_type_1.h \
    trap.h \
    hurt.h \
    jumpitem.h \
    map.h \
    trap_1.h \
    mybutton.h \
    startmenu.h \
    goondialog.h \
    itemdialog.h \
    itemlabel.h \
    stuffitem.h \
    statuslabel.h \
    fire.h \
    trap_2.h \
    trap_3.h \
    enemy_type_2.h \
    enemy_type_3.h \
    boss.h \
    omg.h

FORMS    +=

RESOURCES += \
    source.qrc
