//
// Created by cxh on 19-11-14.
//

#ifndef HELLOGL_SHADER_H
#define HELLOGL_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class shader {
public:
    shader(const char *verticesPath, const char *fragmentPath);

    virtual ~shader();

    void use();

private:
    unsigned int ID;
    char *vertice;
    char *fragment;
};

#endif //HELLOGL_SHADER_H
