//
// Created by cxh on 19-11-14.
//

#ifndef HELLOGL_VAOOBJECT_H
#define HELLOGL_VAOOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

struct VertData{
    float *vertices;
    unsigned int size;
    unsigned int AttrNumber;
    unsigned int VertNumber;
    unsigned int *indices;
    unsigned int size2;
};

class VAOobject {
public:

    explicit VAOobject(VertData);

    void bindVAO();

    void add_texture(const char *);
    void add_textureA(const char *);
    void bind_texture();

    void deleteVAO();

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int vertNumber;
    std::vector<unsigned int> textures;
    bool isIndices;

};


#endif //HELLOGL_VAOOBJECT_H
