# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (MocoresDemo)
# 添加头文件
include_directories(../include)
include_directories(../dependents/libevent/include)
# 添加子目录
add_subdirectory(container)
add_subdirectory(database)
add_subdirectory(filesystem)
add_subdirectory(log)
add_subdirectory(net)
# add_subdirectory(serialization)
add_subdirectory(sqlite)
add_subdirectory(thread)
add_subdirectory(utility)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)
# 指定生成目标
add_executable(MocoresDemo ${DIR_LIB_SRCS})
# 添加链接库
target_link_libraries(MocoresDemo MocoresContainer)
target_link_libraries(MocoresDemo MocoresDatabase)
target_link_libraries(MocoresDemo MocoresFilesystem)
target_link_libraries(MocoresDemo MocoresLog)
target_link_libraries(MocoresDemo MocoresNet)
target_link_libraries(MocoresDemo MocoresSqlite)
target_link_libraries(MocoresDemo MocoresThread)
target_link_libraries(MocoresDemo MocoresUtility)