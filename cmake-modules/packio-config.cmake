include(ExternalProject)

if(NOT TARGET Packio_project)
    ExternalProject_Add(Packio_project 
        URL https://github.com/qchateau/packio/archive/2.0.1.tar.gz
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    ExternalProject_Get_Property(Packio_project SOURCE_DIR)

    ExternalProject_Add(Packio_install_project 
        DOWNLOAD_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND cp -R ${SOURCE_DIR}/include ${CMAKE_INSTALL_PREFIX}
    )
endif()

ExternalProject_Get_Property(Packio_project SOURCE_DIR)

set(Packio_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include) 

add_library(Packio STATIC IMPORTED)

add_dependencies(Packio_install_project Packio_project)
add_dependencies(Packio Packio_install_project)