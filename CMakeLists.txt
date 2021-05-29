cmake_minimum_required(VERSION 3.17)
project(PascalCompiler)

set(CMAKE_CXX_STANDARD 14)

IF(APPLE)
    set(LLVM_PATH /opt/homebrew/opt/llvm)
    include_directories(${LLVM_PATH}/include)
    link_libraries(${LLVM_PATH}/lib/libLLVM.dylib)

ENDIF()

add_executable(ConvertEngineTest
        convertEngine.cpp nodeList.cpp)

add_executable(PascalCompiler
        main.cpp nodeList.cpp)
