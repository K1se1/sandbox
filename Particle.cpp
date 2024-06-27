#include "Particle.hpp"

namespace Particles
{

Particle::Particle(): _pos{.0, .0}
{

}

Particle::Particle(Point pos): _pos{pos}
{

}

float Particle::GetMass() const
{
    return _mass;
}

float Particle::GetDensity() const
{
    return _density;
}

Point Particle::GetPos() const 
{
     return _pos;
}

RGBColor Particle::GetColor() const 
{
    return _color;
}

}