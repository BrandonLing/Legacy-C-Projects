#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <Point.h>
#include <Face.h>

class ObjModel
{
    public:
        //Obj
        std::vector <std::string> comments; //#comments
        std::string matLib; //matlib
        std::string objectName; //o
        std::string mat; //material
        int s;

        std::vector<Point> verts; //v
        std::vector<Point> norms; //vn
        std::vector<Point> textVerts; //vt
        std::vector<Face> faces; //f

        //Mtl
        std::string map_Kd; //difuse texture map

        //openGL texture
        std::vector<GLuint> textureBook;
    protected:
    private:
};

#endif // OBJMODEL_H
