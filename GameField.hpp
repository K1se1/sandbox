#define SAND 5
#define VOID 0
#define WATER 2
#define WOOD 6
#define ACID 
#define VIRUS 30
#define FIRE 31
#include<vector>
#include<random>
#include<set>
#include<GLFW/glfw3.h>
#include "InputProcessing.hpp"
#include "Point.hpp"
// основной класс с логикой игры 
namespace Core
{
    class GameField
    {
        private:
        InputProcessing InputState; // объект для считывания нажатия клавиш, мыши 
        std::vector<std::vector<int>> _GameFieldArr; // игровок поле
        std::vector<std::vector<int>> _NoActiveTicks; // массив активности частиц(используется для оптимизации)
        std::set<Point> _ActiveParticles; // множество активных частиц
        int _size; //  размер игрового поля
        public:
        GameField(GLFWwindow* window); 
        GameField(const int& size, GLFWwindow* window);
        void AddParticle(int particle, const Point& coords); // функия добавления частицы
        std::vector<std::vector<int>> DoTick(); // игровой тик
        void HardUpdate(); // Делает каждую частицу - активной
        int GetSize(); // принимаем размер
        ~GameField();

    };
}


/*
P.S
Активные частицы - те, которые еще могут совершить какое-то дейстиве, к примеру песок упасть, или осыпаться и т.п
*/