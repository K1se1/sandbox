#include<iostream>
#include "Screen.hpp"
#include<vector>
#include<random>
#include<windows.h>
#include<chrono>
#include "Point.hpp"
#include "GameField.hpp"
#include<map>

void add_cube(int size, Core::GameField& field, int material)
{
    int r = size/2;//rand() % size-(size/32);
    for(int i = r-size/128; i < r+size/128;++i)
    {
        for(int j = size/2-size/128; j < size/2+size/128;++j)
        {
        field.AddParticle(material, Point{i , j});
        }
    }
}

int main(int argc, char *argv[])
{
    int count = 0;
    int size = 700;
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
    glfwSetWindowUserPointer(test.GetWindowId(), &field);
    glfwSetMouseButtonCallback(test.GetWindowId(),[](GLFWwindow* window, int button, int action, int mods)
    {
        Core::GameField* w = static_cast<Core::GameField*>(glfwGetWindowUserPointer(window));
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            w->SetMouseState(false);

        if(w->GetMouseState() || button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            w->SetMouseState(true);
        
    });
    glfwSetCursorPosCallback(test.GetWindowId(), [](GLFWwindow* window, double xPos, double yPos)
    {
        Core::GameField* w = static_cast<Core::GameField*>(glfwGetWindowUserPointer(window));
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        x/=1920.0f;
        x*=w->GetSize();
        std::cout << y << "\n";
        y/=1080.0f;
        y*=w->GetSize()*(1080.0f/1920.0f);
        std::cout << y << "\n";
        y+=(w->GetSize()*(1.0f -1080.0f/1920.0f));
        std::cout << y << "\n";
        w->_LastCursorPosition.x = x;
        w->_LastCursorPosition.y = y;
        
    });
    while(true)
    {
        if(test.isClosed()) break;
        if(count % 10 == 0)
        {
            add_cube(size,field, WATER);
        }
        if(count  > 1002)
        {
            count--;
        }
         auto  now = std::chrono::high_resolution_clock::now();
        // Тут пишем нужные вычисления
        std::vector<std::vector<int>> f = field.DoTick();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now);
       // std::cout << "Time to process : " << elapsed.count() << "ms.\n";
        std::map<RGBColor, std::vector<Point>> pixels;
        RGBColor color;
        for(int i=0; i < size; ++i)
        {
            for(int j =0; j < size; ++j)
                {
                    if(f[i][j]!= VOID) 
                    {
                        if(f[i][j] == WATER)
                            color = RGBColor{0, 0, 1.f};
                        else if(f[i][j] == SAND)
                            color = RGBColor{0.992F, 0.913f, 0.062f};
                        else if(f[i][j] == WOOD)
                            color = RGBColor{148, 123, 0};
                        pixels[color].push_back(Point{i, j});
                    }
                }
        }
        now = std::chrono::high_resolution_clock::now();
        test.Display(size, pixels);
         elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now);
        // std::cout << "Time to display : " << elapsed.count() << "ms.\n";
        count++;

    }
}