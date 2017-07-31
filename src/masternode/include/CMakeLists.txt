# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (MocoresMasterHeader)
# 添加子目录
add_subdirectory(container)
add_subdirectory(database)
add_subdirectory(filesystem)
add_subdirectory(log)
add_subdirectory(net)
add_subdirectory(serialization)
add_subdirectory(sqlite)
add_subdirectory(thread)
add_subdirectory(utility)
# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
  )
# 是否使用标准线程库
option (MocoresUseStdThread "Use thread in c++11 std" ON)
