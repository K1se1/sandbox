#pragma once
#include "C:/msys64/mingw64/lib/glad/include/glad/glad.h"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

namespace Graphics
{

class Shader
{
    private:
    GLuint ID;
    std::string GetFileContent(const char* filename);
    public:
    Shader(const char* vertFile, const char* fragFile);
    void Activate();
    void Delete();
    GLuint GetID();



};

}