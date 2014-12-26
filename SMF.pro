#-------------------------------------------------
#
# Project created by QtCreator 2014-12-25T22:11:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_FILE = app.rc

win32 {
CONFIG += embed_manifest_exe
QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
}

TARGET = SMF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
