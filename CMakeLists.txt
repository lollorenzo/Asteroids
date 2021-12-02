cmake_minimum_required(VERSION 3.10)

set(SFML_ROOT_DIR "C:/SFML" CACHE PATH "Root of SFML lirbary folder")

# set the project name
project(Asteroids)

set(
    SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/custom_texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/custom_texture.h
    ${CMAKE_CURRENT_LIST_DIR}/src/common/game_entity.h
    ${CMAKE_CURRENT_LIST_DIR}/src/common/collision_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/collision_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/src/asteroid/asteroid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/asteroid/asteroid.h
    ${CMAKE_CURRENT_LIST_DIR}/src/asteroid/asteroid_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/asteroid/asteroid_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/src/spaceship/spaceship.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/spaceship/spaceship.h
)

# add the executable
add_executable(Asteroids ${SOURCE_FILES})

# set include dirs
target_include_directories(Asteroids PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

set(
    REQUIRED_PACKAGES
    graphics
    window
    system
)

# Add location to search for SFML component
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${SFML_ROOT_DIR})
# find SFML package
find_package(SFML COMPONENTS REQUIRED ${REQUIRED_PACKAGES})

foreach(PKG ${REQUIRED_PACKAGES})    
    # Link loaded packages
    target_link_libraries(Asteroids sfml-${PKG})
endforeach(PKG ${REQUIRED_PACKAGES})

if(MSVC)
    # If i'm using Visual studio i should create filters and change exceution folder
    set_target_properties(Asteroids PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
    set_property(DIRECTORY ${CMAKE_CURRENT_BIN_PATH} PROPERTY VS_STARTUP_PROJECT Asteroids)
    file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
    foreach(_source IN ITEMS ${_source_list})
        get_filename_component(_source_path "${_source}" PATH)
        string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_group_path}")
        source_group("${_group_path}" FILES "${_source}")
    endforeach()
endif(MSVC)
