#pragma once
#include "C:/msys64/mingw64/lib/glad/include/glad/glad.h"
#include<GLFW/glfw3.h>
#include<string> 
#include<cmath>
#include<vector>
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "Point.hpp"
#include "RGBColor.hpp"
namespace Graphics
{
    class Screen
    {
        private:
        GLFWwindow* _window; // дескриптор окна
        int _height, _width;
        std::string _name; // название окна
        RGBColor _color; // цвет фона
        VAO vao; // массив вершин
        EBO ebo; //  буффер индексов
        Shader shader; // шейдеры
        void DrawQuad(int x, int y, int gameSize); // отрисовываем квадрат по координатам
        public:
        Screen();
        Screen(int height, int width, std::string name, RGBColor &color);
        ~Screen();
        void Init(); // инициализация окна
        void Display(int gameSize, std::vector<Point> pixels); // рисуем один кадр
        bool isClosed(); // закрыто ли окно
    };
}