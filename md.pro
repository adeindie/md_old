#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T15:54:41
#
#-------------------------------------------------

QT       += core gui
QT += webkit webkitwidgets
CONFIG += c++11 warn_off

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = md
TEMPLATE = app

INCLUDEPATH += ./third_party/sundown/src
INCLUDEPATH += ./third_party/sundown/html

LIBS += -L$${PWD}/Libs/ -lsundown

SOURCES += main.cpp\
    mainwindow.cpp \
    TextEditer.cpp \
    WebView.cpp

HEADERS  += mainwindow.h \
    TextEditer.h \
    WebView.h

FORMS    += mainwindow.ui
