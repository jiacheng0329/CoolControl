#-------------------------------------------------
#
# Project created by QtCreator 2015-06-13T23:45:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = CoolControl
TEMPLATE = app
include(../Control/control.pri)

SOURCES += \
    mdiareawidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mdiareawidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resource.qrc

win32{
    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
}
