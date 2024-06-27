#include "Particle.hpp"


namespace Particles
{
    class Sand: public Particle         
    {
        protected:
        const RGBColor _color{255, 255, 0};
        public: 
        Sand();
        Sand(Point pos);
        ~Sand();
        void DoTick(); 

    };
}