#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T15:54:41
#
#-------------------------------------------------

QT       += core gui
QT += webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = md
TEMPLATE = app

INCLUDEPATH += ./src
INCLUDEPATH += ./html

SOURCES += main.cpp\
        mainwindow.cpp \
    src/autolink.c \
    src/buffer.c \
    src/markdown.c \
    src/stack.c \
    html/houdini_href_e.c \
    html/houdini_html_e.c \
    html/html_smartypants.c \
    html/html.c \
    TextEditer.cpp

HEADERS  += mainwindow.h \
    src/autolink.h \
    src/buffer.h \
    src/html_blocks.h \
    src/markdown.h \
    src/stack.h \
    html/houdini.h \
    html/html.h \
    TextEditer.h

FORMS    += mainwindow.ui
