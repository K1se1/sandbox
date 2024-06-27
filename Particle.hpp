#include "Point.hpp"
#include "RGBColor.hpp"
namespace Particles
{

class Particle
{
    protected:
    const float _density = 1.;
    const float _mass = 1.;
    const RGBColor _color{1, 1, 1};
    Point _pos;
    public:
    Particle();
    Particle(Point pos);
    virtual ~Particle() = 0;
    virtual void DoTick() = 0;
    inline Point GetPos() const;
    inline float GetMass() const;
    inline float GetDensity() const;
    inline RGBColor GetColor() const;
};

}