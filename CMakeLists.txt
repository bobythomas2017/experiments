cmake_minimum_required(VERSION 2.8)
project( Class_filter)
find_package( OpenCV REQUIRED )
add_executable( Class_filter class_filter.cpp )
target_link_libraries(Class_filter ${OpenCV_LIBS} )


