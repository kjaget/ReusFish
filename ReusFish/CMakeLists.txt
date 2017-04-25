cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Release)
project(reusfish)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_definitions(-std=c++11 -DZED_SUPPORT -Wall  -Wextra)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto=8 -march=native -mtune=native")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Ofast -flto=8 -march=native -mtune=native")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -g")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -O2 -g")
find_package(Gperftools REQUIRED) 
add_executable(reusfish
Animal.cpp
Aspects.cpp
Biome.cpp
Building.cpp
EnumerateSources.cpp
Giants.cpp
Landscape.cpp
Mineral.cpp
Plant.cpp
ReusFish.cpp
Source.cpp
SourceContainer.cpp
SourceTypeList.cpp
Space.cpp
UsedList.cpp
Yield.cpp
)

target_link_libraries(reusfish ${GPERFTOOLS_LIBRARIES})

add_executable(check_upgrade_tree
check_upgrade_tree.cpp
Animal.cpp
Aspects.cpp
Biome.cpp
Building.cpp
EnumerateSources.cpp
Giants.cpp
Landscape.cpp
Mineral.cpp
Plant.cpp
Source.cpp
SourceContainer.cpp
SourceTypeList.cpp
Space.cpp
UsedList.cpp
Yield.cpp
)
target_link_libraries(check_upgrade_tree ${GPERFTOOLS_LIBRARIES})
