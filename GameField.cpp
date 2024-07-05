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
        for(int i = 0; i < _size; ++i)
        {
            for(int j =_size-1; j >= 0; --j)
            {
                switch(OldGameFieldArr[i][j])
                { 
                case VOID:
                    break;
                case (FSAND || SAND):
                    Point temp;
                    if(j+1 < _size && OldGameFieldArr[i][j+1] == VOID)
                    {
                        _GameFieldArr[i][j] = VOID;
                        if(j+1 == _size-1 ||_GameFieldArr[i][j+2] == SAND)
                                _GameFieldArr[i][j+1] = SAND;
                        else
                            _GameFieldArr[i][j+1] = FSAND;
                    }
                    else if(j+1 == _size || OldGameFieldArr[i][j+1] == SAND)
                    {
                        if(i > 0 && i+1 < _size)
                        {
                            if(OldGameFieldArr[i-1][j+1] == VOID)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i-1][j] = SAND; 
                            }
                            else if(OldGameFieldArr[i+1][j+1] == VOID)
                            {
                                _GameFieldArr[i][j] = VOID; 
                                _GameFieldArr[i+1][j] = SAND; 
                            }
                        }
                    
                    }
                }


            }
        }
        return _GameFieldArr;
    }
    
    GameField::~GameField()
    {}
    

}