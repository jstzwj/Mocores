TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    database/resultset.cpp \
    database/sqlmanager.cpp \
    database/statement.cpp \
    filesystem/file.cpp \
    filesystem/filesystem.cpp \
    filesystem/iomethod.cpp \
    net/mocores_socket.cpp \
    thread/mocores_thread.cpp \
    clio.cpp \
    errcode.cpp \
    logerror.cpp \
    mocores_time.cpp \
    mocoresinstance.cpp \
    settings.cpp \
    sqlite/sqlite3.c

DISTFILES += \
    mocores.ini

HEADERS += \
    database/mocores_sql.h \
    database/resultset.h \
    database/sqlmanager.h \
    database/statement.h \
    filesystem/file.h \
    filesystem/filesystem.h \
    filesystem/iomethod.h \
    net/mocores_socket.h \
    sqlite/sqlite3.h \
    sqlite/sqlite3ext.h \
    thread/mocores_thread.h \
    clio.h \
    errcode.h \
    logerror.h \
    mocores_time.h \
    mocoresinstance.h \
    platform.h \
    settings.h
