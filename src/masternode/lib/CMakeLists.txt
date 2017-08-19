# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (MocoresDemo)
# 添加头文件
include_directories(../include)
# 添加子目录

SET(CONTAINER_SRC container)
SET(DATABASE_SRC database)
SET(FILESYSTEM_SRC filesystem)
SET(LOG_SRC log)
SET(NET_SRC net)
SET(SQLITE_SRC sqlite)
SET(THREAD_SRC thread)
SET(UTILITY_SRC utility)

# add_subdirectory(container)
# add_subdirectory(database)
# add_subdirectory(filesystem)
# add_subdirectory(log)
# add_subdirectory(net)
# add_subdirectory(serialization)
# add_subdirectory(sqlite)
# add_subdirectory(thread)
# add_subdirectory(utility)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)
# 指定生成目标
add_executable(MocoresDemo ${DIR_LIB_SRCS} 
	${CONTAINER_SRC}
	${DATABASE_SRC}
	${FILESYSTEM_SRC}
	${LOG_SRC}
	${NET_SRC}
	${SQLITE_SRC}
	${THREAD_SRC}
	${UTILITY_SRC})
