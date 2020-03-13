//
// Created by cxh on 20-3-13.
//

#ifndef HELLOGL_SHAPE_H
#define HELLOGL_SHAPE_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VertData {
    float *vertices;
    unsigned int size;
    unsigned int AttrNumber;
    unsigned int VertNumber;
    unsigned int *indices;
    unsigned int size2;
};

class Shape {
public:

    explicit Shape(VertData);

    virtual ~Shape();

    virtual void paint();

    virtual void add_texture(const char *);

    void bind_texture();

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int vertNumber;
    std::vector<unsigned int> textures;
};


#endif //HELLOGL_SHAPE_H
