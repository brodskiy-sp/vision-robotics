cmake_minimum_required(VERSION 3.20)

project(day02_opencv)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(day02 main.cpp)

target_link_libraries(day02 PRIVATE ${OpenCV_LIBS})

add_executable(test_camera test_camera.cpp)
target_link_libraries(test_camera PRIVATE ${OpenCV_LIBS})

add_executable(view_xr24 view_xr24.cpp)
target_link_libraries(view_xr24 PRIVATE ${OpenCV_LIBS})


add_executable(rtsp_test rtsp_test.cpp)
target_link_libraries(rtsp_test PRIVATE ${OpenCV_LIBS})
