#include "ShaderCore.h"

void ShaderCore::init()
{
    this->loadDefaultShaders("default");

    this->useDefaultShader();
}

void ShaderCore::quit()
{

}

bool ShaderCore::loadDefaultShaders(std::string shaderName)
{
    std::string shaderSource;

    //Vertex Shader
    //const char* filename = "Shaders/default.vert";
    std::string filename = "Shaders/"; filename.append(shaderName.c_str()); filename.append(".vert");

    std::string nextLine;
    std::ifstream shaderFile (filename.c_str());
    if (shaderFile.is_open())
    {
        while ( getline(shaderFile, nextLine) )
        {
            shaderSource.append(nextLine);
            shaderSource.append("\n");
        }
        shaderFile.close();

        this->defaultvShader = glCreateShader(GL_VERTEX_SHADER);
        const char *shaderCSrc = shaderSource.c_str();
        glShaderSource(defaultvShader, 1, &shaderCSrc, NULL);
        glCompileShader(defaultvShader);

        GLint isCompiled = 0;
        glGetShaderiv(this->defaultvShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(this->defaultvShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(this->defaultvShader, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            std::cout << "Shader0\n";
            for (unsigned int i = 0; i < errorLog.size(); i++)
            {
                std::cout << errorLog[i];
            }

            // Exit with failure.
            glDeleteShader(this->defaultvShader); // Don't leak the shader.
        }
    }
    else
    {
        shaderFile.close();
        return false;
    }

    //Fragment Shader
    shaderSource.clear();
    filename = "Shaders/"; filename.append(shaderName.c_str()); filename.append(".frag");

    std::ifstream fshaderFile (filename.c_str());
    if (fshaderFile.is_open())
    {
        while ( getline(fshaderFile, nextLine) )
        {
            shaderSource.append(nextLine);
            shaderSource.append("\n");
        }
        fshaderFile.close();

        this->defaultfShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char *shaderCSrc = shaderSource.c_str();
        glShaderSource(defaultfShader, 1, &shaderCSrc, NULL);
        glCompileShader(defaultfShader);
            GLint isCompiled = 0;
            glGetShaderiv(this->defaultfShader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(this->defaultfShader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(this->defaultfShader, maxLength, &maxLength, &errorLog[0]);

                // Provide the infolog in whatever manor you deem best.
                std::cout << "Shader1\n";
                for (unsigned int i = 0; i < errorLog.size(); i++)
                {
                    std::cout << errorLog[i];
                }

                // Exit with failure.
                glDeleteShader(this->defaultfShader); // Don't leak the shader.

            }

    }
    else
    {
        fshaderFile.close();
        return false;
    }
    this->defaultProg = glCreateProgram();
    glAttachShader(this->defaultProg, this->defaultvShader);
    glAttachShader(this->defaultProg, this->defaultfShader);
    glLinkProgram(this->defaultProg);

        //Error checking
        GLint isLinked = 0;
        glGetShaderiv(this->defaultvShader, GL_LINK_STATUS, &isLinked);

        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(this->defaultvShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(this->defaultvShader, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            //std::cout << "Shader2\n";
            for (unsigned int i = 1; i < errorLog.size(); i++)
            {
                std::cout << errorLog[i];
            }

        }

    /*Print MVP Matrix
    std::cout << (this->modelviewproj[0][0]) << ", " << (this->modelviewproj[0][1]) << ", " << (this->modelviewproj[0][2]) << ", " << (this->modelviewproj[0][3]) << "\n";
    std::cout << (this->modelviewproj[1][0]) << ", " << (this->modelviewproj[1][1]) << ", " << (this->modelviewproj[1][2]) << ", " << (this->modelviewproj[1][3]) << "\n";
    std::cout << (this->modelviewproj[2][0]) << ", " << (this->modelviewproj[2][1]) << ", " << (this->modelviewproj[2][2]) << ", " << (this->modelviewproj[2][3]) << "\n";
    std::cout << (this->modelviewproj[3][0]) << ", " << (this->modelviewproj[3][1]) << ", " << (this->modelviewproj[3][2]) << ", " << (this->modelviewproj[3][3]) << "\n";
    */
    return true;
}

//This default shader is used to render the camera
void ShaderCore::useDefaultShader()
{
    glUseProgram(this->defaultProg);

    //restore default
    GameData.cameraList[0].restoreModelMatrix();

    //Set Uniform
    GLint loc = glGetUniformLocation(this->defaultProg, "modelviewproj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &(GameData.cameraList[0].modelviewproj)[0][0]);
}

//This default shader is used to render the camera
void ShaderCore::useObjShader()
{
    glUseProgram(this->defaultProg);

    //Set Uniform
    GLint loc = glGetUniformLocation(this->defaultProg, "modelviewproj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &(GameData.cameraList[0].modelviewproj)[0][0]);
}




