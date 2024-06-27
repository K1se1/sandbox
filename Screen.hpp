#pragma once
#include "C:/msys64/mingw64/lib/glad/include/glad/glad.h"
#include<GLFW/glfw3.h>
#include<string> 
#include<cmath>
#include "RGBColor.hpp"
namespace Graphics
{
    class Screen
    {
        private:
        GLFWwindow* _window;
        int _height, _width;
        std::string _name;
        RGBColor _color;
        const char* _vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

        const char* _fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
        "}\n\0";
        public:
        Screen();
        Screen(int height, int width, std::string name, RGBColor color);
        ~Screen();
        void Init();
        void Display();
    };
}