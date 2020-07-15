cmake_minimum_required(VERSION 3.1.0)

project(SimpleParticle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

include_directories(
	"include"
	"library/glad/include"
	"modules/glfw/include"
	"modules/SimpleMath/include")

# OpenGL

find_package(OpenGL REQUIRED)
link_libraries(OpenGL::GL)

# GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
add_subdirectory(modules/glfw)
link_libraries(glfw)

# GLAD

add_library(glad "library/glad/include/glad/glad.h" "library/glad/src/glad.c")
link_libraries(glad)

# Particle

add_subdirectory(source)
link_libraries(SimpleParticle)

add_executable(Main "source/Main.cpp")
