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
#include "utils/stb_image.h"
#include "Source/vertices_data.h"
#include "camera.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool firstMouse = true;
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;

camera FirstCamera;

int main(int argc, char *argv[]) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FirstCameraGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    shader shader1("../shader/vert", "../shader/frag");
    shader lightShader("../shader/lightvert", "../shader/lightfrag");

    VAOobject object3(cube);
    VAOobject sun(lightData);
    VAOobject norcube(normalvertices, 3);
//    VAOobject objectCube(cube);
//    VAOobject object1(vertices);
    object3.add_texture("/home/cxh/CLionProjects/hellogl/container.jpg");
    object3.add_textureA("/home/cxh/CLionProjects/hellogl/awesomeface.png");
//  every time when you set uniform ,you have to use share FirstCamera.
    shader1.use();
    shader1.setInt("texture1", 0);
    shader1.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window)) {
        FirstCamera.update_time();
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        shader1.use();
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(FirstCamera.Zoom), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
        shader1.setMatrixf("view", FirstCamera.get_view());
        shader1.setMatrixf("projection", projection);
        object3.bind_texture();
        for (unsigned int i = 1; i < 11; i++) {
            float speed = 1;
            if (i % 3 == 0 || i == 1) {
                speed = (float) glfwGetTime();
            }
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i - 1]);
            float angle = 20.0f * i;
            model = glm::rotate(model, speed * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
            shader1.setMatrixf("model", model);
            shader1.setVec3f("lightColor", 0.5, 0.5, 0.5);
            shader1.setVec3f("objectColor", 1.0, 0.5, 0.3);
            object3.bindVAO();
        }
        lightShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-4.0, 2.0, -4.0));
        model = glm::scale(model,glm::vec3(0.4));
        lightShader.setMatrixf("model", model);
        lightShader.setMatrixf("view", FirstCamera.get_view());
        lightShader.setMatrixf("projection", projection);
        sun.bindVAO();

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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        FirstCamera.processInput(FORWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        FirstCamera.processInput(BACKWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        FirstCamera.processInput(LEFT);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        FirstCamera.processInput(RIGHT);
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    FirstCamera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    FirstCamera.processScrollMovement(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

    glViewport(0, 0, width, height);
}
