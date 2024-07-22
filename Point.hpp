#pragma once
struct Point
{
    int x, y;
    bool operator<(const Point&p1) const // магический оператор, сделан очень странно, но если что-нибудь поменять - все сломается
    {
        return y<p1.x+p1.y;
    }
};