TEMPLATE = app

QT += testlib
QT -= gui

CONFIG += testcase console
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    controller_test.cpp \
    communication_test.cpp \
    mocks/qudpsocket_mock.cpp \
    usermanager_test.cpp

HEADERS += \
    controller_test.h \
    communication_test.h \
    mocks/qudpsocket_mock.h \
    usermanager_test.h

include(../common.pri)
include(../messenger/messenger.pri)

