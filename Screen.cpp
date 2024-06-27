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
            std::cout << "Faild create the window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(_window);
        gladLoadGL();
        glViewport(0, 0, 800, 800);
        //Обрабатываем шейдеры
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // вершинныЙ шейдер
        glShaderSource(vertexShader, 1, &_vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // фрагментный шейдер
        glShaderSource(fragmentShader, 1, &_fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
   
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glLinkProgram(shaderProgram);

        GLuint VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);


        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0 );
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

         while(!glfwWindowShouldClose(_window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
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