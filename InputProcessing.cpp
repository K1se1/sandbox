#include "InputProcessing.hpp"

InputProcessing::InputProcessing(GLFWwindow* window)
{
    // Тут используется трюк, для использования кол-бэков внутри класса
    MouseState = false;
    LastPressedKey = 0;
    glfwSetWindowUserPointer(window, this); // Даем доступ к нашему классу внутри коллбэка
    // в коллбэк передаем лямбду
    glfwSetMouseButtonCallback(window,[](GLFWwindow* window, int button, int action, int mods) 
    {
        InputProcessing* w = static_cast<InputProcessing*>(glfwGetWindowUserPointer(window));
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            w->SetMouseState(false);

        if(w->GetMouseState() || button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            w->SetMouseState(true);
        
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
    {
        InputProcessing* w = static_cast<InputProcessing*>(glfwGetWindowUserPointer(window));
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        w->SetCursorPos(x, y);
    });
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
         InputProcessing* w = static_cast<InputProcessing*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS && key >= GLFW_KEY_0  && key <= GLFW_KEY_9 )
            w->SetLastKey(key);
    });
}


void InputProcessing::SetCursorPos(double x, double y)
{
    CursorPos.first =x;
    CursorPos.second = y;
}

void InputProcessing::SetLastKey(int key)
{
    LastPressedKey = key;
}

void InputProcessing::SetMouseState(bool flag)
{
    MouseState = flag;
}

bool InputProcessing::GetMouseState()
{
    return MouseState;
}

std::pair<double, double> InputProcessing::GetCursorPos()
{
    return CursorPos;
}


int InputProcessing::GetLastKey()
{
    return LastPressedKey;
}


