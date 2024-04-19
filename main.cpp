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
    system("clear");
    GameState game;

    
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
        Menu();
        int input;
        cin >> input;
        cout << endl << endl;
        int sizeBoard;
        bool gameActive = true;
        switch(input)
        {
            case 1:
                system("clear");
                cout << "It is tic tac toe!" << endl;
                PressEnter(1);
                  /// enter button
                break;
            case 2:
                cout << "What size board would you like!" << endl;
                cin >> sizeBoard;
                pvp(sizeBoard, gameActive);
                PressEnter();/// continue
                break;
            case 3:
                cout << "What size board would you like!" << endl;
                cin >> sizeBoard;
                EasyAi(sizeBoard, gameActive);
                PressEnter();
                break;
            case 4: //If Ai first will always win or tie
                cout << "What size board would you like!" << endl;
                cin >> sizeBoard;
                HardAi(sizeBoard, gameActive);
                PressEnter();
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
