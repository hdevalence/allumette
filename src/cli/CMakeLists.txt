add_executable(allumette-cli main.cpp)
qt5_use_modules(allumette-cli Core)
target_link_libraries(allumette-cli AllumetteEngine)

