#include<iostream>
#include "Screen.hpp"
#include<vector>
#include<random>
#include<windows.h>
#include<chrono>
#include "Point.hpp"
#include "GameField.hpp"


void add_cube(int size, Core::GameField& field, int material)
{
    int r = size/2;//rand() % size-(size/32);
    for(int i = r-size/64; i < r+size/64;++i)
    {
        for(int j = size/2-size/64; j < size/2+size/64;++j)
        {
        field.AddParticle(material, Point{i , j});
        }
    }
}

int main(int argc, char *argv[])
{
    int count = 0;
    int size = 400;
    Core::GameField field(size);
    //add_cube(size, field, WATER);
     for(int i = size/2-size/3; i < size/2+size/3;++i)
    {
        for(int j = size/2+size/3; j < size/2+size/3+1;++j)
        {
        field.AddParticle(WOOD, Point{i , j});
        }
    }
    for(int i = 0; i < 10; ++i)
    {
        field.AddParticle(WOOD, Point{size/2-size/3 , size/2+size/3-i});
        field.AddParticle(WOOD, Point{size/2+size/3 , size/2+size/3-i});
    }
    Graphics::Screen test;
    test.Init();
    while(true)
    {
        if(test.isClosed()) break;
        if(count == 500)
        {
            add_cube(size,field, WATER);
            count = 0;
        }

         auto  now = std::chrono::high_resolution_clock::now();
        // Тут пишем нужные вычисления
        std::vector<std::vector<int>> f = field.DoTick();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now);
        std::cout << "Time to process : " << elapsed.count() << "ns.\n";
        std::vector<std::pair<Point, RGBColor>> pixels;
        RGBColor color;
        for(int i=0; i < size; ++i)
        {
            for(int j =0; j < size; ++j)
                {
                    if(f[i][j]!= VOID) 
                    {
                        if(f[i][j] == WATER)
                            color = RGBColor{0, 0, 255};
                        if(f[i][j] == SAND)
                            color = RGBColor{253, 233, 16};
                        if(f[i][j] == WOOD)
                            color = RGBColor{148, 123, 0};
                        pixels.push_back(std::pair(Point{i, j}, color));
                    }
                }
        }
        now = std::chrono::high_resolution_clock::now();
        test.Display(size, pixels);
         elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now);
         std::cout << "Time to display : " << elapsed.count() << "ns.\n";
        count++;

    }
}