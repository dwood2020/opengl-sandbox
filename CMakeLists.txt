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
#TODO: Add MinGW + Linux/GCC build options
if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # building on Windows using MSVC 
        set_target_properties(IUP_LIBRARY PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/msvc-x64/iup.lib)
        set_target_properties(IUPGL_LIBRARY PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/msvc-x64/iupgl.lib)
        
        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC IUP_LIBRARY)
        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC IUPGL_LIBRARY)
        
        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC comctl32)
        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC opengl32)

        # set additional linker flag to avoid LNK4098
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")

    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # building on Windows using GCC

        # TEST: use libc++ ...STATE: libc++ not working effortlessly on MinGW/MSYS2
        #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++") 

        set_target_properties(IUP_LIBRARY PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/mingw-x64/libiup.a)
        set_target_properties(IUPGL_LIBRARY PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/mingw-x64/libiupgl.a)
        
        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC IUP_LIBRARY)
        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC IUPGL_LIBRARY)

        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC comctl32)
        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC opengl32)        
    endif()

elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # building on Linux using GCC
        #NOTE: THis is a new function (avail. since CMake 3.13) which "should be avoided"
        target_link_directories(${MAIN_TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/gcc-x64)
        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC iup)
        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC iupgl)

        target_link_libraries(${MAIN_TARGET_NAME} PUBLIC dl)
    endif()
endif()

