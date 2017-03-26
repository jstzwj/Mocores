TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
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
    sqlite/sqlite3.c \
    database/sqlconnection.cpp \
    databasemodule.cpp \
    nodelistenermodule.cpp \
    messagequeue.cpp \
    thread/mocores_mutex.cpp \
    database/sqlquery.cpp \
    database/sqlrecord.cpp \
    database/sqlresultset.cpp \
    mvariant.cpp

DISTFILES += \
    mocores.ini \


HEADERS += \
    database/mocores_sql.h \
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
    settings.h \
    database/sqlconnection.h \
    databasemodule.h \
    nodelistenermodule.h \
    messagequeue.h \
    thread/mocores_mutex.h \
    database/sqlquery.h \
    database/sqlrecord.h \
    database/sqlresultset.h \
    mvariant.h


LIBS += -lpthread libwsock32 libws2_32
