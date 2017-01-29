#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <IsoConversion.h>

//Core Dependencies
#include <MapCore.h>

extern MapCore MapData;

class Camera
{
    public:
        glm::mat4 proj;
        glm::vec3 cameraPos;
        glm::vec3 cameraTarget;
        glm::vec3 cameraUp;
        glm::mat4 view;
        glm::mat4 model;
        glm::mat4 modelviewproj;
        float xLeft = -160.0;
        float xRight = 160.0;
        float yHigh = 90.0;
        float yLow = -90.0;
        float zFar = 1000.0;
        float zNear = -1000.0;
        float viewWidth, viewHeight;

        void init();
        void updateCamPos(float x, float y, float z);
        void updateCamTarget(float x, float y, float z);
        void updateCamUpVec(float x, float y, float z);
    protected:
    private:
};

#endif // CAMERA_H
