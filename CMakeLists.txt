cmake_minimum_required(VERSION 3.17)
project(PascalCompiler)

set(CMAKE_CXX_STANDARD 14)

IF(APPLE)
    include_directories(/opt/homebrew/opt/llvm/include)
    link_libraries(/opt/homebrew/opt/llvm/lib/libLLVM-C.dylib)
    set(LLVM_CONFIG /opt/homebrew/opt/llvm/bin)

ENDIF()

set(CMAKE_CXX_FLAGS_<CONFIG>  $(LLVM_CONFIG))
set(CMAKE_CXX_FLAGS --cppflags)
set(CMAKE_CXX_FLAGS --ldflags)
set(CMAKE_CXX_FLAGS --libs core bitwriter)
set(CMAKE_CXX_FLAGS --system-libs)
set(CMAKE_CXX_FLAGS -std=c++11)



add_executable(ConvertEngineTest
        convertEngine.cpp)

add_executable(PascalCompiler
        main.cpp nodeList.cpp convertEngine.cpp)
