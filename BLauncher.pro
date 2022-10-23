QT += core gui widgets
CONFIG += qt warn_on ltcg c++20 strict_c++
#CONFIG += static release
CONFIG -= exe_embed_manifest

FORMS += gui/main.ui
DISTFILES += assets/
RC_FILE = BLauncher.rc
SOURCES += src/main.cpp

#QMAKE_CXXFLAGS += /std:c++20
#QMAKE_CXXFLAGS += -std=c++20
