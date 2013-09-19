
QT += qml quick network

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

LIBS += -lmessenger

win32 {
    CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../messenger/release/
    CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../messenger/debug/

    CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../messenger/release/messenger.lib
    CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../messenger/debug/messenger.lib
}

unix {
    LIBS += -L$$OUT_PWD/../messenger/
    PRE_TARGETDEPS += $$OUT_PWD/../messenger/libmessenger.a

    QMAKE_LFLAGS_DEBUG += -fprofile-arcs
}

HEADERS +=

SOURCES +=

