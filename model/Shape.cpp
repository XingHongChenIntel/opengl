//
// Created by cxh on 20-3-13.
//

#include "Shape.h"
#include <iostream>
#include "../utils/stb_image.h"

std::vector<long long> unit_texture = {GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2,
                                       GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5};

Shape::Shape(VertData data) : VAO(0), VBO(0), EBO(0), vertNumber(data.VertNumber) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, data.size, data.vertices, GL_STATIC_DRAW);
}

Shape::~Shape() {
    glDeleteVertexArrays(1, &VAO);
}

void Shape::paint() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertNumber);
}


void Shape::add_texture(const char *path) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
// 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 加载并生成纹理
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    textures.push_back(texture);
}


void Shape::bind_texture() {
    for (int i = 0; i < textures.size(); i++) {
        glActiveTexture(unit_texture[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
}