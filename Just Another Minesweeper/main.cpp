//
//  main.cpp
//  Just Another Minesweeper
//
//  Created by Ichkamo on 3/17/16.
//  Copyright © 2016 Ichkamo. Means Open-Source.
//


#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <stdio.h>
using namespace std;

// ---Global Vars---

const int TABLEMAXSIZE = 10;
int Size = 0;

// \Global Vars

// ---FUNCTIONS---


bool playagain (){
    int ask;
    cout << "------GAME OVER------" << endl << "Play again? (1 = YES, 0 = NO): ";
    cin >> ask;
    switch (ask) {
        case 1:
            cout << endl << "GOOD CHOICE !" << endl;
            return true;
            break;
        case 0:
            cout << "Cya! Well played!" << endl << "(please disregard this message if you didn't play well)" << endl;
            return false;
            break;
        default:
            cout << "!!! INVALID ANSWER >:O- !!!"<< endl << "Therefore shalt thou play!" << endl;
            return true;
            break;
    }
}



int minecount (int Table[TABLEMAXSIZE][TABLEMAXSIZE])
{
    int NumberOfMines = 0;
    for (int yi = 0; yi < Size; yi++) {
        for (int xi = 0; xi < Size; xi++) {
            if (Table[xi][yi] == 666) {
                NumberOfMines++;
            }
        }
    }
    return NumberOfMines;
}


void drawblock (int block)
{
    switch (block) {
        case 666:
            cout << "|x";
            break;
        case 0:
            cout << "|_";
            break;
        case 1:
            cout << "|1";
            break;
        case 2:
            cout << "|2";
            break;
        case 3:
            cout << "|3";
            break;
        case 4:
            cout << "|4";
            break;
        case 5:
            cout << "|5";
            break;
        case 6:
            cout << "|6";
            break;
        case 7:
            cout << "|7";
            break;
        default:
            cout << "|8";
            break;
    }
}



int sumTable (int AnotherTable[TABLEMAXSIZE][TABLEMAXSIZE]){
    int sum = 0;
    for (int xi = 0; xi < Size; xi++) {
        for (int yi = 0; yi < Size; yi++) {
            if (AnotherTable[xi][yi] == 1) {
                sum++;
            }
        }
    }

    return sum;
    
}

//// IF CLEAR SCREEN NEEDED <----------
//void ClearScreen()
//{
//    cout << string( 100, '\n' );
//}

// \FUNCTIONS


int main(void) {
    
    cout << "~~~~~~ Welcome to ~~~~~~~" << endl << "~JUST ANOTHER MINESWEEPER~" << endl << "~~~~~~~~~Ichkamo~~~~~~~~~"<< endl;
    
    do {
        
        // ---INITIALISATION---
        
        int Mines = 0;
        int Table[TABLEMAXSIZE][TABLEMAXSIZE];
        int MineGen = 0;
        
        do {
            cout << "Please enter table Size (3->" << TABLEMAXSIZE << ") : ";
            cin >> Size;
        } while (Size < 3 || Size > TABLEMAXSIZE);
        
        do {
            cout << endl << "Please enter number of Mines (Max is " << Size*Size << " and not recommended!) : ";
            cin >> Mines;
        } while (Mines < 0 || Mines > Size*Size);
        
        if (Mines == Size*Size) {
            cout << "--- INSTANT DEFEAT!! ---" << endl << "Better Luck Next Time!" << endl;
            playagain();
        }
        // World Generation
        
        cout << "World Generation in Progress... " << endl;
        
        // 0 is free 666 is mine
        
        cout << "    Filling World.." << endl;
        for (int xi = 0; xi < TABLEMAXSIZE; xi++) {
            for (int yi = 0; yi < TABLEMAXSIZE ; yi++) {
                Table[xi][yi] = 0;
                //cout << "xi" << xi << "yi" << yi<< endl; //debug
            }
        }
        
        cout << "    Adding Mines.. " << endl;
        srand(static_cast<unsigned int>(time(NULL)));// we don't wanna get the same "random" every TIME!
        while (MineGen < Mines) {
            Table[rand()%Size][rand()%Size] = 666;
            //cout << "minegen" << MineGen << "minecount" << minecount(Table)<< endl; //debug
            MineGen = minecount(Table);
        }
        
        //add neighbors 1 2 3 4...
        for (int yi = 0; yi < Size; yi++) {
            for (int xi = 0; xi < Size ; xi++) {
                if (Table[xi][yi] == 0) {
                    //cout << "xi" << xi << "yi" << yi << endl; //debug
                    //empty? what about neighbors?
                    for (int yj =(yi-1<0)?0:yi-1; yj <= yi+1 && yj != TABLEMAXSIZE ; yj++) {
                        for (int xj =(xi-1<0)?0:xi-1; xj <= xi+1 && xj != TABLEMAXSIZE; xj++) {
                            //cout << "xj" << xj << "yj" << yj << endl; //debug
                            if (Table[xj][yj] == 666) {
                                Table[xi][yi]++;
                                //cout << "+1" << endl; //debug
                            }
                        }
                    }
                }
                
            }
        }
        
        
        cout << "World Generation Successful!" << endl;
        
        //game initialisation
        
        bool gameON = true;
        int X = 0;
        int Y = 0;
        int revealed [TABLEMAXSIZE][TABLEMAXSIZE];
        int easterEgg = 0;
        
        
        // 0 is hidden, 1 is revealed
        for (int xi = 0; xi < TABLEMAXSIZE; xi++) {
            for (int yi = 0; yi < TABLEMAXSIZE ; yi++) {
                revealed[xi][yi] = 0;
            }
        }
        
        cout << endl << "GAME START!"<< endl;
        
        // ---GAME LOOP---
        do {
            
            // PAINTING LEVEL
            
            cout << " ";
            for (int i=0; i<Size; i++) {
                cout << " " << i;
            }// x margin
            cout << endl;

            
            for (int yi = 0; yi < Size; yi++) {
                cout << yi; // y margin
                for (int xi = 0; xi < Size ; xi++) {
                    if (revealed[xi][yi] == 1) {
                        drawblock(Table[xi][yi]);
                    }else {
                        cout << "|#";
                        
                    }
                    
                }
                cout << "|" << endl;
            }
            
            // input
            
            cout << "Don't Think Twice It's All Right!" << endl;
            cout << "X : ";
            cin >> X;
            cout << "Y : ";
            cin >> Y;
            
            
            // process input
            //check if player wants to see the easter egg
            if (X < 0 || X >= Size || Y >= Size || Y < 0) {
                cout << "Nothing interesting happens..." << endl;
                easterEgg++ ;
            }else{ //player wants to play
                //check if there's a Mine
                if (Table[X][Y] == 666) {
                    cout << ">>>>> BBBAAAAAZZZAAAAAMMM!! <<<<<<" << endl << "( Means you're Pixie dust :D )" << endl;
                    gameON = false;
                } else {//if not let's roll!
                        revealed[X][Y] = 1;
                        // let's reveal more! (if 0, all neighboring table[][] == 0)
                        // LOOKING FOR AN EASIER WAY TO DO THIS!!!! >:O-
                        // nb : RECURSIVE IS NOT AN OPTION
                        // thanks for your help! ;)
                    if (Table[X][Y] == 0) {
                        bool keepsweeping = true;
                        do{
                            keepsweeping = false;
                            for (int yi = 0; yi < Size; yi++) {  //sweeping all over the board!
                                for (int xi = 0; xi < Size; xi++) {
                                    if (Table[xi][yi] == 0 && revealed[xi][yi] == 0) { //if there's a hidden 0, check for revealed friends
                                        for (int yj =(yi-1<0)?0:yi-1; yj <= yi+1 && yj != TABLEMAXSIZE ; yj++) {                                            for (int xj =(xi-1<0)?0:xi-1; xj <= xi+1 && xj != TABLEMAXSIZE; xj++) {
                                                if (revealed[xj][yj] == 1 && Table[xj][yj] == 0) { //if revealed 0 neighbor
                                                    revealed[xi][yi] = 1; // reveal me!
                                                    keepsweeping = true; // and keep going..
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }while (keepsweeping);
                        // showing revealed board edge numbers!
                        for (int yi = 0; yi < Size; yi++) { // sweeping all over the board again!
                            for (int xi = 0; xi < Size; xi++) {
                                if (Table[xi][yi] == 0 && revealed[xi][yi] == 1) {
                                    // if there's a revealed 0, make sure he's not lonely
                                    for (int yk =(yi-1<0)?0:yi-1; yk <= yi+1 && yk != TABLEMAXSIZE ; yk++) {
                                        for (int xk =(xi-1<0)?0:xi-1; xk <= xi+1 && xk != TABLEMAXSIZE; xk++) {
                                        revealed[xk][yk] = 1; // revealing 0's neighbors!
                                        }
                                    }
                                }
                            }
                        }
                        // end of additional sweeping... Got a better way? HELP ME!!!
                    }
                }
            }
            
            
            //check if player is eligible to see the easter egg
            if (easterEgg > 10) {
                cout << " ^ Like this message? Try RUNESCAPE!" << endl;
                easterEgg = 0;
            }
            
            
            
            //Check if player won
            cout << "Revealed : " << sumTable(revealed) << endl;
            cout << "What's Left : " << (Size*Size - Mines) - sumTable(revealed) << endl;
            cout << "Total : " << (Size*Size - Mines) << endl;
            
            
            if (sumTable(revealed) >= (Size*Size - Mines) ) {
                cout << "---------------------" << endl << "------GG YOU WON-----" << endl << "(but can you win again?)" << endl;
                gameON = false;
            }
            
        
        }while (gameON);
        // END OF GAME LOOP
        

    }while (playagain());
    
    return 0;
}



