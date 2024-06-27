#include<iostream>
#include "Screen.hpp"

namespace Graphics
{
    Screen::Screen(): _height(800), _width(800), _color{0.07f, 0.13f, 0.17f}, _name("Window") {}
    Screen::Screen(int height, int width, std::string name, RGBColor color):  _height(height), _width(width), 
                                                                                _color{color}, _name(name)   {}
    void Screen::Init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    }
    void Screen::Display()
    {
        _window = glfwCreateWindow(_height, _width, "SandBox", NULL, NULL);
        if(_window == NULL)
        {
            std::cout << "Faild create the window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(_window);
        glViewport(0, 0, 800, 800);
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(_window); 
         while(!glfwWindowShouldClose(_window))
        {
            glfwPollEvents();
        }
    }
    Screen::~Screen()
    {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
}