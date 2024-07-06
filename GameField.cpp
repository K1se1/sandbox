#include "GameField.hpp"

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
        _GameFieldArr.at(coords.x).at(coords.y) = particle;
    }
    std::vector<std::vector<int>> GameField::DoTick() 
    {
        std::vector<std::vector<int>> OldGameFieldArr =_GameFieldArr;
        for(int k =0; k <3;++k)
        {
        OldGameFieldArr =_GameFieldArr;
        for(int j = 0; j < _size; ++j)
        {
            for(int i =_size-1; i >= 0; --i)
            {
                switch(OldGameFieldArr[i][j])
                { 
                case VOID:
                    break;
                case FSAND:
                    if(j < _size-1 && _GameFieldArr[i][j+1] == VOID)
                    {
                        _GameFieldArr[i][j] = VOID;
                        if(j+1 == _size-1 ||_GameFieldArr[i][j+2] == SAND)
                                _GameFieldArr[i][j+1] = SAND;
                        else
                            _GameFieldArr[i][j+1] = FSAND;
                    }
                    else if(j == _size-1 ||_GameFieldArr[i][j+1] == SAND)
                        _GameFieldArr[i][j] = SAND;
                     break;
                case SAND:
                        if(j < _size-1 && _GameFieldArr[i][j+1] != SAND)
                        {
                            _GameFieldArr[i][j] = FSAND;
                            break; 
                        }
                        if(j+1 < _size && i > 0 && i+1 < _size)
                        {
                            bool left = (_GameFieldArr[i-1][j+1] == VOID && _GameFieldArr[i-1][j] == VOID);
                            bool right = (_GameFieldArr[i+1][j+1] == VOID && _GameFieldArr[i+1][j] == VOID);
                            if(left && right)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i+1-(rand()%2)*2][j+1] = FSAND; 
                            }
                            else if(left)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i-1][j+1] = FSAND; 
                            }
                            else if(right)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i+1][j+1] = FSAND; 
                            }
                        }
                         break;
                case WATER:
                    if(j < _size-1 && _GameFieldArr[i][j+1] == VOID)
                    {
                        _GameFieldArr[i][j] = VOID;
                        _GameFieldArr[i][j+1] = WATER;
                    }
                    else if(i > 0 && i+1 < _size &&  _GameFieldArr[i][j+1] != VOID)
                        {
                            if(_GameFieldArr[i-1][j] == VOID && _GameFieldArr[i+1][j] == VOID)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i+1-(rand()%2)*2][j] = WATER; 
                            }
                            else if( _GameFieldArr[i-1][j] == VOID)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i-1][j] = WATER; 
                            }
                            else if( _GameFieldArr[i+1][j] == VOID)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i+1][j] = WATER; 
                            }
                        }
                        break;
                }


            }
        }
        }
        return _GameFieldArr;
    }
    
    GameField::~GameField()
    {}
    

}