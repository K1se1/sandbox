#pragma once
#include "../glad/glad.h" // замеенить путь
#include<GLFW/glfw3.h>
#include<string> 
#include<cmath>
#include<vector>
#include<map>
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "Point.hpp"
#include "RGBColor.hpp"
// класс для отрисовки игрового поля
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
        std::vector<std::vector<GLfloat*>> _vertmap;
        GLfloat* quadVert;
        unsigned int _gameSize;
        public:
        Screen();
        Screen(int height, int width, std::string name, RGBColor &color, unsigned int gameSize);
        ~Screen();
        void Init(); // инициализация окна
        void Display(int gameSize, const std::map<RGBColor, std::vector<Point>>& pixels); // рисуем один кадр
        bool isClosed(); // закрыто ли окно
        GLFWwindow* GetWindowId();
    };
}