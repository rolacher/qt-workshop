TEMPLATE = lib

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += staticlib

INCLUDEPATH += include

SOURCES += \
    source/application.cpp \
    source/controller.cpp \
    source/communication.cpp \
    source/udp_socket.cpp \
    source/mainwindow.cpp \
    source/usermanager.cpp \
    source/usersmodel.cpp \
    source/useritem.cpp \
    source/editdialog.cpp

HEADERS += \
    include/messenger/application.h \
    include/messenger/controller.h \
    include/messenger/communication.h \
    include/messenger/iudp_socket.h \
    include/messenger/udp_socket.h \
    include/messenger/mainwindow.h \
    include/messenger/usermanager.h \
    include/messenger/usersmodel.h \
    include/messenger/useritem.h \
    include/messenger/editdialog.h

OTHER_FILES +=

RESOURCES +=

QMAKE_CXXFLAGS_DEBUG += -fprofile-arcs -ftest-coverage

include(../common.pri)

FORMS += \
    mainwindow.ui

