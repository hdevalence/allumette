include_directories(${EIGEN3_INCLUDE_DIR} ${LIBRAW_INCLUDE_DIR})

add_library(AllumetteEngine ImageLoader.cpp
                            EImage.cpp
                            AllumetteStacker.cpp)

target_link_libraries(AllumetteEngine ${LIBRAW_LIBRARIES})
qt5_use_modules(AllumetteEngine Core)


