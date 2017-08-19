# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (MocoresMaster)

set (MOCORES_VERSION_MAJOR 1)
set (MOCORES_VERSION_MINOR 0)

# 添加子目录
add_subdirectory(deps)
add_subdirectory(include)
add_subdirectory(lib)

