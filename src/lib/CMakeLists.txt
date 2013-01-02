include_directories(${EIGEN3_INCLUDE_DIR} ${LIBRAW_INCLUDE_DIR})

add_library(AllumetteEngine AllumetteEngine.cpp  ImageLoader.cpp  SourceFrame.cpp  StackerBuffer.cpp  Stacker.cpp)

target_link_libraries(AllumetteEngine ${LIBRAW_LIBRARIES})
qt5_use_modules(AllumetteEngine Core)


