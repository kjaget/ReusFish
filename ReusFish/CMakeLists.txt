cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
project(reusfish)

add_definitions(-std=c++11 -DZED_SUPPORT -Wall  -Wextra)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto=8")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Ofast -flto=8")

add_executable(reusfish
Animal.cpp
Aspects.cpp
Biome.cpp
Giants.cpp
Mineral.cpp
Plant.cpp
ReusFish.cpp
Source.cpp
SourceContainer.cpp
SourceTypeList.cpp
Yield.cpp
)

