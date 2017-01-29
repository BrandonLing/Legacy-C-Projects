#include "Camera.h"

void Camera::init()
{
    //init vars
    this->zFar = 1000.0f;
    this->zNear = 0.05f;
    this->aspectRatio = 1280.0f/720.0f;
    this->fov = 25.0 * 3.14/180; //degrees field of view in radian
    this->yawCorrAngle = 0.27 * (atan2(this->aspectRatio * tan(this->fov), 1.0)) * 180/3.14;
    this->pitchCorrAngle = this->fov/4.0;

    //init camera var values, promptly overwritten
    this->cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    this->cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->proj = glm::perspective(this->fov, this->aspectRatio, this->zNear, this->zFar);
    //this->proj = glm::frustum(-1.0, 1.0, -1.0, 1.0, 0.1, 1000.0);

    //this->proj = glm::ortho(this->xLeft, this->xRight, this->yLow, this->yHigh, this->zNear, this->zFar);
    //std::cout << this->fov << "," << this->aspectRatio << "\n";

    this->view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
    this->model = glm::mat4(1.0);

    this->modelviewproj = this->proj * this->view * this->model;

    this->yFlag = false;
    this->strafeFlag = true;

}

void Camera::updateCamPos(float x, float y, float z)
{
    this->cameraPos = glm::vec3(x, y, z);
}

void Camera::updateCamTarget(float x, float y, float z)
{
    this->cameraTarget = glm::vec3(x, y, z);
}

void Camera::updateCamUpVec(float x, float y, float z)
{
    this->cameraUp = glm::vec3(x, y, z);
}


void Camera::updateMVPMatrix()
{
    //update view
    this->view = glm::lookAt(this->cameraPos, this->cameraTarget, this->cameraUp);

    //calculate mvp matrix
    this->modelviewproj = this->proj * this->view * this->model;
}

void Camera::translate(float x, float y, float z)
{
    this->model = glm::translate(this->model, glm::vec3(x, y, z));
    this->updateMVPMatrix();
}

void Camera::rot(float x, float y, float z)
{
    float degreesToRadian = 3.14/180;
    this->model = glm::rotate(this->model, x * degreesToRadian, glm::vec3(1.0, 0.0, 0.0));
    this->model = glm::rotate(this->model, -y * degreesToRadian, glm::vec3(0.0, 1.0, 0.0));
    this->model = glm::rotate(this->model, z * degreesToRadian, glm::vec3(0.0, 0.0, 1.0));
    this->updateMVPMatrix();
}

void Camera::scale(float x, float y, float z)
{
    this->model = glm::scale(this->model, glm::vec3(x, y, z));
    this->updateMVPMatrix();
}

void Camera::restoreModelMatrix()
{
    this->model = glm::mat4(1.0);
}
