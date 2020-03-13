//
// Created by cxh on 20-3-13.
//

#include "Cube.h"

Cube::Cube(VertData data) : VAO(0), VBO(0), EBO(0), vertNumber(data.VertNumber) {
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
        glVertexAttribPointer(1, attr, GL_FLOAT, GL_FALSE, length * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    if (data.AttrNumber == 3) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, length * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, length * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
}

void Shape::deleteVAO() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if (isIndices) {
        glDeleteBuffers(1, &EBO);
    }
}

void Shape::paint() {
    glBindVertexArray(VAO);
    if (!isIndices) {
        glDrawArrays(GL_TRIANGLES, 0, vertNumber);
    } else {
        glDrawElements(GL_TRIANGLES, vertNumber, GL_UNSIGNED_INT, 0);
    }
//    glBindVertexArray(0);
}
void Shape::add_textureA(const char *path) {
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