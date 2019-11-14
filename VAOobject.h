//
// Created by cxh on 19-11-14.
//

#ifndef HELLOGL_VAOOBJECT_H
#define HELLOGL_VAOOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAOobject {
public:
    VAOobject(float vertices[], unsigned int size);
    VAOobject(float vertices[], unsigned int size, unsigned int *indices, unsigned int size2);
    void bindVAO();
    void deleteVAO();
    unsigned int VAO;
    bool isIndices;

};


#endif //HELLOGL_VAOOBJECT_H
