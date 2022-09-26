QT += core gui widgets
CONFIG += qt warn_on ltcg

DISTFILES += assets/
FORMS += gui/main.ui
SOURCES += src/main.cpp
RC_ICONS += assets/logo.ico

QMAKE_CFLAGS += -s -std=c17
QMAKE_CXXFLAGS += -s -std=c++20
