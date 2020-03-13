cmake_minimum_required(VERSION 3.14)
project(hellogl)

set(CMAKE_CXX_STANDARD 11)

set(TARGET_LIB -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor)
#set(TARGET_DIR "/usr/local/include/glad/" "/usr/local/include/GLFW/" "/usr/local/include/KHR/")
add_executable(hellogl main.cpp utils/glad.c shader.h shader.cpp VAOobject.cpp VAOobject.h utils/stb_image.h utils/stb_image.cpp Source/vertices_data.h camera.cpp camera.h model/Model.cpp model/Model.h Shader.cpp Shader.h model/Shape.cpp model/Shape.h model/Cube.cpp model/Cube.h)
include_directories(glm shader)
target_link_libraries(hellogl ${TARGET_LIB})
#target_include_directories(hellogl PUBLIC "${PROJECT_BINARY_DIR}")
#include_directories(${TARGET_DIR})