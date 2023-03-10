# MinesweeperSDL2    
Simple minesweeper game in SDL2 (C/C++)    
# Installation    
### 1. Install and Setup [Visual Studio Code](https://code.visualstudio.com/download), [Make GNU](http://gnuwin32.sourceforge.net/packages/make.htm), [MinGW](https://sourceforge.net/projects/mingw/). (Remember where you installed the MinGW and MakeGNU).    
### 2. Add MinGW and MakeGNU to environment PATH:
#### - Open the "Edit the system environment variables" by typing on Window Search Bar -> "Advance" -> "Environment Variables".
#### - In "System variables" zone, click on "Path" then "Edit".
#### - Choose "New" then copy the bin file of MinGW and MakeGNU paths to two new lines. And click OK to save.
### 3. Download the repository.    
### 4. Open this repository's folder with vscode. Go to settings, search for "Run in Terminal" and tick the box. Press `Ctrl + Shift + ~` to open Terminal. Type `make run` to play the game. (Or all you have to do is just open main.exe =)))
# How to play
Left click to open the square, right click to set or unset flag.
When you open the square which has a mine, you lose the game. If you set all the flag on right positions, you win the game. 
# About this game.
It's inspired by the original minesweeper game.
There are 3 modes:
- Easy: 9 x 9 (10 mines)
- Medium:  16 x 16 (40 mines)
- Hard: 30 x 16 (99 mines)
