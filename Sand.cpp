#include "Sand.hpp"

namespace Particles
{
    Sand::Sand()
    {
        _pos =  Point{.0, .0};
    }
    Sand::Sand(Point pos)
    {
        _pos = pos;
    }
    void Sand::DoTick()
    {
        _pos.y-=1;
    }
}