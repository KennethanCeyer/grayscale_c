cmake_minimum_required(VERSION 3.17)
project(grayscale C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -m64)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED math.c math.h)
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
