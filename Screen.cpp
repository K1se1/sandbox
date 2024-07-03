#include<iostream>
#include "Screen.hpp"
#include <windows.h>
namespace Graphics
{
    Screen::Screen(): _height(1080), _width(1920), _color{0.07f, 0.13f, 0.17f}, _name("Window")
    {

    }
    Screen::Screen(int height, int width, std::string name, RGBColor& color):  _height(height), _width(width), 
                                                                                _color{color}, _name(name)
        {

                                                                                }
    void Screen::Init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DECORATED, false); // окно без рамок

        _window = glfwCreateWindow(_width, _height, "SandBox", NULL, NULL);  // создание окна
        if(_window == NULL)
        {
            std::cout << "Failed create the window" << std::endl; // если не открылось аварийно завершаем
            glfwTerminate();
        }
        glfwMakeContextCurrent(_window); // вводим окно в использование
        gladLoadGL();
        glViewport(0, 0, _width, _height); 
        shader.Init("C:/sandbox/default.vert", "C:/sandbox/default.frag"); // подключаем шейдеры
        vao.Init();  // инициализируем массив вершин
        GLuint indices[] = {0, 1, 2,
                            0, 2, 3 };
        vao.Bind();
        ebo.Init(indices, sizeof(indices)); // инициализируем буффер обхода индексов 

    }

    void Screen::DrawQuad(int x, int y, int gameSize)
    {
        GLfloat quadsSides = (2.0f / gameSize); // сторона квадрата
        GLfloat ratio = GLfloat(_width)/_height; //  чтобы стороны были пропорциональные
        GLfloat vertices[] = {-1.0f+(quadsSides*x), ratio*2.f-1.f- (quadsSides*(y+1)*ratio), 0.0f, // левый нижний
                            -1.0f+(quadsSides*x), ratio*2.f-1.f- (quadsSides*y*ratio), 0.0f, // левый верхний
                            -1.0f+(quadsSides*(x+1)), ratio*2.f-1.f- (quadsSides*y*ratio), 0.0f, // правый верхний
                            -1.0f+(quadsSides*(x+1)),  ratio*2.f-1.f- (quadsSides*(y+1)*ratio), 0.0f}; // правый нижний
        VBO vbo(vertices, sizeof(vertices)); 
        vao.LinkVBO(vbo, 0);
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vbo.Delete();
    }

    void Screen::Display(int gameSize, std::vector<Point> pixels)
    {

        if (glfwWindowShouldClose(_window)) // Если окно закрывают - завершаем
	    {
            glfwDestroyWindow(_window);
            _window = NULL;
		    glfwTerminate();
	    }
        glClearColor(_color.r, _color.g, _color.b, 1.0f); // установка цвета фона
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Activate(); // активируем шейдеры
        for(const auto& pixel: pixels) // проходимся по координатам каждого пикселя в массиве
        {
            DrawQuad(pixel.x, pixel.y, gameSize); // рисуем пиксель
        }
        glfwSwapBuffers(_window); // меняем местами передний и задний буффер
        glfwPollEvents();
        Sleep(16); //  ограничение частоты кадров
    }
    Screen::~Screen()
    {
        glfwDestroyWindow(_window); // уничтожаем окно
        glfwTerminate(); // завершаем glfw
    }

    bool Screen::isClosed() 
    {
        return !_window;
    }
}