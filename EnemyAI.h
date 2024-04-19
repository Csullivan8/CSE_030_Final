#ifndef ENEMY_AI_H
#define ENEMY_AI_H

#include "GameState.h"

Vec* CanWin(int who, Vec* origin, GameState theGame)
{
    who = (who) % 2;
    Vec* betterMove = new Vec();
    betterMove->set(*origin);

    int currentStreak = 0;
    Vec* canGoHere = new Vec();
    //check for rows
    for(int a = 0; a < theGame.size; a++)
    {
        currentStreak = 0;
        canGoHere->set(-1, -1);
        for(int b = 0; b < theGame.size; b++)
        {
            if(theGame.grid[a][b] == who)
            {
                currentStreak++;
            }
            else if(theGame.grid[a][b] == -1)
            {
                canGoHere->set(a, b);
            }
        }
        if(currentStreak + 1 == theGame.size && canGoHere->x != -1)
        {
            betterMove->set(*canGoHere);
            delete canGoHere;
            return betterMove;
        }
        currentStreak = 0;
    }

    //check for Columns
    for(int b = 0; b < theGame.size; b++)
    {
        currentStreak = 0;
        canGoHere->set(-1, -1);
        for(int a = 0; a < theGame.size; a++)
        {
            if(theGame.grid[a][b] == who)
            {
                currentStreak++;
            }
            else if(theGame.grid[a][b] == -1)
            {
                canGoHere->set(a, b);
            }
        }
        if(currentStreak + 1 == theGame.size && canGoHere->x != -1)
        {
            betterMove->set(*canGoHere);
            delete canGoHere;
            return betterMove;
        }
        currentStreak = 0;
    }
    //check diaognals
    currentStreak = 0;
    canGoHere->set(-1, -1);
    for(int a = 0; a < theGame.size; a++)
    {
        if(theGame.grid[a][a] == who)
        {
            currentStreak++;
        }
        else if(theGame.grid[a][a] == -1)
        {
            canGoHere->set(a, a);
        }
    }
    if(currentStreak + 1 == theGame.size && canGoHere->x != -1)
    {
        betterMove->set(*canGoHere);
        delete canGoHere;
        return betterMove;
    }
    currentStreak = 0;
    canGoHere->set(-1, -1);
    for(int a = 0; a < theGame.size; a++)
    {
        if(theGame.grid[(theGame.size - 1) - a][a] == who)
        {
            currentStreak++;
        }
        else if(theGame.grid[(theGame.size - 1) - a][a] == -1)
        {
            canGoHere->set((theGame.size - 1) - a, a);
        }
    }
    if(currentStreak + 1 == theGame.size && canGoHere->x != -1)
    {
        betterMove->set(*canGoHere);
        delete canGoHere;
        return betterMove;
    }
    
    delete canGoHere;

    return betterMove;
}

Vec* CornerBlock(int who , Vec* origin, GameState theGame)
{
    Vec* betterMove = new Vec();
    betterMove->set(*origin);

    if(theGame.turnCount == 1 && theGame.size == 3)
    {
        if(theGame.grid[2][2] == who)
        {
            betterMove->set(1, 1);
        }
        else if(theGame.grid[0][0] == who)
        {
            betterMove->set(1, 1);
        }
        else if(theGame.grid[2][0] == who)
        {
            betterMove->set(1, 1);
        }
        else if(theGame.grid[0][2] == who)
        {
            betterMove->set(1, 1);
        }
        
    }
    else if(theGame.turnCount == 0 && theGame.size == 3)
    {
        betterMove->set(1, 1);
    }
    else if(theGame.turnCount == 3 && theGame.size == 3)
    {
        if(theGame.grid[0][1] == -1)
            betterMove->set(0, 1);
        else if(theGame.grid[1][0] == -1)
            betterMove->set(1, 0);
        else if(theGame.grid[1][2] == -1)
            betterMove->set(1, 2);
    }

    return betterMove;
}

Vec* LongestPath(int who , Vec* origin, GameState theGame)
{
    Vec* betterMove = new Vec();
    betterMove->set(*origin);

    int row = 0;
    int column = 0;
    int longestStreak = 0;
    int currentStreak = 0;
    Vec* canGoHere = new Vec();
    //check for rows
    for(int b = 0; b < theGame.size; b++)
    {
        currentStreak = 0;
        canGoHere->set(-1, -1);
        for(int a = 0; a < theGame.size; a++)
        {
            if(theGame.grid[a][b] == who)
            {
                currentStreak++;
            }
            else if(theGame.grid[a][b] == (who) % 2) // should be ((who) % 2)
            {
                currentStreak = -999;
            }
            else if(theGame.grid[a][b] == -1)
            {
                canGoHere->set(a, b);
            }
        }
        if(currentStreak > longestStreak && canGoHere->x != -1)
        {
            betterMove->set(*canGoHere);
            //std::cout << "Hori block" << currentStreak << std::endl;
            longestStreak = currentStreak;
        }
        currentStreak = 0;
    }
    
    //check for Columns
    for(int a = 0; a < theGame.size; a++)
    {
        currentStreak = 0;
        canGoHere->set(-1, -1);
        for(int b = 0; b < theGame.size; b++)
        {
            if(theGame.grid[a][b] == who)
            {
                currentStreak++;
            }
            else if(theGame.grid[a][b] == (who) % 2) // should be ((who) % 2)
            {
                currentStreak = -999;
            }
            else if(theGame.grid[a][b] == -1)
            {
                canGoHere->set(a, b);
            }
        }
        if(currentStreak > longestStreak && canGoHere->x != -1)
        {
            betterMove->set(*canGoHere);
            longestStreak = currentStreak;
            //std::cout << "V block" << currentStreak  << std::endl;
        }
        currentStreak = 0;
    }

    //check diaognals
    canGoHere->set(-1, -1);
    currentStreak = 0;
    for(int a = 0; a < theGame.size; a++)
    {
        if(theGame.grid[a][a] == who)
        {
            currentStreak++;
        }
        else if(theGame.grid[a][a] == (who) % 2) // should be ((who) % 2)
        {
            currentStreak = -999;
        }
        else if(theGame.grid[a][a] == -1)
        {
            canGoHere->set(a, a);
        }
    }
    if(currentStreak >= longestStreak && canGoHere->x != -1)
    {
        betterMove->set(*canGoHere);
        longestStreak = currentStreak;
    }
    currentStreak = 0;
    row = (theGame.size - 1);
    column = 0;
    canGoHere->set(-1, -1);
    for(int a = 0; a < theGame.size; a++)
    {
        if(theGame.grid[(theGame.size - 1) - a][a] == who)
        {
            currentStreak++;
        }
        else if(theGame.grid[(theGame.size - 1) - a][a] == (who) % 2) // should be ((who) % 2)
        {
            currentStreak = -999;
        }
        else if(theGame.grid[(theGame.size - 1) - a][a] == -1)
        {
            canGoHere->set((theGame.size - 1) - a, a);
        }
    }
    if(currentStreak >= longestStreak && canGoHere->x != -1)
    {
        betterMove->set(*canGoHere);
        longestStreak = currentStreak;
    }    
    delete canGoHere;

    return betterMove;
}

GameState EnemyPlayBestMove(GameState theGame)
{
    //then move somewhere random
    Vec* move = new Vec(0, 0);
    while(theGame.grid[move->x][move->y] != -1)
    {
        move->set(move->x + 1, move->y);
        if(move->x > (theGame.size - 1))
        {
            move->set(0, move->y + 1);
        }
    }

    //then check if the middle is open
    if(theGame.size % 2 == 1 && theGame.grid[(theGame.size - 1) / 2][(theGame.size - 1) / 2] == -1)
    {
        move->set((theGame.size - 1) / 2, (theGame.size - 1) / 2);
    }

    //then check if we can block the longest streak from enemy (2 or more)
    move->set(*LongestPath((theGame.turnCount - 1) % 2, move, theGame));

    //check if player went in a corner to go in an opposite corner
    move->set(*CornerBlock((theGame.turnCount - 1) % 2, move, theGame));

    //first check if we can stop player win
    move->set(*CanWin((theGame.turnCount - 1) % 2, move, theGame));

    //first check if we can win
    move->set(*CanWin((theGame.turnCount) % 2, move, theGame));

    theGame.play(move->x, move->y);
    return theGame;
}

GameState EnemyPlayRandomMove(GameState theGame)
{
    Vec* move = new Vec(0, 0);
    while(theGame.grid[move->x][move->y] != -1)
    {
        move->set(move->x + 1, move->y);
        if(move->x > (theGame.size - 1))
        {
            move->set(0, move->y + 1);
        }
    }
    theGame.play(move->x, move->y);

    return theGame;
}

#endif