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
    utility/mvariant.cpp \
    utility/merroror.cpp \
    distributeddataset.cpp \
    utility/strutil.cpp \
    database/sqldatabase.cpp \
    database/sqlwrapper.cpp \
    thread/threadpool.cpp \
    thread/mocores_condition_variable.cpp \
    thread/singleton.cpp \
    log/logerror.cpp \
    log/logger.cpp

DISTFILES += \
    mocores.ini \
    build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Debug/.qmake.stash \
    mocores/build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Release/.qmake.stash \
    build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/mocores.exe \
    mocores/build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Release/release/mocores.exe \
    build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Debug/data_frame.db \
    build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Debug/object_script.mocores.Debug \
    build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Debug/object_script.mocores.Release \
    build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Debug/sqlite3 \
    mocores/build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Release/data_frame.db \
    mocores/build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Release/object_script.mocores.Debug \
    mocores/build-mocores-Desktop_Qt_5_7_0_MinGW_32bit-Release/object_script.mocores.Release \
    condition.txt \
    mutex.txt


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
    config.h \
    utility/mvariant.h \
    utility/merroror.h \
    utility/strutil.h \
    distributeddataset.h \
    database/sqldatabase.h \
    database/sqlwrapper.h \
    thread/threadpool.h \
    thread/mocores_condition_variable.h \
    thread/singleton.h \
    log/logerror.h \
    log/logger.h \
    log/loglevel.h \
    log/loglayout.h \
    log/logmsg.h \
    log/logappender.h


LIBS += -lpthread libwsock32 libws2_32

SUBDIRS += \
    serialization/serialization.pro
