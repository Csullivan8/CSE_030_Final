#include <iostream>
#include <istream>
#include <string>
#include <system_error>
#include <cctype>
#include "GameState.h"
#include "EnemyAI.h"

using namespace std;

int main()
{
    GameState game;

    game.play(0, 0);
    game.play(1, 1);
    cout << game << endl;
    cout << "EXTREME TIC TAC TOE!!!!";
    bool looping = true;
    while(looping == true)
    {
        /*

        1: Instructions
        2: pvp mode
        3: weak AI
        4: strong AI
        5: quit

        */
        int input;
        cout << endl << endl;
        cout << "1: Instructions" << endl;
        cout << "2: pvp mode" << endl;
        cout << "3: weak AI" << endl;
        cout << "4: strong AI" << endl;
        cout << "5: quit" << endl << endl;
        cout << "Choose an Option to Continue." << endl;
        cin >> input;
        cout << endl << endl;
        int sizeBoard;
        bool gameActive = true;
        switch(input)
        {
            case 1:
                cout << "It is tic tac toe!" << endl;
                break;
            case 2:
                cout << "What size board would you like!" << endl;
                cin >> sizeBoard;
                if(sizeBoard < 1)
                {
                    cout << "Error. Enter a valid input";
                }
                else
                {
                    GameState pvpGame(sizeBoard);
                    string temp;
                    getline(cin, temp);
                    while(gameActive)
                    {
                        cout << pvpGame << endl;
                        cout << "Player " << 1 + pvpGame.currentTurn << "'s turn" << endl;
                        cout << "Enter where you would like to go in \"row, column\" format!" << endl;
                        string theMove;
                        getline(cin, theMove);
                        int x = (int) stoi(theMove.substr(0, 1)); // add trim maybe
                        int y = (int) stoi(theMove.substr(3, 1));
                        pvpGame.play(x, y);
                        if(pvpGame.hasWon(0))
                        {
                            gameActive = false;
                            cout << pvpGame << endl;
                            cout << "Player " << 0 << " has won!";
                        }
                        else if(pvpGame.hasWon(1))
                        {
                            gameActive = false;
                            cout << pvpGame << endl;
                            cout << "Player " << 1 << " has won!";
                        }
                    }
                }
                break;
            case 3:
                cout << "What size board would you like!" << endl;
                cin >> sizeBoard;
                if(sizeBoard < 1)
                {
                    cout << "Error. Enter a valid input";
                }
                else
                {
                    GameState pveEasyGame(sizeBoard);
                    string temp;
                    int playerNum;
                    //ask if player wants to go first
                    cout << "Would you like to player 1 or 2? (1 or 2)" << endl;
                    cin >> playerNum;
                    if(playerNum == 2)
                    {
                        pveEasyGame = EnemyPlayRandomMove(pveEasyGame);
                    }
                    getline(cin, temp);
                    while(gameActive)
                    {
                        cout << pveEasyGame << endl;
                        cout << "Your turn!" << endl;
                        cout << "Enter where you would like to go in \"row, column\" format!" << endl;
                        string theMove;
                        getline(cin, theMove);
                        int x = (int) stoi(theMove.substr(0, 1)); // add trim maybe
                        int y = (int) stoi(theMove.substr(theMove.find(",") + 2, 1));
                        pveEasyGame.play(x, y);
                        if(pveEasyGame.hasWon(0))
                        {
                            gameActive = false;
                            cout << pveEasyGame << endl;
                            cout << "Player " << 0 << " has won!";
                        }
                        if(pveEasyGame.turnCount % 2 == (playerNum) % 2)
                        {
                            if(pveEasyGame.done == false)
                                pveEasyGame = EnemyPlayRandomMove(pveEasyGame);
                            else if(pveEasyGame.hasWon(1))
                            {
                            gameActive = false;
                            cout << pveEasyGame << endl;
                            cout << "Player " << 1 << " has won!";
                            }
                            else if(pveEasyGame.hasWon(0)) {}
                            else
                            {
                                cout << "It is a draw." << endl;
                                gameActive = false;
                            }
                            if(pveEasyGame.hasWon(1))
                            {
                                gameActive = false;
                                cout << pveEasyGame << endl;
                                cout << "Player " << 1 << " has won!";
                            }
                        }
                    }
                }
                break;
            case 4:
                cout << "What size board would you like!" << endl;
                cin >> sizeBoard;
                if(sizeBoard < 1)
                {
                    cout << "Error. Enter a valid input";
                }
                else
                {
                    GameState pveHardGame(sizeBoard);
                    string temp;
                    int playerNum;
                    //ask if player wants to go first
                    cout << "Would you like to player 1 or 2? (1 or 2)" << endl;
                    cin >> playerNum;
                    if(playerNum == 2)
                    {
                        pveHardGame = EnemyPlayBestMove(pveHardGame);
                    }
                    getline(cin, temp);
                    while(gameActive)
                    {     
                        cout << pveHardGame << endl;
                        cout << "Your turn! EXETREME VERSION" << endl;
                        cout << "Enter where you would like to go in \"row, column\" format!" << endl;
                        string theMove;
                        getline(cin, theMove);
                        int x = (int) stoi(theMove.substr(0, 1)); // add trim maybe
                        int y = (int) stoi(theMove.substr(3, 1));
                        pveHardGame.play(x, y);
                        //std::cout << "NO SEGEMENTATION FAULT HERE.";
                        if(pveHardGame.hasWon(0))
                        {
                            gameActive = false;
                            cout << pveHardGame << endl;
                            cout << "Player " << 0 << " has won!";
                        }
                        //std::cout << "NO SEGEMENTATION FAULT HERE.";
                        if(pveHardGame.turnCount % 2 == (playerNum) % 2)
                        {
                            if(pveHardGame.done == false)
                                pveHardGame = EnemyPlayBestMove(pveHardGame);
                            else if(pveHardGame.hasWon(1))
                            {
                                gameActive = false;
                                cout << pveHardGame << endl;
                                cout << "Player " << ((playerNum - 1) % 2) + 1<< " has won!";
                            }
                            else if(pveHardGame.hasWon(0)) {}
                            else
                            {
                                cout << "It is a draw." << endl;
                                gameActive = false;
                            }
                            if(pveHardGame.hasWon(1))
                            {
                                gameActive = false;
                                cout << pveHardGame << endl;
                                cout << "Player " << 1 << " has won!";
                            }
                        }
                    }
                }
                break;
            case 5:
                cout << "Goodbye!";
                looping = false;
                break;
            default:
                cout << "Error. Enter a valid input";
                break;
        }
    }
    
    return 0;
}