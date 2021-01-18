include(ExternalProject)

if(NOT TARGET JSON_project)
    ExternalProject_Add(JSON_project 
        URL https://github.com/nlohmann/json/releases/download/v3.9.1/include.zip
        URL_HASH SHA256=6bea5877b1541d353bd77bdfbdb2696333ae5ed8f9e8cc22df657192218cad91
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    ExternalProject_Get_Property(JSON_project SOURCE_DIR)

    ExternalProject_Add(JSON_install_project 
        DOWNLOAD_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND cp -R ${SOURCE_DIR}/include ${CMAKE_INSTALL_PREFIX}
    )
endif()

set(JSON_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include) 

add_library(JSON STATIC IMPORTED)

add_dependencies(JSON_install_project JSON_project)
add_dependencies(JSON JSON_install_project)
