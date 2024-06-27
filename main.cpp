#include<iostream>
#include<GLFW/glfw3.h>
#include "Sand.hpp"
#include "Screen.hpp"

int main(int argc, char *argv[])
{
    Graphics::Screen test;
    test.Init();
    test.Display();
}