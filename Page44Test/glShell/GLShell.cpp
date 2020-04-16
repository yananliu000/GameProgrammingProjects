// GLShell.cpp : Defines the entry point for the console application.
//

#include <iostream>
using std::cout;

#include "stdafx.h"
#include "GridMap.h"
#include "Player.h"
#include "MyVector2.h"
#include "Utility.h"
#include "GameManager.h"

#define PLAYER Player::GetInstance() 
#define MAP GridMap::GetInstance() 
#define GAMEMANAGER GameManager::GetInstance() 


//time: the estimated time for the player to arrive the wall
void PutBounceWall(bool isLeft, float time)
{
    //get wall position
    MyVector2 playerSpeed = PLAYER->m_playerSpeed;
    MyVector2 playerPos = PLAYER->m_playerPos;
    MyVector2 wallPos = playerSpeed * time + playerPos;

    //boundaries
    Clamp(&wallPos.x, START_HOR_OFFSET, END_HOR_OFFSET);
    Clamp(&wallPos.y, START_VER_OFFSET, END_VER_OFFSET);

    //get wall grid pos 
    GridMap::Position gridPos = MAP->GetGridPosition(wallPos);

    //spawn wall
    if (isLeft)
    {
        MAP->m_map[gridPos.x][gridPos.y] = MAP->m_leftWallSymbol;
    }
    else
    {
        MAP->m_map[gridPos.x][gridPos.y] = MAP->m_rightWallSymbol;
    }

}

void key(unsigned char key, int x, int y)
{
    switch(key) {
    case VK_ESCAPE:
        exit(0);
        break;

    case 47: // '/'
        PutBounceWall(true, 3);
        break;

    case 92: // '\'
        PutBounceWall(false, 3);
        break;
    }
}

void drawline(color color, line line, float z)
{
    glBegin(GL_LINES);
    glColor4ub(color.r, color.g, color.b, color.a);
    glVertex3f(line.p1x, line.p1y, z);
    glVertex3f(line.p2x, line.p2y, z);
    glEnd();
}

void drawquad(color color, rect rect, float z)
{
    glBegin(GL_QUADS);
    glColor4ub(color.r, color.g, color.b, color.a);
    glVertex3f(rect.left, rect.bot, z);
    glVertex3f(rect.right, rect.bot, z);
    glVertex3f(rect.right, rect.top, z);
    glVertex3f(rect.left, rect.top, z);
    glEnd();
}

void drawarena(void)
{
    int r, c;

    // draw background quad
    drawquad({ 255, 255, 255, 255 }, { START_HOR_OFFSET ,END_VER_OFFSET, END_HOR_OFFSET, START_VER_OFFSET }, -1.5f);

    glBegin(GL_LINES);
    glColor4ub(0, 255, 0, 255);

    // draw grid to provide a sense of scale
    for (r = 0; r <= NUM_INTERVALS; r++)
    {
        glVertex3f(START_HOR_OFFSET, INTERVAL*r + START_VER_OFFSET,  -1.4f);
        glVertex3f(END_HOR_OFFSET, INTERVAL*r + START_VER_OFFSET,  -1.4f);
    }
    for (c = 0; c <= NUM_INTERVALS; c++)
    {
        glVertex3f(INTERVAL*c + START_HOR_OFFSET, START_VER_OFFSET, -1.4f);
        glVertex3f(INTERVAL*c + START_HOR_OFFSET, END_VER_OFFSET, -1.4f);
    }
    glEnd();
}

void drawplayer()
{
    static MyVector2 p1 = {0.24f*GLOBAL_SCALE, 0.0f};
    static MyVector2 p2 = {-0.12f*GLOBAL_SCALE, -0.12f*GLOBAL_SCALE};
    static MyVector2 p3 = {-0.12f*GLOBAL_SCALE, 0.12f*GLOBAL_SCALE};
    MyVector2 t1, t2, t3;

    MyVector2 playerSpeed = PLAYER->m_playerSpeed;
    MyVector2 playerPos = PLAYER->m_playerPos;

    // transform points so that triangle "heads" in travel direction
    t1.x =  p1.Dot(playerSpeed);
    t1.y = -p1.y * playerSpeed.x + p1.x * playerSpeed.y;
    t2.x =  p2.Dot(playerSpeed);
    t2.y = -p2.y * playerSpeed.x + p2.x * playerSpeed.y;
    t3.x = p3.Dot(playerSpeed);
    t3.y = -p3.y * playerSpeed.x + p3.x * playerSpeed.y;

    glBegin(GL_TRIANGLES);
    glColor4ub(0, 0, 0, 255);

    glVertex3f(playerPos.x + t1.x, playerPos.y + t1.y, -1.32f);
    glVertex3f(playerPos.x + t2.x, playerPos.y + t2.y, -1.32f);
    glVertex3f(playerPos.x + t3.x, playerPos.y + t3.y, -1.32f);
    glEnd();
}

void redraw()
{
    /* clear stencil each time */
    glClearColor(0.5f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    // draw play arena
    drawarena();

    // draw objs
    for (size_t j = 0; j < MAP->kGridSizeX; j++)
    {
        for (size_t i = 0; i < MAP->kGridSizeY; i++)
        {
            char cell = MAP->m_map[i][j];
            float x = float(i) - 10;
            float y = 10 - float(j);
            
            if (cell == MAP->m_coinSymbol)
            {
                rect rect = { x , y , x + 1, y - 1 };
                drawquad(sYellow, rect, -1.32f);
            }
            else if (cell == MAP->m_mineSymbol)
            {
                rect rect = { x , y , x + 1, y - 1 };
                drawquad(sRed, rect, -1.32f);
            }
            else if (cell == MAP->m_leftWallSymbol)
            {
                line line = { x , y - 1 , x + 1, y };
                drawline(sRed, line, -1.32f);
            }
            else if (cell == MAP->m_rightWallSymbol)
            {
                line line = {x , y , x + 1, y - 1};
                drawline(sRed, line, -1.32f);
            }
        }
    }

    // draw player triangle
    drawplayer();
    
    glutSwapBuffers();
}

float timedelta(void)
{
    static LARGE_INTEGER sFreq;
    static double        sInvFreq = 0;
    static __int64       sCurrentTime = 0L;

    LARGE_INTEGER now;
    if (sCurrentTime == 0L)
    {
        QueryPerformanceFrequency( &sFreq );
        sInvFreq = 1.0f / ((double)sFreq.QuadPart);
        QueryPerformanceCounter( &now );
        sCurrentTime = (__int64)((double)now.QuadPart * sInvFreq * 1000);
    }
    QueryPerformanceCounter( &now );
    __int64 newcurrentTime = (__int64)((double)now.QuadPart * sInvFreq * 1000);
    float dt = 0.001f*(newcurrentTime - sCurrentTime);
    if (dt < 1.0f/60.0f) // clamp between 60hz and 30hz
        dt = 1.0f/60.0f;
    else if (dt > 1.0f/30.0f)
        dt = 1.0f/30.0f;
    sCurrentTime = newcurrentTime;
    return dt;
}

void anim()
{
    glPushMatrix();
    redraw();
    glPopMatrix();

    float dt = timedelta();

    //check match timer
    if (!GAMEMANAGER->isTimerFinished())
    {
        if (GAMEMANAGER->Update(dt))
        {
            //if the timer just finishes => restart the game
            PLAYER->Start();
            MAP->StartGame();
        }
        return;
    }

    //check lose
    if (PLAYER->m_lives <= 0)
    {
        std::cout << "You Lose!\n";
        GAMEMANAGER->StartTimer();
    }

    //check win
    else if (MAP->m_currentCoinNumber <= 0)
    {
        std::cout << "You win!\n";
        GAMEMANAGER->StartTimer();
    }

    PLAYER->Update(dt);

    //check collision
    //1. get player grid position
    GridMap::Position playerGridPos = MAP->GetGridPosition(PLAYER->m_playerPos);

    //2. check collision
    char symbol = MAP->m_map[playerGridPos.x][playerGridPos.y];
    if (symbol != MAP->m_emptySymbol)
    {
        if (symbol == MAP->m_coinSymbol)
        {
            //player side
            PLAYER->m_coinNum++;

            //map side
            MAP->m_currentCoinNumber--;
            MAP->GenerateRandomTileByTypeAvoid(MAP->m_mineSymbol, 2, playerGridPos, 5);
        }
        else if (symbol == MAP->m_mineSymbol)
        {
            //player side
            PLAYER->m_lives--;

            //map side
            MAP->m_currentMineNumber--;
        }
        else if (symbol == MAP->m_leftWallSymbol)
        {
            //player side
            PLAYER->m_playerSpeed = { PLAYER->m_playerSpeed.y, PLAYER->m_playerSpeed.x };

            //map side
            MAP->m_currentLeftWallNumber--;
        }
        else if (symbol == MAP->m_rightWallSymbol)
        {
            //player side
            PLAYER->m_playerSpeed = { -PLAYER->m_playerSpeed.y, -PLAYER->m_playerSpeed.x };
           
            //map side
            MAP->m_currentRightWallNumber--;
        }
        MAP->m_map[playerGridPos.x][playerGridPos.y] = MAP->m_emptySymbol;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitDisplayMode(GLUT_STENCIL|GLUT_DEPTH|GLUT_DOUBLE);
    (void)glutCreateWindow("Page 44 Test");
    glutDisplayFunc(redraw);
    glutKeyboardFunc(key);
    glutIdleFunc(anim);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-10., 10., -10., 10., 0., 20.);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_COLOR_MATERIAL);

    PLAYER->Start();

    glutMainLoop();

    return 0;
}

