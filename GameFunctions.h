#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GameState.h"
#include "EnemyAI.h"
#include <limits>

using namespace std;

void PressEnter(int num=0){
    std::cout << "press Enter: ";
    if(num == 1){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.clear();
    cin.get();
    system("clear"); 
}

void Menu(){
    cout << endl << endl;
    cout << "1: Instructions" << endl;
    cout << "2: pvp mode" << endl;
    cout << "3: weak AI" << endl;
    cout << "4: strong AI" << endl;
    cout << "5: quit" << endl << endl;
    cout << "Choose an Option to Continue." << endl;
}


string Storepoints(string playerFile){
    int point = 1;

    ofstream file;
    file.open(playerFile, ios::app);
    if(file.is_open()){
        file << point << endl;
        file.close();
    }
    else{
        return "file can't open\n";
    }
}

int ReadPoints(string playerFile){
    int Total_points = 0;
    int num;

    ifstream file;
    file.open(playerFile, ios::in);
    if(file.is_open()){
        while(file >> num){
            if(num == 1){
                Total_points+=num;
            }
            else{
                break;
            }
        }
        file.close();   
    }
    return Total_points;
}
// void points(bool player1, bool player2, string section){
//     if(player1){
//        Storepoints(section+"player1");
//         cout << "Total points:" << ReadPoints(section+"player1") << endl;
        
//     }if(player2){
//         Storepoints(section+"player2");
//         cout << "Total points:" << ReadPoints(section + "player2") << endl;
//     }
// }


void pvp(int sizeBoard, bool gameActive){
    
    if(sizeBoard < 1)
    {
        cout << "Error. Enter a valid input";
    }
    else{
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
            if(pvpGame.done==true)
            {
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
                else
                {
                    cout << "It is a draw." << endl;
                    gameActive = false;
                } 
            }  
        }
    }
}

void EasyAi(int sizeBoard, bool gameActive){

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
        cout << "Would you like to be player 1 or 2? (1 or 2)" << endl;
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
            if(pveEasyGame.done == true)
            {
                if(pveEasyGame.hasWon(1))
                {
                    gameActive = false;
                    cout << pveEasyGame << endl;
                    cout << "Player 2 has won!" << endl;
                }
                else if(pveEasyGame.hasWon(0)) 
                {
                    gameActive = false;
                    cout << pveEasyGame << endl;
                    cout << "Player 1 has won!" << endl;
                }
                else
                {
                    cout << "It is a draw." << endl;
                    gameActive = false;
                }
            }
            if(pveEasyGame.turnCount % 2 == (playerNum) % 2)
            {
                if(pveEasyGame.done == false)
                    pveEasyGame = EnemyPlayRandomMove(pveEasyGame);
                else if(pveEasyGame.hasWon(1))
                {
                    gameActive = false;
                    cout << pveEasyGame << endl;
                    cout << "Player 2 has won!";
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
                    cout << "Player 2 has won!" << endl;
                }
                if(pveEasyGame.hasWon(0))
                {
                    gameActive = false;
                    cout << pveEasyGame << endl;
                    cout << "Player 1 has won!" << endl;
                }
            }
        }
        // if(pveEasyGame.hasWon(0)){
        //     Storepoints("Easyplayer1");
        //     cout << "Total points: " << ReadPoints("Easyplayer1") << endl;
        // }if(pveEasyGame.hasWon(1)){
        //     Storepoints("Easyplayer2");
        //     cout << "Total points: " << ReadPoints("Easyplayer2") << endl;
        // }
        
    }

}
void HardAi(int sizeBoard, bool gameActive){
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
            system("clear");
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
            if(pveHardGame.done == true)
            {
                system("clear");
                if(pveHardGame.hasWon(1))
                {
                    gameActive = false;
                    cout << pveHardGame << endl;
                    cout << "Player 2 has won!" << endl;
                }
                else if(pveHardGame.hasWon(0)) 
                {
                    gameActive = false;
                    cout << pveHardGame << endl;
                    cout << "Player 1 has won!" << endl;
                }
                else
                {
                    cout << "It is a draw." << endl;
                    gameActive = false;
                }
            }
            //std::cout << "NO SEGEMENTATION FAULT HERE.";
            if(pveHardGame.turnCount % 2 == (playerNum) % 2)
            {
                system("clear");
                if(pveHardGame.done == false)
                    pveHardGame = EnemyPlayBestMove(pveHardGame);
                else if(pveHardGame.hasWon(1))
                {
                    gameActive = false;
                    cout << pveHardGame << endl;
                    cout << "Player 2 has won!" << endl;
                }
                else if(pveHardGame.hasWon(0)) 
                {
                    gameActive = false;
                    cout << pveHardGame << endl;
                    cout << "Player 1 has won!" << endl;
                }
                else
                {
                    cout << "It is a draw." << endl;
                    gameActive = false;
                }
                system("clear");
                if(pveHardGame.hasWon(1))
                {
                    gameActive = false;
                    cout << pveHardGame << endl;
                    cout << "Player 2 has won!" << endl;
                }
                if(pveHardGame.hasWon(0))
                {
                    gameActive = false;
                    cout << pveHardGame << endl;
                    cout << "Player 1 has won!" << endl;
                }
            }
        }             
    }
}
                        
#endif
