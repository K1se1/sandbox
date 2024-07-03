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
    std::string GetFileContent(std::string filename);
    public:
    Shader();
    void Init(std::string vertFile, std::string fragFile);
    void Activate();
    void Delete();
    GLuint GetID();



};

}