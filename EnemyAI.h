#ifndef ENEMY_AI_H
#define ENEMY_AI_H

#include "GameState.h"

Vec* LongestPath(int who , Vec* origin, GameState theGame)
{
    Vec* betterMove = new Vec();
    betterMove->set(*origin);

    std::cout << *betterMove << std::endl;

    int row = 0;
    int column = 0;
    int longestStreak = 0;
    int currentStreak = 0;
    Vec* canGoHere = new Vec();
    //check for rows
    for(int b = 0; b < theGame.size; b++)
    {
        canGoHere->set(-1, -1);
        for(int a = 0; a < theGame.size; a++)
        {
            if(theGame.grid[a][b] == who)
            {
                currentStreak++;
            }
            else if(theGame.grid[a][b] == 1) // should be ((who + 1) % 2)
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
        }
        currentStreak = 0;
        std::cout << *betterMove << std::endl;
    }
    //check for Columns
    for(int a = 0; a < theGame.size; a++)
    {
        canGoHere->set(-1, -1);
        for(int b = 0; b < theGame.size; b++)
        {
            if(theGame.grid[a][b] == who)
            {
                currentStreak++;
            }
            else if(theGame.grid[a][b] == 1) // should be ((who + 1) % 2)
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
        }
        std::cout << *betterMove << std::endl;
        currentStreak = 0;
    }
    //currentStreak = 0;
    //check diaognals
    canGoHere->set(-1, -1);
    for(int a = 0; a < theGame.size; a++)
    {
        if(theGame.grid[a][a] == who)
        {
            currentStreak++;
        }
        else if(theGame.grid[a][a] == 1) // should be ((who + 1) % 2)
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
    std::cout << *betterMove << std::endl;
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
        else if(theGame.grid[(theGame.size - 1) - a][a] == 1) // should be ((who + 1) % 2)
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
    std::cout << *betterMove << std::endl;
    // std::cout << *betterMove << std::endl;
    // std::cout << *betterMove << std::endl;
    // std::cout << *betterMove << std::endl;
    // std::cout << *betterMove << std::endl;
    // std::cout << *betterMove << std::endl;

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

    move->set(*LongestPath(0, move, theGame));

    //first check if we can win
    //LongestPath(1, move, theGame);

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