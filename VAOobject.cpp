//
// Created by cxh on 19-11-14.
//

#include "VAOobject.h"
#include <iostream>
#include "stb_image.h"

std::vector<long long> unit_texture = {GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2,
                                       GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5};

VAOobject::VAOobject(VertData data) : VAO(0), VBO(0), EBO(0), vertNumber(data.VertNumber) {
    isIndices = false;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size, data.vertices, GL_STATIC_DRAW);
    if (data.indices) {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size2, data.indices, GL_STATIC_DRAW);
        vertNumber = data.size2 / sizeof(unsigned int);
        isIndices = true;
    }
    int length = data.size / data.VertNumber / sizeof(float);
    if (data.AttrNumber >= 1) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, length * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
    }
    if (data.AttrNumber == 2) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, length * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    if (data.AttrNumber == 3) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, length * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, length * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
}

//VAOobject::VAOobject(float *vertices, unsigned int
//size, unsigned int *indices, unsigned int size2) {
//    isIndices = true;
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size2, indices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//}

void VAOobject::bindVAO() {
    glBindVertexArray(VAO);
    if (!isIndices) {
        glDrawArrays(GL_TRIANGLES, 0, vertNumber);
    } else {
        glDrawElements(GL_TRIANGLES, vertNumber, GL_UNSIGNED_INT, 0);
    }
//    glBindVertexArray(0);
}

void VAOobject::deleteVAO() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if (isIndices) {
        glDeleteBuffers(1, &EBO);
    }
}

void VAOobject::add_texture(const char *path) {
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

void VAOobject::add_textureA(const char *path) {
    unsigned int texture;
    glGenTextures(1, &texture);
    std::cout << texture << std::endl;
    glBindTexture(GL_TEXTURE_2D, texture);
// 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 加载并生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    textures.push_back(texture);
}

void VAOobject::bind_texture() {
    for (int i = 0; i < textures.size(); i++) {
        glActiveTexture(unit_texture[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
}