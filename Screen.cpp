#include<iostream>
#include "Screen.hpp"
#include <windows.h>
namespace Graphics
{
    Screen::Screen(): _height(1080), _width(1920), _color{0.07f, 0.13f, 0.17f}, _name("Window"), _gameSize(400)
    {
        GLfloat quadsSides = (2.0f / _gameSize); // сторона квадрата
        GLfloat ratio = GLfloat(_width)/_height; //  чтобы стороны были пропорциональны
        quadVert = new GLfloat[12]{-1.0f, ratio*2.f-1.f- (quadsSides*ratio), 0.0f, // левый нижний
                            -1.0f, ratio*2.f-1.f, 0.0f, // левый верхний
                            -1.0f+quadsSides, ratio*2.f-1.f, 0.0f, // правый верхний
                            -1.0f+quadsSides,  ratio*2.f-1.f-(quadsSides*ratio), 0.0f}; // правый нижний
        _vertmap.resize(_gameSize);
        for(int x = 0; x < _gameSize; ++x)
        {
            _vertmap[x].resize(_gameSize);
            for(int y  =0; y < _gameSize; ++y)
            {
                _vertmap[x][y] = new GLfloat[3] {quadsSides*x, -quadsSides*y*ratio, 0.0f}; // смещение
            }
        }
    }
    Screen::Screen(int height, int width, std::string name, RGBColor& color, unsigned int gameSize):  _height(height), _width(width), 
                                                                                _color{color}, _name(name), _gameSize(gameSize)
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
        shader.Activate();

    }

    void Screen::DrawQuad(int x, int y, int gameSize, RGBColor color)
    {
        shader.SetColor(color);
        VBO vbo(_vertmap[x][y], 12*sizeof(GLfloat)); 
        vao.LinkVBO(vbo, 1, 0);
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vbo.Delete();
    }

    void Screen::Display(int gameSize, std::vector<std::pair<Point, RGBColor>> pixels)
    {
        

        GLfloat* translations = new GLfloat[pixels.size()*3];
        for(int i =0; i < pixels.size()*3; i+=3)
        {
            for(int j =0; j < 3; ++j)
                translations[i+j] = _vertmap[pixels[i/3].first.x][pixels[i/3].first.y][j]; //Супер опасно, беру указатель с приватного члена класса, главное ниче не сломать 
        }
        if (glfwWindowShouldClose(_window)) // Если окно закрывают - завершаем
	    {
            glfwDestroyWindow(_window);
            _window = NULL;
		    glfwTerminate();
	    }
        glClearColor(_color.r, _color.g, _color.b, 1.0f); // установка цвета фона
        glClear(GL_COLOR_BUFFER_BIT); 
        VBO iVbo(translations, 3*sizeof(GLfloat)*pixels.size());
        VBO quadVbo(quadVert, 12*sizeof(GLfloat));
        vao.Bind();
        vao.LinkVBO(quadVbo, 1, 0); 
        vao.LinkVBO(iVbo, 0, 1);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, pixels.size());
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.UnBind();
        // for(const auto& pixel: pixels) // проходимся по координатам каждого пикселя в массиве
        // {
        //     DrawQuad(pixel.first.x, pixel.first.y, gameSize, pixel.second); // рисуем пиксель
        // }
        glfwSwapBuffers(_window); // меняем местами передний и задний буффер
        glfwPollEvents();
        iVbo.Delete();
        quadVbo.Delete();
        delete[] translations;
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