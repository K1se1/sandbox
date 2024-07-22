#pragma once
#include "../glad/glad.h"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include "RGBColor.hpp"
namespace Graphics
{

// класс для считывания и инициализации вершинного и фрагментного шейдеров
class Shader
{
    private:
    GLuint ID;
    GLint vertColorLocation;
    std::string GetFileContent(std::string filename);
    public:
    Shader();
    void Init(std::string vertFile, std::string fragFile);
    void Activate();
    void Delete();
    void SetColor(RGBColor color);
    GLuint GetID();



};

}