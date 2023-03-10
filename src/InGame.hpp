#pragma once
#include<iostream>
#include<cstdlib>
#include<time.h>
#include "InitGame.hpp"
#include "Action.hpp"
using namespace std;

class InGame {
private:
    int row;
    int col;
    char a[31][31]; // primary board to determine what type of each square
    bool b[31][31]; // additional board to determine which square is a mine
    int moveRow[8] = {0,-1,-1,-1,0,1,1,1}; 
    int moveCol[8] = {-1,-1,0,1,1,1,0,-1};
    int openRow[4] = {0,-1,0,1};
    int openCol[4] = {-1,0,1,0};
    int mine;
public:
    InGame();
    int getRow();
    int getCol();
    void setNumMine(int m);
    int getMine();
    void setSize(int n, int m);
    void setFlag(int r, int c);     // Put flag on a square
    void setMine(int n);            // randomly put mines on board
    bool checkValid(int r, int c);  // check row and column are valid
    bool checkMine(int r, int c);   // check a square is a mine or not
    bool checkNum(int r, int c);    // check a square is a number
    bool checkUnoccupied(int r, int c);     // check a square has been opened
    bool checkFlagRightPos(int r, int c);   // check flags around an opened square is in right position
    int countFlag(int r, int c);    // count the number of flags around an opened square
    int countMine(int r, int c);    // count the number of mines around an opened square
    void openFieldOccupied(int r, int c);   // open the board if clicked on an opened square
    void openFieldEmpty(int r, int c);      // open the board if clicked on an unopened square
    void initialize(int mode);
    void handleGame(int chooseRow, int chooseCol, bool &quit, bool &lose);
    void printAll(); // only show this when you lose
};