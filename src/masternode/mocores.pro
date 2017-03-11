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
    errcode.cpp \
    clio.cpp \
    mocores_time.cpp \
    mocores_thread.cpp \
    mocores_socket.cpp

HEADERS += \
    file.h \
    filesystem.h \
    iomethod.h \
    logerror.h \
    platform.h \
    settings.h \
    mocoresinstance.h \
    errcode.h \
    clio.h \
    mocores_time.h \
    mocores_thread.h \
    mocores_socket.h
