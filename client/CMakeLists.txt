project(client VERSION 0.1.0 DESCRIPTION "Server")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(APPLE)
    set(APP_TYPE MACOSX_BUNDLE)
else(WIN32)
    set(APP_TYPE WIN32)
endif()

set(SOURCES client.cpp mainwindow.h mainwindow.cpp mainwindow.ui)

add_executable(${PROJECT_NAME} ${APP_TYPE} ${SOURCES})

find_package(Packio REQUIRED)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${Packio_INCLUDE_DIR}")
add_dependencies(${PROJECT_NAME} Packio)

find_package(JSON REQUIRED)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${JSON_INCLUDE_DIR}")
add_dependencies(${PROJECT_NAME} JSON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
