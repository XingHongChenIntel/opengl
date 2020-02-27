//
// Created by cxh on 19-11-20.
//

#ifndef HELLOGL_CAMERA_H
#define HELLOGL_CAMERA_H

#include <gtc/matrix_transform.hpp>
#include "glm/glm.hpp"
#include <gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>


enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class camera {
public:

    glm::vec3 position;
    glm::vec3 upDirect;
    glm::vec3 rightDirect;
    glm::vec3 forwardDirect;
    glm::vec3 worldup;
    glm::mat4 view;

    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    float currentTime = 0.0f;
    float lastTime = 0.0f;
    float deltaTime;

    camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH);

    camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void processInput(Camera_Movement direction);

    void processMouseMovement(double, double, GLboolean = GL_TRUE);

    void processScrollMovement(double xoffset, double yoffset);

    void update();

    void update_time();

    void set_speed(float);

    glm::mat4 get_view();
};


#endif //HELLOGL_CAMERA_H
