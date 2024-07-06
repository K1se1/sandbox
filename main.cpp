#include<iostream>
#include "Screen.hpp"
#include<vector>
#include<random>
#include<windows.h>
#include "Point.hpp"
#include "GameField.hpp"


void add_cube(int size, Core::GameField& field, int material)
{
    for(int i = size/2-size/32; i < size/2+size/32;++i)
    {
        for(int j = size/2-size/32; j < size/2+size/32;++j)
        {
        field.AddParticle(material, Point{i , j});
        }
    }
}

int main(int argc, char *argv[])
{
    int count = 0;
    int size = 500;
    Core::GameField field(size);
    add_cube(size, field, WATER);
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
        if(count == 1000)
        {
            add_cube(size,field, WATER);
            count = 0;
        }
        std::vector<std::vector<int>> f = field.DoTick();       
        std::vector<Point> pixels;
        for(int i=0; i < size; ++i)
        {
            for(int j =0; j < size; ++j)
                {
                    if(f[i][j]!= VOID) 
                    {
                        pixels.push_back(Point{i, j});
                    }
                }
        }
        test.Display(size, pixels);
        count++;
        Sleep(7);
    }
}