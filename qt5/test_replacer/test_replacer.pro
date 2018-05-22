QT += testlib widgets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \ 
    tst_replacer.cpp

HEADERS += \
    tst_replacer.h

INCLUDEPATH += $$PWD/../Replacer/
include($$PWD/../Replacer/Replacer.pri)
