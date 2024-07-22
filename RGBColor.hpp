#pragma once
// вспомогательная структура для цвета
struct RGBColor
{
    float r, g, b;
    // нужен исключительно формально, чтобы можно было засунуть в контейнер с сортировкой
    bool operator<(const RGBColor& c) const 
    {
        return r+g+b>c.r+c.g+c.b;
    }
};