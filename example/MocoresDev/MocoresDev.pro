TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    mocores_init.cpp \
    mocores_register.cpp

HEADERS += \
    mocores_init.h \
    mocores_register.h
