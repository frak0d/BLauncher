QT += core gui widgets
CONFIG += qt warn_on ltcg

FORMS += gui/main.ui
DISTFILES += assets/
RC_FILE = BLauncher.rc
SOURCES += src/main.cpp

QMAKE_CXXFLAGS += /std:c++20 /O2
