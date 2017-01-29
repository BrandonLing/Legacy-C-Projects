#include "Camera.h"

void Camera::init()
{
    this->viewWidth = this->xRight - this->xLeft;
    this->viewHeight = this->yHigh - this->yLow;

    this->proj = glm::ortho(this->xLeft, this->xRight, this->yLow, this->yHigh, this->zNear, this->zFar);

    this->cameraPos = glm::vec3(-5.0f, -5.0f, 0.0f);
    this->cameraTarget = glm::vec3(-5.0f, -50.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    this->model = glm::translate(glm::mat4(1.0f), glm::vec3(this->xRight/2, this->yHigh/2, 0.0f));

    this->modelviewproj = this->proj * this->view * this->model;

}

void Camera::updateCamPos(float x, float y, float z)
{
    this->cameraPos = glm::vec3(x, y, z);
    this->modelviewproj = this->proj * this->view * this->model;
}

void Camera::updateCamTarget(float x, float y, float z)
{
    this->cameraTarget = glm::vec3(x, y, z);
    this->view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
    this->modelviewproj = this->proj * this->view * this->model;
}

void Camera::updateCamUpVec(float x, float y, float z)
{
    this->cameraUp = glm::vec3(x, y, z);
    this->modelviewproj = this->proj * this->view * this->model;
}
