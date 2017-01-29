#include "RenderCore.h"

void RenderCore::init()
{
    //Init vars
    this->windowTitle = "Go Online";
    this->windowWidth = 1280;
    this->windowHeight = 720;

    //init SDL2
    bool success1 = SDL_Init(SDL_INIT_VIDEO);
    this->sdlWindow = SDL_CreateWindow(this->windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI);
    this->glContext = SDL_GL_CreateContext(this->sdlWindow);
    SDL_GetWindowSize(this->sdlWindow, &(this->windowWidth), &(this->windowHeight));
    //Check for success of window/openGL creation
    if (success1 != 0) //returns 0 on success
        std::cout << "Error in Render Core: Cannot Init";

    //init openGL
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	glClearColor( 1.f, 0.5f, 0.f, 1.f );
    this->glRefreshViewport();

    //init glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        //Problem: glewInit failed, something is seriously wrong.
        std::cout << "GLEW Init failed\n";
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);

    //Init Generation of Buffers
    glGenBuffers(1, &this->dynamicEntityBuffer);
    glGenBuffers(1, &this->dynamicTextureBuffer);
    glGenVertexArrays(1, &this->dynamicVAO);
}

void RenderCore::quit()
{
    SDL_GL_DeleteContext(this->glContext);
    SDL_Quit();
    this->sdlWindow = NULL;

    //DestroyBuffers
    glDeleteVertexArrays(1, &this->dynamicVAO);
    glDeleteBuffers(1, &this->dynamicTextureBuffer);
    glDeleteBuffers(1, &this->dynamicEntityBuffer);
}

void RenderCore::glRefreshViewport()
{
    SDL_GetWindowSize(this->sdlWindow, &(this->windowWidth), &(this->windowHeight));
    glViewport(-(this->windowWidth), -(this->windowHeight), (this->windowWidth) * 2, (this->windowHeight) * 2);
    std::cout << "Window size set to " << (this->windowWidth) << "x" << (this->windowHeight) << "\n";
}

void RenderCore::printGLInfo()
{
    //print openGL version data
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion =
    glGetString( GL_SHADING_LANGUAGE_VERSION );
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);
}

void RenderCore::renderGameObject(GameObject obj)
{
    //init buffers
    std::vector<float> gpuBuffer;
    std::vector<float> textureBuffer;

    //bug fixes and optimizations
    gpuBuffer.push_back(0.0); //padding bug fix
    gpuBuffer.reserve(1000); //request change in capacity
    textureBuffer.reserve(500);

    //Pull mesh data into gpuBuffer
    ObjModel *mesh = &(ModelData.meshLibrary[obj.meshID]);
    int totalFaces = mesh->faces.size();
    for (int faceIndex = 0; faceIndex < totalFaces; faceIndex++)
    {
        Face polygon = mesh->faces[faceIndex];
        int polySides = polygon.vertex.size();
        if (polySides == 4)
        {//it's a quad
            //Handle vertice information
            //get vertex indices that form the face
            int vertIndex1 = polygon.vertex[0];
            int vertIndex2 = polygon.vertex[1];
            int vertIndex3 = polygon.vertex[2];
            int vertIndex4 = polygon.vertex[3];

            //get vertex points
            Point vertex1 = mesh->verts[vertIndex1 - 1];
            Point vertex2 = mesh->verts[vertIndex2 - 1];
            Point vertex3 = mesh->verts[vertIndex3 - 1];
            Point vertex4 = mesh->verts[vertIndex4 - 1];

            //std::cout << vertex1.x << "," << vertex1.y << "," << vertex1.z << "\n";
            gpuBuffer.push_back(vertex1.x); gpuBuffer.push_back(vertex1.y); gpuBuffer.push_back(vertex1.z);
            gpuBuffer.push_back(vertex2.x); gpuBuffer.push_back(vertex2.y); gpuBuffer.push_back(vertex2.z);
            gpuBuffer.push_back(vertex3.x); gpuBuffer.push_back(vertex3.y); gpuBuffer.push_back(vertex3.z);
            gpuBuffer.push_back(vertex3.x); gpuBuffer.push_back(vertex3.y); gpuBuffer.push_back(vertex3.z);
            gpuBuffer.push_back(vertex4.x); gpuBuffer.push_back(vertex4.y); gpuBuffer.push_back(vertex4.z);
            gpuBuffer.push_back(vertex1.x); gpuBuffer.push_back(vertex1.y); gpuBuffer.push_back(vertex1.z);

            //Handle texture coordinate information
            int textIndex1 = polygon.texture[0];
            int textIndex2 = polygon.texture[1];
            int textIndex3 = polygon.texture[2];
            int textIndex4 = polygon.texture[3];
            Point vt1 = mesh->textVerts[textIndex1 - 1];
            Point vt2 = mesh->textVerts[textIndex2 - 1];
            Point vt3 = mesh->textVerts[textIndex3 - 1];
            Point vt4 = mesh->textVerts[textIndex4 - 1];

            textureBuffer.push_back(vt1.x); textureBuffer.push_back(1.0 - vt1.y);
            textureBuffer.push_back(vt2.x); textureBuffer.push_back(1.0 - vt2.y);
            textureBuffer.push_back(vt3.x); textureBuffer.push_back(1.0 - vt3.y);
            textureBuffer.push_back(vt3.x); textureBuffer.push_back(1.0 - vt3.y);
            textureBuffer.push_back(vt4.x); textureBuffer.push_back(1.0 - vt4.y);
            textureBuffer.push_back(vt1.x); textureBuffer.push_back(1.0 - vt1.y);
        }
        else if (polySides == 3)
        {//its a triangle
            std::cout << "Error: RenderCore found a triangle\n";
        }
        else
        {//unhandled as of now
            std::cout << "Error: Unrecognized shape detected in render core (" << polySides << " sides)\n";
        }
    }

    //set model scale/trans/rotate matrix
    GameData.cameraList[0].translate(obj.x, obj.y, obj.z);
    GameData.cameraList[0].rot(obj.roll, obj.pitch, obj.yaw);
    GameData.cameraList[0].scale(obj.xscale, obj.yscale, obj.zscale);

    //set shader to default shader
    Shader.useObjShader();
    GLint texLoc = glGetUniformLocation(Shader.defaultProg, "objTexture");
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textureBook[0]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (gpuBuffer.size() - 1), &gpuBuffer[1], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (textureBuffer.size()), &textureBuffer[0], GL_STREAM_DRAW);

    glBindVertexArray (this->dynamicVAO);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    glDrawArrays(GL_TRIANGLES, 0, (gpuBuffer.size() - 1) / 3);
    //std::cout << (gpuBuffer.size() - 1) / 3 << "\n";

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray (0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
        //Print gpuBuffer
        /*for (int i = 1; i < gpuBuffer.size(); i++)
                {
                    std::cout << gpuBuffer[i];
                    std::cout << ",";
                    if ((i % 3) == 0 )
                        std::cout << "\n";
                }
        std::cout << "\n\n";*/
    gpuBuffer.clear();

    Shader.useDefaultShader();
}

void RenderCore::renderAllEntities()
{
    for (unsigned int entity = 0; entity < GameData.entityList.size(); entity++)
    {
        this->renderGameObject(GameData.entityList[entity]);
    }
}

void RenderCore::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->renderAllEntities();

    SDL_GL_SwapWindow(sdlWindow);
}
