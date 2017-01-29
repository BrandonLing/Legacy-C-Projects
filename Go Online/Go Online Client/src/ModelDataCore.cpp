#include "ModelDataCore.h"

void ModelDataCore::init()
{
    this->loadAllObjects();

}

void ModelDataCore::quit()
{

}

void ModelDataCore::loadAllObjects()
{
    std::string searchDir = "Resources/Blender Data/";
    std::vector<std::string> fileListings = this->getFileListing(searchDir);
    for(unsigned int i = 0; i < fileListings.size(); i++)
    {//go through each file
        //Find filetype
        std::string filetype;
        std::string letter;
        for (unsigned int j = (fileListings[i].size() - 1); j >= 0; j--)
        {
            letter = fileListings[i][j];
            if (letter.compare(".")) //not a period
                filetype.insert(0, letter);
            else //is a period
                break;
        }

        if (!filetype.compare("obj")) //load model if file is obj
        {
            std::string dir = searchDir;
            dir.append(fileListings[i]);
            this->loadModel(dir);
        }
        //std::cout << filetype << "\n";
        //std::cout << fileListings[i] << "\n";
    }
}

std::vector<std::string> ModelDataCore::getFileListing(std::string directory)
{
    DIR*    dir;
    dirent* pdir;
    std::vector<std::string> files;

    dir = opendir(directory.c_str());

    while (pdir = readdir(dir))
    {
        files.push_back(pdir->d_name);
    }

    //std::cout << files.size() << " files found\n";
    return files;
}

int ModelDataCore::loadModel(std::string filename)
{
    //open .obj file
    std::ifstream myfile;
    myfile.open(filename.c_str());

    std::string line;
    ObjModel output;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            //Parse Data
            this->parseObjLine(line, output);
        }
        myfile.close();
    }
    else
    {
        std::cout << "Error: Can't find model file at " << filename << "\n";
    }
    //end obj file

    //open .mtl file
    //std::cout << "Found mat file: " << output.matLib << "\n";

    std::ifstream matfile;
    std::string fileDir = "Resources/Blender Data/";
    std::string matDestination = fileDir;
    matDestination.append(output.matLib);
    matfile.open(matDestination.c_str());

    std::string matline;
    if (matfile.is_open())
    {
        while (getline(matfile, matline))
        {
            //Parse Data
            this->parseMtlLine(matline, output);
        }
        matfile.close();
    }
    else
    {
        std::cout << "Error: Can't find model file at " << filename << "\n";
    }
    //end mtl file

    //load textures
    std::string textureDestination = fileDir;
    textureDestination.append(output.map_Kd);
    this->loadTexturefromPNG(textureDestination, output);
    //end textures

    //push mesh data onto library stack
    this->meshLibrary.push_back(output);
    return 0;
}

void ModelDataCore::loadTexturefromPNG(std::string filepath, ObjModel &obj)
{
    SDL_Surface *image;
    image = IMG_Load(filepath.c_str());

    if(!image) //Handle Error
    {
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
    else
    {
        int textureIndex = obj.textureBook.size();
        obj.textureBook.push_back(0); //create a texture. will be overwritten shortly
        glGenTextures(1, &(obj.textureBook[textureIndex]));

        glBindTexture(GL_TEXTURE_2D, obj.textureBook[textureIndex]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);

        //free memory
        SDL_FreeSurface(image);
        image = NULL;
    }

}

void ModelDataCore::parseMtlLine(std::string line, ObjModel &obj)
{
    //Print line
    //std::cout << line << "\n";

    //Get first word of line
    std::string firstWord;
    unsigned int i = 0;
    for (i = 0; i < line.size(); i++)
    {
        if (line[i] != ' ')
        {
            firstWord.push_back(line[i]);
        }
        else
        {
            break;
        }
    }

    if (firstWord.size() == 0)
    {
        //blank line
    }
    else if (!firstWord.compare("#")) //comment
    {

    }
    else if(!firstWord.compare("newmtl")) //material name
    {

    }
    else if(!firstWord.compare("Ns")) //phong specular component
    {

    }
    else if(!firstWord.compare("Ka")) //ambient color
    {

    }
    else if(!firstWord.compare("Kd")) //diffuse color
    {

    }
    else if(!firstWord.compare("Ks")) //specular color
    {

    }
    else if(!firstWord.compare("Ni")) //refraction index
    {

    }
    else if(!firstWord.compare("d")) //transparency
    {

    }
    else if(!firstWord.compare("illum")) //illumination value
    {

    }
    else if(!firstWord.compare("map_Kd")) //diffuse texture map
    {
        for (i = i+1; i<line.size(); i++)
        {
            obj.map_Kd.push_back(line[i]);
        }
    }
    else
    {//unhandled line
        std::cout << "Error: Unhandled line in mtl: " << line << "\n";
    }
}

void ModelDataCore::parseObjLine(std::string line, ObjModel &obj)
{
    //Print line
    //std::cout << line << "\n";

    //Get first word of line
    std::string firstWord;
    unsigned int i = 0;
    for (i = 0; i < line.size(); i++)
    {
        if (line[i] != ' ')
        {
            firstWord.push_back(line[i]);
        }
        else
        {
            break;
        }
    }

    //Continue rest of line and parse
    if (!firstWord.compare("#"))
    {
        obj.comments.push_back(line);
    }
    else if (!firstWord.compare("mtllib"))
    {
        for (i = i+1; i<line.size(); i++)
        {
            obj.matLib.push_back(line[i]);
        }
    }
    else if (!firstWord.compare("o"))
    {
        for (i = i+1; i<line.size(); i++)
        {
            obj.objectName.push_back(line[i]);
        }
    }
    else if (!firstWord.compare("v"))
    {
        //Extract the floats from the line
        std::string nextWord;
        std::vector<std::string> pointText;
        for (i = i+1; i<line.size(); i++)
        {
            if (line[i] != ' ')
            {//add letter to next word
                nextWord.push_back(line[i]);
            }
            else
            {//add next word to pointText
                pointText.push_back(nextWord);
                nextWord.clear();
            }
        }
        //add last word
        pointText.push_back(nextWord);
        nextWord.clear();

        float x = atof(pointText[0].c_str());
        float y = atof(pointText[1].c_str());
        float z = atof(pointText[2].c_str());
        Point vertex(x, y, z);

        obj.verts.push_back(vertex);
    }
    else if (!firstWord.compare("vn"))
    {
        //Extract the floats from the line
        std::string nextWord;
        std::vector<std::string> pointText;
        for (i = i+1; i<line.size(); i++)
        {
            if (line[i] != ' ')
            {//add letter to next word
                nextWord.push_back(line[i]);
            }
            else
            {//add next word to pointText
                pointText.push_back(nextWord);
                nextWord.clear();
            }
        }
        //add last word
        pointText.push_back(nextWord);
        nextWord.clear();

        float x = atof(pointText[0].c_str());
        float y = atof(pointText[1].c_str());
        float z = atof(pointText[2].c_str());
        Point vertex(x, y, z);

        obj.norms.push_back(vertex);
    }
    else if (!firstWord.compare("vt"))
    {
        //Extract the floats from the line
        std::string nextWord;
        std::vector<std::string> pointText;
        for (i = i+1; i<line.size(); i++)
        {
            if (line[i] != ' ')
            {//add letter to next word
                nextWord.push_back(line[i]);
            }
            else
            {//add next word to pointText
                pointText.push_back(nextWord);
                nextWord.clear();
            }
        }
        //add last word
        pointText.push_back(nextWord);
        nextWord.clear();

        float x = atof(pointText[0].c_str());
        float y = atof(pointText[1].c_str());
        float z = 0; //z value is not applicable to 2-d texture coordinates
        Point vertex(x, y, z);

        obj.textVerts.push_back(vertex);
    }
    else if (!firstWord.compare("usemtl"))
    {
        for (i = i+1; i<line.size(); i++)
        {
            obj.mat.push_back(line[i]);
        }
    }
    else if (!firstWord.compare("s"))
    {
        std::string nextWord;
        for (i = i+1; i<line.size(); i++)
        {
            nextWord.push_back(line[i]);
        }

        if (!nextWord.compare("off"))
        {
            obj.s = 0;
        }
        else
        {
            obj.s = 1;
        }
    }
    else if (!firstWord.compare("f"))
    {
        std::string v, vt, vn;
        int vi, vti, vni;
        Face facedata;
        int counter = 0; //keeps track if the string is on v/vn/vt - 1/2/3

        for (i = i+1; i<line.size(); i++)
        {
            if (line[i] == ' ')
            {
                //add data to obj
                vi = atoi(v.c_str());
                vti = atoi(vt.c_str());
                vni = atoi(vn.c_str());

                //convert data to face class
                facedata.vertex.push_back(vi);
                facedata.texture.push_back(vti);
                facedata.normal.push_back(vni);

                //clear for next vertex
                v.clear();
                vt.clear();
                vn.clear();
                counter = 0;
                continue;
            }
            else
            {
                if(line[i] != '/')
                {//character is a value
                    switch(counter)
                    {
                        case 0: //vertex
                        {
                            v.push_back(line[i]);
                            break;
                        }
                        case 1: //vtexture
                        {
                            vt.push_back(line[i]);
                            break;
                        }
                        case 2: //vnormal
                        {
                            vn.push_back(line[i]);
                            break;
                        }
                    }
                }
                else
                {
                    counter++;
                }
            }


        }

        //add last data entry to obj
        vi = atoi(v.c_str());
        vti = atoi(vt.c_str());
        vni = atoi(vn.c_str());

        //Convert data to face class
        facedata.vertex.push_back(vi);
        facedata.texture.push_back(vti);
        facedata.normal.push_back(vni);

        //set Data into obj
        obj.faces.push_back(facedata);
    }

    else
    {
        std::cout << "Unhandled Line in obj: " << line << "\n";
    }


    /*for (i = i+1; i<line.size(); i++)
    {
        //std::cout << line[i];
    }*/

}


