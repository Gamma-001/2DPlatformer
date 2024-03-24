cmake_minimum_required(VERSION 3.18)

project(2D-Platformer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    "${CMAKE_SOURCE_DIR}/vendor/glfw/include"
    "${CMAKE_SOURCE_DIR}/vendor/glm"
    "${CMAKE_SOURCE_DIR}/vendor"
    "${CMAKE_SOURCE_DIR}/2DPlatformer"
    "${CMAKE_SOURCE_DIR}/lib/include"
    "${CMAKE_SOURCE_DIR}/2DPlatformer/include"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    link_directories("${CMAKE_SOURCE_DIR}/vendor/glfw/build/src/Release")
else()
    link_directories("${CMAKE_SOURCE_DIR}/vendor/glfw/build/src")
endif()

add_executable(2D-Platformer 
    ${CMAKE_SOURCE_DIR}/2DPlatformer/main.cpp 
    ${CMAKE_SOURCE_DIR}/vendor/glad/glad.c
)
target_link_libraries(2D-Platformer glfw3 engine game)

add_subdirectory(lib)
add_subdirectory(2DPlatformer)