#include <time.h>
#include <stdlib.h>

#include "GridMap.h"
#include "Utility.h"

typedef unsigned __int32 uint32_t;
/* Null, because instance will be initialized on demand. */
GridMap* GridMap::m_instance = 0;

GridMap::GridMap()
    :m_map()
    , m_startCoinNumber(20)
    , m_startLeftWallNumber(2)
    , m_startMineNumber(8)
    , m_startRightWallNumber(2)
    , m_currentCoinNumber (0)
    , m_currentMineNumber (0)
    , m_currentLeftWallNumber (0)
    , m_currentRightWallNumber (0)
{
    srand(unsigned(time(NULL))); // seed
    m_seed = rand();
    StartGame();
}

void GridMap::ClearMap()
{
    for (size_t j = 0; j < kGridSizeX; j++)
    {
        for (size_t i = 0; i < kGridSizeY; i++)
        {
            m_map[i][j] = m_emptySymbol;
        }
    }
}

GridMap* GridMap::GetInstance()
{
    if (m_instance == 0)
    {
        m_instance = new GridMap();
    }

    return m_instance;
}

void GridMap::StartGame()
{
    m_currentCoinNumber = m_startCoinNumber;
    m_currentMineNumber = m_startMineNumber;
    m_currentLeftWallNumber = m_startLeftWallNumber;
    m_currentRightWallNumber = m_startRightWallNumber;

    ClearMap();

    GenerateRandomTileByType(m_coinSymbol, m_startCoinNumber);
    GenerateRandomTileByType(m_mineSymbol, m_startMineNumber);
    GenerateRandomTileByType(m_leftWallSymbol, m_startLeftWallNumber);
    GenerateRandomTileByType(m_rightWallSymbol, m_startRightWallNumber);
}

GridMap::Position GridMap::GetValidRandomTileAvoid(Position avoidPosition, float radiusSquare)
{
    Position result = GetValidRandomTile();

    if (Square(result.x - avoidPosition.x) + Square(result.y - avoidPosition.y) < radiusSquare)
    {
        return GetValidRandomTileAvoid(avoidPosition, radiusSquare);
    }
    return result;
}

GridMap::Position GridMap::GetValidRandomTile()
{
    size_t result = GetRandomNumber() % kMapSize;

    size_t y = result / kGridSizeX;
    size_t x = result % kGridSizeX;

    Clamp(&y, 0, kGridSizeY);
    Clamp(&x, 0, kGridSizeX);

    if (m_map[x][y] != m_emptySymbol)
    {
        return GetValidRandomTile();
    }
    return { x, y };
}

size_t GridMap::GetRandomNumber()
{
    static uint32_t x = m_seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    m_seed = x;
    return x;
}

void GridMap::GenerateRandomTileByType(char type, int number)
{
    for (int i = 0; i < number; i++)
    {
        Position result = GetValidRandomTile();
        m_map[result.x][ result.y] = type;
    }
}

void GridMap::GenerateRandomTileByTypeAvoid(char type, int number, Position avoidPosition, float radius)
{
    float radiusSquare = radius * radius;
    for (int i = 0; i < number; i++)
    {
        Position result = GetValidRandomTileAvoid(avoidPosition, radiusSquare);
        m_map[result.x][result.y] = type;
    }
}



GridMap::Position GridMap::GetGridPosition(MyVector2 pos)
{
    size_t x = pos.x + kGridSizeX / 2;
    size_t y = kGridSizeY / 2 - pos.y;
    Clamp(&y, 0, kGridSizeY);
    Clamp(&x, 0, kGridSizeX);
    return { (size_t)x, (size_t)y };
}
