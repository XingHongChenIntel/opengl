//

#include "camera.h"

//
// Created by cxh on 19-11-20.

camera::camera(glm::vec3 Position, glm::vec3 WorldUp, float yaw, float pitch) : forwardDirect(
        glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    position = Position;
    worldup = WorldUp;
    Yaw = yaw;
    Pitch = pitch;
    update();
}

// Constructor with scalar values
camera::camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        : forwardDirect(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    position = glm::vec3(posX, posY, posZ);
    worldup = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    update();
}

void camera::update() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    forwardDirect = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    rightDirect = glm::normalize(glm::cross(forwardDirect, worldup));
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    upDirect = glm::normalize(glm::cross(rightDirect, forwardDirect));
}

void camera::set_speed(float sp) {
    MovementSpeed = sp;
}

glm::mat4 camera::get_view() {
    view = glm::lookAt(position, forwardDirect + position, upDirect);
    return view;
}

void camera::update_time() {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
}

void camera::processInput(Camera_Movement direction) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD) {
        position += forwardDirect * velocity;
    } else if (direction == BACKWARD) {
        position -= forwardDirect * velocity;
    } else if (direction == LEFT) {
        position -= rightDirect * velocity;
    } else if (direction == RIGHT) {
        position += rightDirect * velocity;
    }
}

void camera::processMouseMovement(double xoffset, double yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;
    if (constrainPitch) {
        if (Pitch > 89.0f) {
            Pitch = 89.0f;
        }
        if (Pitch < -89.0f) {
            Pitch = -89.0f;
        }
    }
    update();
}

void camera::processScrollMovement(double xoffset, double yoffset) {
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= yoffset;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}


