#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T13:15:41
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = solar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    planet.cpp \
    myscene.cpp \
    myview.cpp \
    planetedit.cpp \
    basicsettings.cpp \
    basicsettingsdata.cpp \
    mychart.cpp \
    chartpanel.cpp

HEADERS  += mainwindow.h \
    planet.h \
    myscene.h \
    myview.h \
    planetedit.h \
    basicsettings.h \
    basicsettingsdata.h \
    mychart.h \
    chartpanel.h

FORMS    += mainwindow.ui \
    planetedit.ui \
    basicsettings.ui\
    mychart.ui \
    chartpanel.ui

RESOURCES += \
    icon.qrc
