TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    file.cpp \
    filesystem.cpp \
    iomethod.cpp \
    logerror.cpp \
    settings.cpp \
    mocoresinstance.cpp \
    errcode.cpp

HEADERS += \
    file.h \
    filesystem.h \
    iomethod.h \
    logerror.h \
    platform.h \
    settings.h \
    mocoresinstance.h \
    errcode.h
