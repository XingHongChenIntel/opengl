// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <zconf.h>
#include <gtc/matrix_transform.hpp>
#include "shader.h"
#include "VAOobject.h"
#include "stb_image.h"
#include "vertices_data.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc, char *argv[]) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FirstGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    char path[150] = {0};
    char *p = getcwd(path, 150);
    std::cout << p << std::endl;

    shader shader1("../vert", "../frag");

    VAOobject object3(cube);
//    VAOobject objectCube(cube);
//    VAOobject object1(vertices);
    object3.add_texture("/home/cxh/CLionProjects/hellogl/container.jpg");
    object3.add_textureA("/home/cxh/CLionProjects/hellogl/awesomeface.png");
//  every time when you set uniform ,you have to use share first.
    shader1.use();
    shader1.setInt("texture1", 0);
    shader1.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
//        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(60.0f),float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
//        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        shader1.use();
//        shader1.setMatrixf("view", view);
        shader1.setMatrixf("projection", projection);
//        shader1.setMatrixf("model", model);
        object3.bind_texture();
//        object3.bindVAO();
        for(unsigned int i = 1; i < 11; i++)
        {
            float speed = 1;
            if(i%3 == 0 || i ==1){
                speed = (float)glfwGetTime();
            }
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i-1]);
            float angle = 20.0f * i;
            model = glm::rotate(model, speed * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
            shader1.setMatrixf("model", model);
            object3.bindVAO();
        }
        float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        shader1.setMatrixf("view", view);
        object3.bindVAO();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    object3.deleteVAO();
    glfwTerminate();
    return EXIT_SUCCESS;
}


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

    glViewport(0, 0, width, height);
}
