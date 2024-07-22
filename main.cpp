#include<iostream>
#include "Screen.hpp"
#include<vector>
#include<random>
#include<windows.h>
#include<chrono>
#include "Point.hpp"
#include "GameField.hpp"
#include<map>

int main(int argc, char *argv[])
{
    int size = 450; // размер игрового поля
    Graphics::Screen test; // объект для отображения игрового поля
    test.Init();
    Core::GameField field(size, test.GetWindowId()); // объект игрового поля
    while(true)
    {
        std::vector<std::vector<int>> f = field.DoTick(); //  Обрабатываем один игровой тик и берем состояние всех  частиц на игровом поле
        std::map<RGBColor, std::vector<Point>> pixels; // Это то, что мы передадим в отрисовку(координаты и цвета частиц соответсвенно)
        RGBColor color; 
        for(int i=0; i < size; ++i)
        {
            for(int j =0; j < size; ++j)
                {
                    if(f[i][j]!= VOID) // отрисовываем только непустые клетки
                    {
                        if(f[i][j] == WATER)
                            color = RGBColor{0, 0, 1.f};
                        else if(f[i][j] == SAND)
                            color = RGBColor{0.992F, 0.913f, 0.062f};
                        else if(f[i][j] == WOOD)
                            color = RGBColor{0.640F, 0.454F, 0.286F};
                        else if(f[i][j] == VIRUS)
                            color = RGBColor{0.309F, 0.0F, 0.439F};
                        else if(f[i][j] == FIRE)
                            color = RGBColor{0.99F, (1.f/255.f)*(rand() % 255), 0.0F};
                        pixels[color].push_back(Point{i, j});
                    }
                }
        }
        test.Display(size, pixels); // отображаем один игровой тик

    }
}

/*
P.S
В проекте есть утечка, кажется не одна, кажется много, что с этим делать - не знаю
*/