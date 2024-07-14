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
        std::vector<std::vector<int>> OldGameFieldArr =_GameFieldArr;
        for(int k =0; k <7;++k)
        {
        std::set<Point> NewActiveParticles;
        OldGameFieldArr =_GameFieldArr;
        for(auto iter = _ActiveParticles.begin(); iter != _ActiveParticles.end(); ++iter)
        {
                int i = iter->x;
                int j = iter->y;
                switch(OldGameFieldArr[i][j])
                { 
                case VOID:
                    break;
                case SAND:
                    if(j < _size-1 && _GameFieldArr[i][j+1] < SAND)
                    {
                        int r = rand() % 2 +1,s; // для неоднородного падения песка
                        for(s = 1; s < r; ++s)
                        {
                        if(_GameFieldArr[i][j+s] >= SAND)
                            break;
                        }
                        _GameFieldArr[i][j] = _GameFieldArr[i][j+s-1];
                        _GameFieldArr[i][j+s-1] = SAND;
                        NewActiveParticles.insert(Point{i, j+s-1});
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
                        }
                        else if(left)
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i-1][j+1]; 
                            _GameFieldArr[i-1][j+1] = SAND; 
                            NewActiveParticles.insert(Point{i-1, j+1});
                        }
                        else if(right)
                        {
                            _GameFieldArr[i][j] = _GameFieldArr[i+1][j+1]; 
                            _GameFieldArr[i+1][j+1] = SAND;
                            NewActiveParticles.insert(Point{i+1, j+1});
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
                        int r = rand() % 2 +1,s; // для неоднородного падения воды
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
                                if(l >= r)
                                    prioretyleft = true;
                                else
                                    prioretyright = true;
                                int r =(rand()%2)*2;
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i+(prioretyleft)-(prioretyright)-( prioretyleft &&  prioretyright)][j] = WATER;
                                NewActiveParticles.insert(Point{i+(prioretyleft)-(prioretyright)-( prioretyleft &&  prioretyright), j}); 
                            }
                            else if(left)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i-1][j] = WATER; 
                                NewActiveParticles.insert(Point{i-1, j});
                            }
                            else if(right)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i+1][j] = WATER;
                                NewActiveParticles.insert(Point{i+1, j});
                            }
                            else
                                NewActiveParticles.insert(Point{i, j});
                        }
                        else
                            NewActiveParticles.insert(Point{i, j});
                        break;


            }
        }
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

}