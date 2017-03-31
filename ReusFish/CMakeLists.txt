cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Release)
project(reusfish)

add_definitions(-std=c++11 -DZED_SUPPORT -Wall  -Wextra)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto=8")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Ofast -flto=8")

add_executable(reusfish
Animal.cpp
Aspects.cpp
Biome.cpp
Building.cpp
Giants.cpp
Landscape.cpp
Mineral.cpp
Plant.cpp
ReusFish.cpp
Source.cpp
SourceContainer.cpp
SourceTypeList.cpp
Space.cpp
Yield.cpp
)

