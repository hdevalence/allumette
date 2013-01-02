include_directories(${EIGEN3_INCLUDE_DIR} "${PROJECT_SOURCE_DIR}/src/lib")
add_executable(allumette-cli main.cpp)
qt5_use_modules(allumette-cli Core)
target_link_libraries(allumette-cli AllumetteEngine)

