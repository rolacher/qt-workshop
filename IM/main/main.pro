QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = messenger

TEMPLATE = app

SOURCES +=  \
    main.cpp

include(../common.pri)
include(../messenger/messenger.pri)

