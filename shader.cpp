//
// Created by cxh on 19-11-14.
//
#include "shader.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <gtc/type_ptr.hpp>


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

void shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void shader::setMatrixf(const std::string &name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::add_uniform(std::string variable, std::string dataType) {

}