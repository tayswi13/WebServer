# 最小版本号
cmake_minimum_required(VERSION 3.0)

# 指定项目名称
project(WebServer)

# 指定可执行文件的目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 指定头文件目录
include_directories(./include)

# 指定源代码目录
aux_source_directory(./src SRC)

# 添加编译参数
add_compile_options(-Wall -std=c++11 -O2)

# 生成可执行文件
add_executable(main ${SRC})