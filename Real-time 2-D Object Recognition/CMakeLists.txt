cmake_minimum_required(VERSION 3.0.0)
project(P-3 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};G:/opencv/opencv/build/x64/vc16/lib/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(P-3 main.cpp tasks.cpp)
target_link_libraries(P-3 PRIVATE ${OpenCV_LIBS})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
