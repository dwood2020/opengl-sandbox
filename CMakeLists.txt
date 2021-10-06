# Top-level: OpenGL Sandbox
# This project builds a single executable for showcasing ("sandbox")
# ==================================================================

cmake_minimum_required(VERSION 3.14)

project(opengl-sandbox VERSION 1.0
    DESCRIPTION "OpenGL Sandbox project."
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# this is the name of the "main" target: the sandbox executable
set(MAIN_TARGET_NAME ${CMAKE_PROJECT_NAME})


# set an additional include directory globally
include_directories(${PROJECT_SOURCE_DIR}/lib/include)


# all sources are contained in the src folder
add_subdirectory(${PROJECT_SOURCE_DIR}/src)