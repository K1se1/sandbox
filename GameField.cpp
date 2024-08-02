#include "GameField.hpp"
namespace Core 
{
    GameField::GameField(const int& size, GLFWwindow* window): InputState(window)
    {
        _size = size;
        _GameFieldArr.resize(_size);
        _NoActiveTicks.resize(_size);
        for(auto& row: _GameFieldArr)
        {
            row = std::vector<int>(_size, 0);
        }
        for(auto& row: _NoActiveTicks)
        {
            row = std::vector<int>(_size, 100);
        }
    }
        GameField::GameField(GLFWwindow* window): GameField(1000, window)
    {
    }
    void GameField::AddParticle(int particle, const Point& coords)
    {
        Point temp = coords;
        for(int i =-1; i <= 1; ++i )
        {
                for(int j =-1; j<=1; ++j)
                {
                    temp.x= coords.x+i;
                    temp.y = coords.y+j;
                    if(temp.x < _size && temp.x >=0 && temp.y < _size && temp.y>=0)
                                    _ActiveParticles.insert(temp);
                }
        }
        _GameFieldArr.at(coords.x).at(coords.y) = particle;
    }
    std::vector<std::vector<int>> GameField::DoTick() 
    {
        if(InputState.GetMouseState())
        {
        int material = SAND;
        switch(InputState.GetLastKey())
        {
            case GLFW_KEY_1:
                material = SAND;
                break;
            case GLFW_KEY_2:
                material = WATER;
                break;
            case GLFW_KEY_3:
                material = WOOD;
                break;    
            case GLFW_KEY_4:
                material = VIRUS;
                break;
            case GLFW_KEY_5:
                material = FIRE;
                break;
            case GLFW_KEY_0:
                material =VOIDP;
                break;
            default:
             material = SAND;
             break;
        }
        double x = InputState.GetCursorPos().first;
        double y = InputState.GetCursorPos().second;
        x/=1920.0f;
        x*=_size;
        y/=1080.0f;
        y*=_size*(1080.0f/1920.0f);
        y+=(_size*(1.0f -1080.0f/1920.0f));
        int  brushSize = 4;
        Point temp{int(x), int(y)};
        for(int i =-brushSize; i <= brushSize; ++i )
        {
                for(int j =-brushSize; j<=brushSize; ++j)
                {
                    temp.x= x+i;
                    temp.y = y+j;
                    if(temp.x < _size && temp.x >=0 && temp.y < _size && temp.y>=0)
                                    AddParticle(material, temp);
                }
        }
        }
        std::vector<std::thread> threads;
        for(auto iter = _ActiveParticles.begin(); iter != _ActiveParticles.end(); ++iter)
        {
                int i = iter->x;
                int j = iter->y;
               // threads.push_back(std::thread(ParticleHandler, this, i, j));
                ParticleHandler(i, j);
        }
        // for(auto& thread: threads)
        //      thread.join();
        std::set<Point> NewActiveParticles;
        int counter = 0;
        for(int i = 0; i < _size;++i)
        {
            for(int j =0; j < _size;++j)
            {
                if(_NoActiveTicks[i][j] < 3)
                {
                    NewActiveParticles.insert(Point{i, j});
                    counter++;
                }
            }
        }
        _ActiveParticles = NewActiveParticles;
        return _GameFieldArr;
    }
    
    GameField::~GameField()
    {}
    void GameField::HardUpdate()
    {
        std::set<Point> NewActiveParticles;
        for(int i =0; i <_size; ++i)
        {
            for(int j =0; j <_size; ++j)
            {
                if(_GameFieldArr[i][j] != VOIDP)
                    NewActiveParticles.insert(Point{i, j});
            }
        }
        _ActiveParticles = std::move(NewActiveParticles);
    }
    int GameField::GetSize()
    {
        return _size;
    }
    void GameField::ParticleHandler(int i, int j)
    {
        //std::lock_guard<std::mutex> lock(_m1);
        switch(_GameFieldArr[i][j])
                { 
                case VOIDP:
                    _NoActiveTicks[i][j] = 100;
                    break;
                case SAND:
                    if(j < _size-1 && _GameFieldArr[i][j+1] < SAND)
                    {
                        for(int r=-1; r <= 1; ++r )
                        {
                            for(int s =-1; s<=1; ++s)
                            {

                            if(i+r < _size && i+r >=0 && j+s < _size && j+s>=0)
                                    _NoActiveTicks[i+r][j+s] = 0;
                            }
                        }
                        int r = rand() % 10 +1,s; // для неоднородного падения песка
                        for(s = 1; s <= r; ++s)
                        {
                        if(j+s >= _size || _GameFieldArr[i][j+s] >= SAND)
                            break;
                        }
                        r = rand() % 2;
                        if((i+1-2*r) >= 0 && (i+1-2*r) < _size && _GameFieldArr[i+1-2*r][j+s-1]  < SAND)
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i+1-2*r][j+s-1];
                            _GameFieldArr[i+1-2*r][j+s-1] = SAND;
                            _NoActiveTicks[i+1-2*r][j+s-1] = 0;
                        }
                        else
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i][j+s-1];
                            _GameFieldArr[i][j+s-1] = SAND;
                           _NoActiveTicks[i][j+s-1] = 0;
                        }
                    }
  
                    else if(j+1 < _size &&  _GameFieldArr[i][j+1] >= SAND)
                    {
                        bool left = (i-1 >= 0 && _GameFieldArr[i-1][j+1] < SAND && _GameFieldArr[i-1][j] < SAND);
                        bool right = (i+1 < _size && _GameFieldArr[i+1][j+1] <SAND && _GameFieldArr[i+1][j] <SAND );
                        if(left && right)
                        {
                            int r =(rand()%2)*2;
                            _GameFieldArr[i][j] = _GameFieldArr[i+1-r][j+1] ; 
                            _GameFieldArr[i+1-r][j+1] = SAND;
                            

                        }
                        else if(left)
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i-1][j+1]; 
                            _GameFieldArr[i-1][j+1] = SAND; 
                        }
                        else if(right)
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i+1][j+1]; 
                            _GameFieldArr[i+1][j+1] = SAND;
                        }
                        else
                        {
                                _NoActiveTicks[i][j]++;
                                break;
                        }
                        _NoActiveTicks[i][j] = 0;
                        for(int r=-1; r <= 1; ++r )
                        {
                            for(int s =-1; s<=1; ++s)
                            {

                            if(i+r < _size && i+r >=0 && j+s < _size && j+s>=0)
                                    _NoActiveTicks[i+r][j+s] = 0;
                            }
                        }
                    }
                    else
                        _NoActiveTicks[i][j]++;
                     break;
                case WATER:
                    if(j < _size-1 && _GameFieldArr[i][j+1] < WATER)
                    {
                        for(int r=-1; r <= 1; ++r )
                        {
                            for(int s =-1; s<=1; ++s)
                            {

                            if(i+r < _size && i+r >=0 && j+s < _size && j+s>=0)
                                    _NoActiveTicks[i+r][j+s] = 0;
                            }
                        }
                        int r = rand() % 10 +1,s; // для неоднородного падения воды
                        for(s = 1; s <= r; ++s)
                        {
                        if(j+s >= _size || _GameFieldArr[i][j+s] >= WATER)
                            break;
                        }
                        r = rand() % 2;
                        if((i+1-2*r) >= 0 && (i+1-2*r) < _size && _GameFieldArr[i+1-2*r][j+s-1]  < WATER)
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i+1-2*r][j+s-1];
                            _GameFieldArr[i+1-2*r][j+s-1] = WATER;
                            _NoActiveTicks[i+1-2*r][j+s-1] = 0;
                        }
                        else
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i][j+s-1];
                            _GameFieldArr[i][j+s-1] = WATER;
                           _NoActiveTicks[i][j+s-1] = 0;
                        }
                    }
                    else if((j < _size-1 ||_GameFieldArr[i][j+1] != VOIDP))
                        {
                            int r  =_size, l = _size;
                            bool prioretyleft = false;
                            bool prioretyright = false;
                            bool left = (i > 0 && _GameFieldArr[i-1][j] == VOIDP);
                            bool right = ( i+1 < _size &&  _GameFieldArr[i+1][j] == VOIDP);
                            if(left && right)
                            {
                                for(int t = 0; t < i; ++t)
                                {
                                if(_GameFieldArr[i-t][j+1] == VOIDP)
                                {
                                    l =  t;
                                    break;
                                }
                                }
                                for(int t = 0; t < _size-i; ++t)
                                {
                                    if(_GameFieldArr[i+t][j+1] == VOIDP)
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
                                    if(i+s >= _size-1 ||_GameFieldArr[i+s][j+down] != VOIDP)
                                        break;
                                    if(j+down+1 < _size-1  && _GameFieldArr[i+s][j+1+down] == VOIDP)
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
                                    if(i-s <= 0 ||_GameFieldArr[i-s][j+down] != VOIDP)
                                        break;
                                    if(j+down+1 <= _size-1  && _GameFieldArr[i-s][j+1+down] == VOIDP)
                                    {
                                        down++;
                                    }
                                }
                                s-=1;
                                }
                                _GameFieldArr[i][j] = VOIDP; 
                                _GameFieldArr[i+(((prioretyleft)-(prioretyright)-( prioretyleft &&  prioretyright))*s)][j+down] = WATER;
                                _NoActiveTicks[i+(((prioretyleft)-(prioretyright)-( prioretyleft &&  prioretyright))*s)][j+down] = 0;
                            }
                            else if(left)
                            {
                                int s =1 , down = 0;
                                for(s = 2; s <= 6; ++s)
                                {
                                    if(i-s <= 0 ||_GameFieldArr[i-s][j+down] != VOIDP)
                                        break;
                                    if(j+down+1 <= _size-1  && _GameFieldArr[i-s][j+1+down] == VOIDP)
                                    {
                                        down++;
                                    }
                                }
                                s-=1;
                                _GameFieldArr[i][j] = VOIDP; 
                                _GameFieldArr[i-s][j+down] = WATER; 
                                 _NoActiveTicks[i-s][j+down] = 0;
                            }
                            else if(right)
                            {
                                int s = 1, down = 0;
                                for(s = 2; s <= 6; ++s)
                                {
                                    if(i+s >= _size-1 ||_GameFieldArr[i+s][j+down] != VOIDP)
                                        break;
                                    if(j+down+1 <= _size-1  && _GameFieldArr[i+s][j+1+down] == VOIDP)
                                    {
                                        down++;
                                    }
                                }
                                s-=1;
                                _GameFieldArr[i][j] = VOIDP; 
                                _GameFieldArr[i+s][j+down] = WATER;
                               _NoActiveTicks[i+s][j+down] = 0;
                            }
                            else
                            {
                               _NoActiveTicks[i][j]++;
                               break;
                            }
                            for(int r=-1; r <= 1; ++r )
                            {
                                for(int s =-1; s<=1; ++s)
                                {

                                if(i+r < _size && i+r >=0 && j+s < _size && j+s>=0)
                                    _NoActiveTicks[i+r][j+s] = 0;
                                }
                            }
                        }
                        else
                           _NoActiveTicks[i][j]++;
                        break;
                case VIRUS:
                    {
                    bool flag = false;
                    if(rand() % 3 == 0)
                        break;
                    int s = rand() % 3 -1;
                    int r = rand() % 3 -1;
                    for(int s =-1; s<= 1; ++s)
                    {
                    for(int r =-1; r<=1; ++r)
                    {   
                         if(i+s < _size && i+s >=0 && j+r < _size && j+r >=0 && _GameFieldArr[i+s][j+r] != VOIDP && _GameFieldArr[i+s][j+r] != VIRUS)
                        {
                                    flag = true;
                                    if(rand()%2)
                                    {
                                    _GameFieldArr[i+s][j+r] = VIRUS;
                                    _NoActiveTicks[i+s][j+r] = 0;
                                    }
                        }
                    }
                    if(!flag)  _NoActiveTicks[i][j] = 100;
                    }
                    break;
                    }
                case FIRE:
                    bool flag = false;
                    if(rand() % 10  == 0)
                    {
                        _GameFieldArr[i][j] = VOIDP;
                        break;
                    }
                    if(j-1 >= 0 && _GameFieldArr[i][j-1] < FIRE && rand() %2 )
                    {
                        _GameFieldArr[i][j-1] = FIRE;
                        _NoActiveTicks[i][j-1] = 0;
                        _GameFieldArr[i][j] = VOIDP;
                    }
                    for(int s =-1; s<= 1; ++s)
                    {
                    for(int r =-1; r<=1; ++r)
                    {   
                         if(i+s < _size && i+s >=0 && j+r < _size && j+r >=0 && (_GameFieldArr[i+s][j+r] == WOOD || _GameFieldArr[i+s][j+r] == FIRE || _GameFieldArr[i+s][j+r] == VIRUS) )
                        {
                            flag = true;
                            if(rand()%2)
                            {
                                _GameFieldArr[i+s][j+r] = FIRE;
                                _NoActiveTicks[i+s][j+r] = 0;
                            }
                        }
                    }
                    }

                    break;
                    



            }
        }
}