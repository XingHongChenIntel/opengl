cmake_minimum_required(VERSION 3.14)
project(hellogl)

set(CMAKE_CXX_STANDARD 11)

set(TARGET_LIB -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor)
#set(TARGET_DIR "/usr/local/include/glad/" "/usr/local/include/GLFW/" "/usr/local/include/KHR/")
add_executable(hellogl main.cpp glad.c shader.h shader.cpp VAOobject.cpp VAOobject.h stb_image.h stb_image.cpp MatrixUniform.cpp MatrixUniform.h vertices_data.h)
include_directories(glm)
target_link_libraries(hellogl ${TARGET_LIB})
#target_include_directories(hellogl PUBLIC "${PROJECT_BINARY_DIR}")
#include_directories(${TARGET_DIR})