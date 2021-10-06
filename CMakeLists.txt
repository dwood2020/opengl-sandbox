# Top-level: OpenGL Sandbox
# This project builds a single executable for showcasing ("sandbox")
# ==================================================================

cmake_minimum_required(VERSION 3.15)

project(opengl-sandbox VERSION 1.0
    DESCRIPTION "OpenGL Sandbox project."
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# this is the name of the "main" target: the sandbox executable
set(MAIN_TARGET_NAME ${CMAKE_PROJECT_NAME})


# DEBUG:
add_executable(${MAIN_TARGET_NAME})


# set an additional include directory globally
include_directories(${PROJECT_SOURCE_DIR}/lib/include)


# all sources are contained in the src folder
add_subdirectory(${PROJECT_SOURCE_DIR}/src)


# add the iup libraries
add_library(IUP_LIBRARY STATIC IMPORTED)
add_library(IUPGL_LIBRARY STATIC IMPORTED)

# DEBUG
message("CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

# currently, only msvc build available:
set_target_properties(IUP_LIBRARY PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/iup.lib)
set_target_properties(IUPGL_LIBRARY PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/iupgl.lib)

target_link_libraries(${MAIN_TARGET_NAME} PUBLIC IUP_LIBRARY)
target_link_libraries(${MAIN_TARGET_NAME} PUBLIC IUPGL_LIBRARY)

target_link_libraries(${MAIN_TARGET_NAME} PUBLIC comctl32)
target_link_libraries(${MAIN_TARGET_NAME} PUBLIC opengl32)