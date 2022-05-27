#pragma once

#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraDirection { 
    NONE,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

class Camera {
public:
    Camera(glm::vec3 position);

    void UpdateCameraDirection(double dx, double dy);

    void UpdateCameraPos(CameraDirection direction, double dt);

    void UpdateCameraZoom(double dy);

    glm::mat4 GetViewMatrix();

private:
    void UpdateCameraVector();

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    float zoom;

};