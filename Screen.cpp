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
        GLfloat vertices[] = {-0.5f, -0.5f, 0.0f,
                            -0.5f, 0.5f, 0.0f,
                            0.5f, 0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f};
        GLuint indices[] = {0, 1, 2,
                            0, 2, 3 };
        _window = glfwCreateWindow(_height, _width, "SandBox", NULL, NULL);
        if(_window == NULL)
        {
            std::cout << "Failed create the window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(_window);
        gladLoadGL();
        glViewport(0, 0, 800, 800);
        //Обрабатываем шейдеры
        Shader shader("C:/sandbox/default.vert", "C:/sandbox/default.frag");

        VAO vao;
        vao.Bind();
        VBO vbo(vertices, sizeof(vertices));
        EBO ebo(indices, sizeof(indices));
        vao.LinkVBO(vbo, 0);
        vao.UnBind();
        vbo.UnBind();
        ebo.UnBind();

         while(!glfwWindowShouldClose(_window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            shader.Activate();
            vao.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glfwSwapBuffers(_window);
            glfwPollEvents();
        }
    }
    Screen::~Screen()
    {

        glfwDestroyWindow(_window);
        glfwTerminate();
    }
}