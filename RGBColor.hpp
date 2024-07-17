#pragma once
struct RGBColor
{
    float r, g, b;
    bool operator<(const RGBColor& c) const // магический оператор, сделан очень странно, но если что-нибудь поменять - все сломается
    {
        return r+g+b>c.r+c.g+c.b;
    }
};