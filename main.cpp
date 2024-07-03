#include<iostream>
#include "Sand.hpp"
#include "Screen.hpp"
#include<vector>
#include<random>
#include "Point.hpp"
int main(int argc, char *argv[])
{
    int size = 700;
    Graphics::Screen test;
    test.Init();
    while(true)
    {
        if(test.isClosed()) break;        
        std::vector<Point> pixels;
        for(int i =0; i < size; i++)
        {
            pixels.push_back(Point{rand() % size, i});
        }
        test.Display(size, pixels);
    }
}