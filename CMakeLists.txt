cmake_minimum_required(VERSION 3.0)
project(opengl_base)

# See https://github.com/SasLuca/GLFWCMakeTemplate/tree/main
include(cmake/glad.cmake)
include(cmake/glfw.cmake)

add_executable(main main.cpp)

target_link_libraries(main glad glfw)