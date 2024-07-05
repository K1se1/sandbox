#define SAND 3
#define FSAND 2
#define VOID 0
#include<vector>
#include<random>
#include "Point.hpp"
namespace Core
{
    class GameField
    {
        private:
        std::vector<std::vector<int>> _GameFieldArr;
        int _size;
        public:
        GameField();
        GameField(int size);
        void AddParticle(int particle, const Point& coords);
        std::vector<std::vector<int>> DoTick();
        ~GameField();

    };
}