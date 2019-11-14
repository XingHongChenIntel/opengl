//
// Created by cxh on 19-11-14.
//
#include "shader.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>

shader::shader(const char *verticesPath, const char *fragmentPath) {
    vertice = nullptr;
    fragment = nullptr;
    std::ifstream vert;
    std::ifstream frag;
    vert.open(verticesPath);
    frag.open(fragmentPath);
    std::stringstream vertStream, fragStream;
    vertStream << vert.rdbuf();
    fragStream << frag.rdbuf();
    vert.close();
    frag.close();
    std::string vertString = vertStream.str();
    std::string fragString = fragStream.str();
    const char *vertTemp = vertString.c_str();
    const char *fragTemp = fragString.c_str();
    int vertLen = strlen(vertTemp);
    int fragLen = strlen(fragTemp);
    vertice = new char[vertLen];
    fragment = new char[fragLen];
    strcpy(vertice, vertTemp);
    strcpy(fragment, fragTemp);

    int success;
    char infoLog[512];
    unsigned int vertShade = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragShade = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertShade, 1, &vertice, NULL);
    glCompileShader(vertShade);
    glGetShaderiv(vertShade, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShade, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    glShaderSource(fragShade, 1, &fragment, NULL);
    glCompileShader(fragShade);
    glGetShaderiv(fragShade, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShade, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    ID = glCreateProgram();
    glAttachShader(ID, vertShade);
    glAttachShader(ID, fragShade);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertShade);
    glDeleteShader(fragShade);
}

shader::~shader() {
    if (!vertice && !fragment) {
        vertice = nullptr;
        fragment = nullptr;
    } else {
        delete[] vertice;
        delete[] fragment;
    }
}

void shader::use() {
    glUseProgram(ID);
}