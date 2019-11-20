//
// Created by cxh on 19-11-19.
//

#ifndef HELLOGL_MATRIXUNIFORM_H
#define HELLOGL_MATRIXUNIFORM_H

#include <gtc/matrix_transform.hpp>
#include "glm/glm.hpp"
#include <gtc/type_ptr.hpp>

class MatrixUniform {
public:
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;

    MatrixUniform();
};


#endif //HELLOGL_MATRIXUNIFORM_H
