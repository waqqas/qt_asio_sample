project(client VERSION 0.1.0 DESCRIPTION "Server")

set(SOURCES client.cpp )

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Packio REQUIRED)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${Packio_INCLUDE_DIR}")
add_dependencies(${PROJECT_NAME} Packio)

find_package(JSON REQUIRED)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${JSON_INCLUDE_DIR}")
add_dependencies(${PROJECT_NAME} JSON)
