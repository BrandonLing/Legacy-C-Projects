#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
    public:
        glm::vec3 cameraPos;
        glm::vec3 cameraTarget;
        glm::vec3 cameraUp;

        glm::mat4 proj;
        glm::mat4 view;
        glm::mat4 model;
        glm::mat4 modelviewproj;

        float zFar;
        float zNear;
        float aspectRatio;
        float fov; //degrees field of view
        float yawCorrAngle, pitchCorrAngle;

        void init();
        void updateCamPos(float x, float y, float z);
        void updateCamTarget(float x, float y, float z);
        void updateCamUpVec(float x, float y, float z);
        void updateMVPMatrix();

        void rot(float roll, float pitch, float yaw);
        void translate(float x, float y, float z);
        void scale(float x, float y, float z);
        void restoreModelMatrix();

        //disable/enable y axis moment
        bool yFlag;
        bool strafeFlag;
    protected:
    private:
};

#endif // CAMERA_H
