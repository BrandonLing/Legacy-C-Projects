#include "RenderCore.h"

void RenderCore::init()
{
    //Init vars
    this->windowTitle = "Polar Academy";

    //init SDL2
    bool success1 = SDL_Init(SDL_INIT_VIDEO);
    this->sdlWindow = SDL_CreateWindow(this->windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, SDL_WINDOW_OPENGL);
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
}

void RenderCore::quit()
{
    SDL_GL_DeleteContext(this->glContext);
    SDL_Quit();
    this->sdlWindow = NULL;
}

void RenderCore::glRefreshViewport()
{
    SDL_GetWindowSize(this->sdlWindow, &(this->windowWidth), &(this->windowHeight));
    glViewport(-(this->windowWidth), -(this->windowHeight), (this->windowWidth) * 2, (this->windowHeight) * 2);
    std::cout << "Refresh viewport: " << (this->windowWidth) << "x" << (this->windowHeight) << "\n";
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

void RenderCore::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(sdlWindow);
}
