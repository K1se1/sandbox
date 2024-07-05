#include<iostream>
#include "Screen.hpp"
#include<vector>
#include<random>
#include<windows.h>
#include "Point.hpp"
#include "GameField.hpp"
int main(int argc, char *argv[])
{
    int size = 400;
    Core::GameField field(size);
    for(int i = size/2-size/24; i < size/2+size/24;++i)
    {
        for(int j = size/2-size/6; j < size-size/8;++j)
        {
        field.AddParticle(FSAND, Point{i , j});
        }
    }
    Graphics::Screen test;
    test.Init();
    while(true)
    {
        if(test.isClosed()) break; 
        std::vector<std::vector<int>> f = field.DoTick();       
        std::vector<Point> pixels;
        for(int i=0; i < size; ++i)
        {
            for(int j =0; j < size; ++j)
                {
                    if(f[i][j]!= VOID) pixels.push_back(Point{i, j});
                }
        }
        Sleep(100);
        test.Display(size, pixels);
    }
}