#define SAND 5
#define FSAND 4
#define VOID 0
#define WATER 2
#define FWATER 1
#define WOOD 6
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