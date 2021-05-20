cmake_minimum_required(VERSION 3.17)
project(PascalCompiler)

set(CMAKE_CXX_STANDARD 14)

IF(APPLE)
    include_directories(/usr/local/opt/llvm/include/llvm)
ENDIF()

add_executable(PascalCompiler
        main.cpp)
