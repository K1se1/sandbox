#pragma once
#include<GLFW/glfw3.h>
#include<string> 
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
        public:
        Screen();
        Screen(int height, int width, std::string name, RGBColor color);
        ~Screen();
        void Init();
        void Display();
    };
}