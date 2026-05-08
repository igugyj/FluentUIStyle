CONFIG += c++17
QT += core gui widgets svg

win32-msvc {
    QMAKE_CXXFLAGS += /wd4273
}

DESTDIR_BIN = $$OUT_PWD/../bin
DESTDIR_LIB = $$OUT_PWD/../lib

isEmpty(PREFIX) {
    PREFIX = $$PWD/install
}
