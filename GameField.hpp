#define SAND 5
#define VOID 0
#define WATER 2
#define WOOD 6
#define ACID 
#define VIRUS 30
#define FIRE 31
#include<vector>
#include<random>
#include<set>
#include<GLFW/glfw3.h>

#include "Point.hpp"
namespace Core
{
    class GameField
    {
        private:
        std::vector<std::vector<int>> _GameFieldArr;
        std::set<Point> _ActiveParticles;
        int _size;
        bool MouseIsPressed =0;
        public:
        Point _LastCursorPosition;
        void Cursor_Position_Callback(GLFWwindow* window, double xPos, double yPos);
        void Mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods);
        GameField();
        GameField(int size);
        void AddParticle(int particle, const Point& coords);
        std::vector<std::vector<int>> DoTick();
        void HardUpdate();
        void SetMouseState(bool flag);
        bool GetMouseState();
        int GetSize();
        ~GameField();

    };
}