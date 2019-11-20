//
// Created by cxh on 19-11-14.
//

#ifndef HELLOGL_SHADER_H
#define HELLOGL_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "glm/glm.hpp"

class shader {
public:
    shader(const char *verticesPath, const char *fragmentPath);

    virtual ~shader();

    void use();

    void setInt(const std::string &name, int value) const;
    void setBool(const std::string &name, bool value) const;
    void setFloat(const std::string &name, float value) const;
    void setMatrixf(const std::string &name, glm::mat4) const;
    void add_uniform(std::string variable, std::string dataType);

private:
    unsigned int ID;
    char *vertice;
    char *fragment;
};

#endif //HELLOGL_SHADER_H
