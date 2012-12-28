cmake_minimum_required(VERSION 2.8.8)

project(allumette)

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)

add_subdirectory(src)

