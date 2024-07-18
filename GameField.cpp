#include "GameField.hpp"
#include<iostream>
namespace Core 
{
    GameField::GameField(int size)
    {
        _size = size;
        _GameFieldArr.resize(_size);
        for(auto& row: _GameFieldArr)
        {
            row = std::vector<int>(_size, 0);
        }
    }
        GameField::GameField(): GameField(1000)
    {
    }
    void GameField::AddParticle(int particle, const Point& coords)
    {
        _ActiveParticles.insert(coords);
        
        _GameFieldArr.at(coords.x).at(coords.y) = particle;
    }
    std::vector<std::vector<int>> GameField::DoTick() 
    {
        Point temp = _LastCursorPosition;

        if(MouseIsPressed)
        {
            AddParticle(SAND, temp);
            if(temp.x < _size) temp.x+=1;
            AddParticle(SAND, temp);
            if(temp.y < _size) temp.y+=1;
            AddParticle(SAND, temp);
        }
        std::vector<std::vector<int>> OldGameFieldArr =_GameFieldArr;
        for(int k =0; k <1;++k)
        {
        std::set<Point> NewActiveParticles;
        OldGameFieldArr =_GameFieldArr;
        for(auto iter = _ActiveParticles.begin(); iter != _ActiveParticles.end(); ++iter)
        {
                int i = iter->x;
                int j = iter->y;
                switch(_GameFieldArr[i][j])
                { 
                case VOID:
                    break;
                case SAND:
                    if(j < _size-1 && _GameFieldArr[i][j+1] < SAND)
                    {
                        int r = rand() % 2 +1,s; // для неоднородного падения песка
                        for(s = 1; s <= r; ++s)
                        {
                        if(_GameFieldArr[i][j+s] >= SAND)
                            break;
                        }
                        s--;
                        int temp;
                        for(int r = 0; r <= s-1;++r)
                        {
                            temp = _GameFieldArr[i][j+r+1];
                            _GameFieldArr[i][j+r+1] = _GameFieldArr[i][j+r];
                            _GameFieldArr[i][j+r] = temp;
                            if(_GameFieldArr[i][j+r] != VOID)
                                NewActiveParticles.insert(Point{i, j+r});

                        }
                        // _GameFieldArr[i][j] = VOID;
                        // _GameFieldArr[i][j+s-1] = _GameFieldArr[i][j+s];
                        // _GameFieldArr[i][j+s] = SAND;
                       // if(_GameFieldArr[i][j+s-1] != VOID && _GameFieldArr[i][j+s-1] != SAND)
                         //   NewActiveParticles.insert(Point{i, j+s-1});
                        NewActiveParticles.insert(Point{i, j+s});
                    }
  
                    else if(j+1 < _size && i > 0 && i+1 < _size)
                    {
                        bool left = (_GameFieldArr[i-1][j+1] < SAND && _GameFieldArr[i-1][j] < SAND);
                        bool right = (_GameFieldArr[i+1][j+1] <SAND && _GameFieldArr[i+1][j] <SAND );
                        if(left && right)
                        {
                            int r =(rand()%2)*2;
                            _GameFieldArr[i][j] = _GameFieldArr[i+1-r][j+1] ; 
                            _GameFieldArr[i+1-r][j+1] = SAND;
                            NewActiveParticles.insert(Point{i+1-r, j+1});
                            NewActiveParticles.insert(Point{i, j});
                            

                        }
                        else if(left)
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i-1][j+1]; 
                            _GameFieldArr[i-1][j+1] = SAND; 
                            NewActiveParticles.insert(Point{i-1, j+1});
                            NewActiveParticles.insert(Point{i, j});
                        }
                        else if(right)
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i+1][j+1]; 
                            _GameFieldArr[i+1][j+1] = SAND;
                            NewActiveParticles.insert(Point{i+1, j+1});
                            NewActiveParticles.insert(Point{i, j});
                        }
                        else
                            NewActiveParticles.insert(Point{i, j});
                    }
                    else
                        NewActiveParticles.insert(Point{i, j});
                     break;
                case WATER:
                    if(j < _size-1 && _GameFieldArr[i][j+1] == VOID)
                    {
                        int r = rand() % 10 +1,s; // для неоднородного падения воды
                        for(s = 1; s < r; ++s)
                        {
                        if(_GameFieldArr[i][j+s] != VOID)
                            break;
                        }
                        _GameFieldArr[i][j] = VOID;
                        _GameFieldArr[i][j+s-1] = WATER;
                        NewActiveParticles.insert(Point{i, j+s-1});
                    }
                    else if(i > 0 && i+1 < _size &&  (_GameFieldArr[i][j+1] != VOID || j < _size-1))
                        {
                            int r  =_size, l = _size;
                            bool prioretyleft = false;
                            bool prioretyright = false;
                            bool left = (_GameFieldArr[i-1][j] == VOID);
                            bool right = (_GameFieldArr[i+1][j] == VOID);
                            if(left && right)
                            {
                                for(int t = 0; t < i; ++t)
                                {
                                if(_GameFieldArr[i-t][j+1] == VOID)
                                {
                                    l =  t;
                                    break;
                                }
                                }
                                for(int t = 0; t < _size-i; ++t)
                                {
                                    if(_GameFieldArr[i+t][j+1] == VOID)
                                    {
                                        r = t;
                                        break;
                                    }
                                }
                                int s = 1;
                                int down = 0;
                                if(l >= r)
                                    prioretyleft = true;
                                else
                                    prioretyright = true;
                                if(prioretyleft  || ( prioretyleft &&  prioretyright))
                                {
                                for(s = 2; s <= 6; ++s)
                                {
                                    if(i+s >= _size-1 ||_GameFieldArr[i+s][j+down] != VOID)
                                        break;
                                    if(j+down+1 < _size-1  && _GameFieldArr[i+s][j+1+down] == VOID)
                                    {
                                        down++;
                                    }
                                }
                                s-=1;
                                }
                                else if(prioretyright)
                                {
                                for(s = 2; s <= 6; ++s)
                                {
                                    if(i-s <= 0 ||_GameFieldArr[i-s][j+down] != VOID)
                                        break;
                                    if(j+down+1 <= _size-1  && _GameFieldArr[i-s][j+1+down] == VOID)
                                    {
                                        down++;
                                    }
                                }
                                s-=1;
                                }
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i+(((prioretyleft)-(prioretyright)-( prioretyleft &&  prioretyright))*s)][j+down] = WATER;
                                NewActiveParticles.insert(Point{i+(((prioretyleft)-(prioretyright)-( prioretyleft &&  prioretyright))*s), j+down}); 
                            }
                            else if(left)
                            {
                                int s =1 , down = 0;
                                for(s = 2; s <= 6; ++s)
                                {
                                    if(i-s <= 0 ||_GameFieldArr[i-s][j+down] != VOID)
                                        break;
                                    if(j+down+1 <= _size-1  && _GameFieldArr[i-s][j+1+down] == VOID)
                                    {
                                        down++;
                                    }
                                }
                                s-=1;
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i-s][j+down] = WATER; 
                                NewActiveParticles.insert(Point{i-s, j+down});
                            }
                            else if(right)
                            {
                                int s = 1, down = 0;
                                for(s = 2; s <= 6; ++s)
                                {
                                    if(i+s >= _size-1 ||_GameFieldArr[i+s][j+down] != VOID)
                                        break;
                                    if(j+down+1 <= _size-1  && _GameFieldArr[i+s][j+1+down] == VOID)
                                    {
                                        down++;
                                    }
                                }
                                s-=1;
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i+s][j+down] = WATER;
                                NewActiveParticles.insert(Point{i+s, j+down});
                            }
                            else
                               NewActiveParticles.insert(Point{i, j});
                        }
                        else
                           NewActiveParticles.insert(Point{i, j});
                        break;
                case VIRUS:
                    {
                    NewActiveParticles.insert(Point{i, j});
                    if(rand() % 3 == 0)
                        break;
                    int s = rand() % 3 -1;
                    int r = rand() % 3 -1;
                    if(i+s < _size && i+s >=0 && i+r < _size && i+r >=0 && _GameFieldArr[i+s][j+r] != VOID && _GameFieldArr[i+s][j+r] != VIRUS)
                                _GameFieldArr[i+s][j+r] = VIRUS;
                    break;
                    }
                case FIRE:
                    if(rand() % 2  == 0)
                    {
                        _GameFieldArr[i][j] = VOID;
                        break;
                    }
                    if(j-1 >= 0)
                        _GameFieldArr[i][j-1] = FIRE;
                    NewActiveParticles.insert(Point{i, j});
                    NewActiveParticles.insert(Point{i, j-1});
                    break;
                    



            }
        }
        std::cout << "\nParticles: " << NewActiveParticles.size() << " \n";
        _ActiveParticles = std::move(NewActiveParticles);
        }
        return _GameFieldArr;
    }
    
    GameField::~GameField()
    {}
    void GameField::HardUpdate()
    {
        for(int i =0; i <_size; ++i)
        {
            for(int j =0; j <_size; ++j)
            {
                if(_GameFieldArr[i][j] != VOID)
                    _ActiveParticles.insert(Point{i, j});
            }
        }
    }
    void GameField::Cursor_Position_Callback(GLFWwindow* window, double xPos, double yPos)
    {
        _LastCursorPosition.x = xPos;
        _LastCursorPosition.y = yPos;
    }
    void GameField::Mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        _LastCursorPosition.x = x;
        _LastCursorPosition.y= y;
        std::cout << _LastCursorPosition.x;
    }
    }
    void GameField::SetMouseState(bool flag)
    {
        MouseIsPressed = flag;
    }
    bool GameField::GetMouseState()
    {
        return MouseIsPressed;
    }
    int GameField::GetSize()
    {
        return _size;
    }
}