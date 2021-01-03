cmake_minimum_required(VERSION 3.12)

list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

# C++ standard.
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(qt_asio_sample VERSION 0.1.0 DESCRIPTION "Sample application that integrates Qt and Boost ASIO")

set(SOURCES main.cpp )

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Packio REQUIRED)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${Packio_INCLUDE_DIR}")
add_dependencies(${PROJECT_NAME} Packio)

find_package(JSON REQUIRED)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${JSON_INCLUDE_DIR}")
add_dependencies(${PROJECT_NAME} JSON)