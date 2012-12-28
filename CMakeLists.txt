cmake_minimum_required(VERSION 2.8.8)

project(allumette)

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Qt5Core REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(LibRaw REQUIRED)

add_subdirectory(src)

