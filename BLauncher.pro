QT += core gui widgets
CONFIG += qt warn_on ltcg c++20 strict_c++
#CONFIG += static release

FORMS += gui/main.ui
DISTFILES += assets/
RC_FILE = BLauncher.rc
SOURCES += src/main.cpp
