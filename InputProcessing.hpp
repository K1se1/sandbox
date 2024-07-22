#include<GLFW/glfw3.h>
#include<string>
#include "Point.hpp"
//Класс для обработки ввода
class InputProcessing
{
    private:
    GLFWwindow *window;
    std::pair<double, double> CursorPos;
    int LastPressedKey;
    bool MouseState;
    public:
    InputProcessing(GLFWwindow* window);
    std::pair<double, double> GetCursorPos();
    int GetLastKey();
    bool GetMouseState();
    void SetMouseState(bool flag);
    void SetCursorPos(double x, double y);
    void SetLastKey(int key);
};