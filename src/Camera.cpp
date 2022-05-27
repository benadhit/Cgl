#include "Camera.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <cmath>
#include <math.h>
#include <iostream>

Camera::Camera(glm::vec3 position)
    : position(position), 
    worldUp(glm::vec3(0.0,1.0,0.0f)),
    yaw(-90.f),
    pitch(0.0f), 
    speed(2.5f),
    zoom(45.0f),
    sensitivity(0.1f),
    front(glm::vec3(0,0,-1.0f))
{
    UpdateCameraVector();
}

void Camera::UpdateCameraDirection(double dx, double dy)
{
    yaw+=dx;
    pitch += dy;
    if (pitch > 89.f)
    {
        pitch = 89.f;
    }else if (pitch < -89.f) {
        pitch = -89.f;
    }
    UpdateCameraVector();
}

void Camera::UpdateCameraPos(CameraDirection direction, double dt)
{
    float velocity = (float)dt *speed;
    switch (direction) {
    case CameraDirection::FORWARD:
        position += front *velocity;
        break;
    case CameraDirection::BACKWARD:
        position -= front *velocity;
        break;
    case CameraDirection::UP:
        position += up * velocity;
        break;
    case CameraDirection::DOWN:
        position -= up * velocity;
        break;
    case CameraDirection::LEFT:
        position -= right * velocity;
        break;
    case CameraDirection::RIGHT:
        position += right * velocity;
        break;
    default:
        break;
    }
}

void Camera::UpdateCameraZoom(double dy)
{
    if (zoom > 1.f && zoom < 45.f)
    {
        zoom -=dy;
    } else if (zoom < 1.f) {
        zoom = 1.f;
    }else {
        zoom =45.f;
    }
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::UpdateCameraVector()
{
    glm::vec3 direction;
    std::cout << "yaw: " << yaw;
    std::cout << "Pitch" << pitch << std::endl; 
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));
    front = glm::normalize(direction);
    std::cout << "x: " <<direction.x 
        << "y: "<<direction.y 
        <<"z: "<< direction.z <<std::endl;
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
