#include "ShaderCore.h"

void ShaderCore::init()
{
    this->loadDefaultShaders("default");
    this->loadTextShaders("text");
    this->loadBackgroundShaders("background");
    this->loadTileShaders("tile");

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
            for (unsigned int i = 0; i < errorLog.size(); i++)
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

bool ShaderCore::loadTextShaders(std::string shaderName)
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

        this->textvShader = glCreateShader(GL_VERTEX_SHADER);
        const char *shaderCSrc = shaderSource.c_str();
        glShaderSource(textvShader, 1, &shaderCSrc, NULL);
        glCompileShader(textvShader);
            GLint isCompiled = 0;
            glGetShaderiv(this->textvShader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(this->textvShader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(this->textvShader, maxLength, &maxLength, &errorLog[0]);

                // Provide the infolog in whatever manor you deem best.
                std::cout << "Shader2\n";
                for (unsigned int i = 0; i < errorLog.size(); i++)
                {
                    std::cout << errorLog[i];
                }

                // Exit with failure.
                glDeleteShader(this->textvShader); // Don't leak the shader.
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

        this->textfShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char *shaderCSrc = shaderSource.c_str();
        glShaderSource(textfShader, 1, &shaderCSrc, NULL);
        glCompileShader(textfShader);
            GLint isCompiled = 0;
            glGetShaderiv(this->textfShader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(this->textfShader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(this->textfShader, maxLength, &maxLength, &errorLog[0]);

                // Provide the infolog in whatever manor you deem best.
                std::cout << "Shader3\n";
                for (unsigned int i = 0; i < errorLog.size(); i++)
                {
                    std::cout << errorLog[i];
                }

                // Exit with failure.
                glDeleteShader(this->textfShader); // Don't leak the shader.

            }

    }
    else
    {
        fshaderFile.close();
        return false;
    }
    this->textProg = glCreateProgram();
    glAttachShader(this->textProg, this->textvShader);
    glAttachShader(this->textProg, this->textfShader);
    glLinkProgram(this->textProg);

        //Error checking
        GLint isLinked = 0;
        glGetShaderiv(this->textvShader, GL_LINK_STATUS, &isLinked);
        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(this->textvShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(this->textvShader, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            //std::cout << "Shader5\n";
            for (unsigned int i = 0; i < errorLog.size(); i++)
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

bool ShaderCore::loadBackgroundShaders(std::string shaderName)
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

        this->backgroundvShader = glCreateShader(GL_VERTEX_SHADER);
        const char *shaderCSrc = shaderSource.c_str();
        glShaderSource(backgroundvShader, 1, &shaderCSrc, NULL);
        glCompileShader(backgroundvShader);
            GLint isCompiled = 0;
            glGetShaderiv(this->backgroundvShader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(this->backgroundvShader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(this->backgroundvShader, maxLength, &maxLength, &errorLog[0]);

                // Provide the infolog in whatever manor you deem best.
                std::cout << "Shader0\n";
                for (unsigned int i = 0; i < errorLog.size(); i++)
                {
                    std::cout << errorLog[i];
                }

                // Exit with failure.
                glDeleteShader(this->backgroundvShader); // Don't leak the shader.
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

        this->backgroundfShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char *shaderCSrc = shaderSource.c_str();
        glShaderSource(backgroundfShader, 1, &shaderCSrc, NULL);
        glCompileShader(backgroundfShader);
            GLint isCompiled = 0;
            glGetShaderiv(this->backgroundfShader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(this->backgroundfShader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(this->backgroundfShader, maxLength, &maxLength, &errorLog[0]);

                // Provide the infolog in whatever manor you deem best.
                std::cout << "Shader1\n";
                for (unsigned int i = 0; i < errorLog.size(); i++)
                {
                    std::cout << errorLog[i];
                }

                // Exit with failure.
                glDeleteShader(this->backgroundfShader); // Don't leak the shader.

            }

    }
    else
    {
        fshaderFile.close();
        return false;
    }
    this->backgroundProg = glCreateProgram();
    glAttachShader(this->backgroundProg, this->backgroundvShader);
    glAttachShader(this->backgroundProg, this->backgroundfShader);
    glLinkProgram(this->backgroundProg);

        //Error checking
        GLint isLinked = 0;
        glGetShaderiv(this->backgroundvShader, GL_LINK_STATUS, &isLinked);
        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(this->backgroundvShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(this->backgroundvShader, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            for (unsigned int i = 0; i < errorLog.size(); i++)
            {
                std::cout << errorLog[i];
            }

        }

    return true;
}

bool ShaderCore::loadTileShaders(std::string shaderName)
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

        this->tilevShader = glCreateShader(GL_VERTEX_SHADER);
        const char *shaderCSrc = shaderSource.c_str();
        glShaderSource(tilevShader, 1, &shaderCSrc, NULL);
        glCompileShader(tilevShader);
            GLint isCompiled = 0;
            glGetShaderiv(this->tilevShader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(this->tilevShader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(this->tilevShader, maxLength, &maxLength, &errorLog[0]);

                // Provide the infolog in whatever manor you deem best.
                std::cout << "Shader0\n";
                for (unsigned int i = 0; i < errorLog.size(); i++)
                {
                    std::cout << errorLog[i];
                }

                // Exit with failure.
                glDeleteShader(this->tilevShader); // Don't leak the shader.
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

        this->tilefShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char *shaderCSrc = shaderSource.c_str();
        glShaderSource(tilefShader, 1, &shaderCSrc, NULL);
        glCompileShader(tilefShader);
            GLint isCompiled = 0;
            glGetShaderiv(this->tilefShader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(this->tilefShader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(this->tilefShader, maxLength, &maxLength, &errorLog[0]);

                // Provide the infolog in whatever manor you deem best.
                std::cout << "Shader1\n";
                for (unsigned int i = 0; i < errorLog.size(); i++)
                {
                    std::cout << errorLog[i];
                }

                // Exit with failure.
                glDeleteShader(this->tilefShader); // Don't leak the shader.

            }

    }
    else
    {
        fshaderFile.close();
        return false;
    }
    this->tileProg = glCreateProgram();
    glAttachShader(this->tileProg, this->tilevShader);
    glAttachShader(this->tileProg, this->tilefShader);
    glLinkProgram(this->tileProg);

        //Error checking
        GLint isLinked = 0;
        glGetShaderiv(this->tilevShader, GL_LINK_STATUS, &isLinked);
        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(this->tilevShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(this->tilevShader, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            for (unsigned int i = 0; i < errorLog.size(); i++)
            {
                std::cout << errorLog[i];
            }

        }

    return true;
}



void ShaderCore::useDefaultShader()
{
    glUseProgram(this->defaultProg);

    //Set Uniform
    GLint loc = glGetUniformLocation(this->defaultProg, "modelviewproj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &(GameData.playerCam.modelviewproj)[0][0]);
}

void ShaderCore::useTextShader()
{
    glUseProgram(this->textProg);

    //Set Uniform
    GLint loc = glGetUniformLocation(this->textProg, "modelviewproj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &(GameData.playerCam.modelviewproj)[0][0]);

    GLint texLoc = glGetUniformLocation(this->textProg, "fontTexture");
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, ResourceData.FontSystem.fontBook[0]);
}

void ShaderCore::useGUITextShader()
{
    glUseProgram(this->textProg);

    //Set Uniform
    GLint loc = glGetUniformLocation(this->textProg, "modelviewproj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &(GameData.playerCam.modelviewproj)[0][0]);

    GLint texLoc = glGetUniformLocation(this->textProg, "fontTexture");
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, ResourceData.FontSystem.fontBook[0]);
}

void ShaderCore::useBGShader()
{
    glUseProgram(this->backgroundProg);

    GLint texLoc = glGetUniformLocation(this->backgroundProg, "bgTexture");
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ResourceData.SpriteData.bgBook[MapData.background]);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ShaderCore::useTileShader()
{
    glUseProgram(this->tileProg);

    //Set Uniform
    GLint loc = glGetUniformLocation(this->defaultProg, "modelviewproj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &(GameData.playerCam.modelviewproj)[0][0]);
}

void ShaderCore::update()
{
    GLint loc = glGetUniformLocation(this->defaultProg, "modelviewproj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &(GameData.playerCam.modelviewproj)[0][0]);
}


