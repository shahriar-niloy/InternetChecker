#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T19:23:02
#
#-------------------------------------------------

QT       += core gui widgets
QT += network multimedia winextras multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ITCheck
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    toast.cpp

HEADERS  += widget.h \
    toast.h

FORMS    += widget.ui \
    toast.ui

DISTFILES +=

RESOURCES += \
    sounds.qrc

RC_FILE = icon.rc
