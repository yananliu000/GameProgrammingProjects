#pragma once
#include "MyVector2.h"

class GridMap
{
private:
    const int m_startCoinNumber;
    const int m_startMineNumber;
    const int m_startLeftWallNumber;
    const int m_startRightWallNumber;
    size_t m_seed;

    /* Here will be the instance stored. */
    static GridMap* m_instance;
    
    /* Private constructor to prevent instancing. */
    GridMap() ;
    void ClearMap();
public:
    struct Position
    {
        size_t x;
        size_t y;
    };

    static constexpr size_t kGridSizeX = 20;
    static constexpr size_t kGridSizeY = 20;
    static constexpr size_t kMapSize = 400;

    const char m_coinSymbol = '$';
    const char m_mineSymbol = '*';
    const char m_leftWallSymbol = '|';
    const char m_rightWallSymbol = '/';
    const char m_emptySymbol = ' ';

    char m_map [kGridSizeX][kGridSizeY];

    int m_currentCoinNumber;
    int m_currentMineNumber;
    int m_currentLeftWallNumber;
    int m_currentRightWallNumber;

    /* Static access method. */
    static GridMap* GetInstance();
    void StartGame();
    Position GetValidRandomTile();
    size_t GetRandomNumber();
    void GenerateRandomTileByType(char type, int number);
    void GenerateRandomTileByTypeAvoid(char type, int number, Position avoidPosition, float radius);
    Position GetValidRandomTileAvoid(Position avoidPosition, float radiusSquare);
    Position GetGridPosition(MyVector2 pos);
};

