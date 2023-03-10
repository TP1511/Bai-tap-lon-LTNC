#pragma once
#include "InGame.hpp"
#include "Action.hpp"
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_events.h>
#include<SDL_mixer.h>
#include<iostream>
using namespace std;

extern string TITLE;
extern int WIDTH;
extern int HEIGHT;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *InitScreen;
extern SDL_Texture *StartGameDefault, *StartGame1, *StartGame2;
extern SDL_Texture *modeEasy, *modeMed, *modeHard, *ChooseMode;
extern SDL_Texture *Easy, *Medium, *Hard;
extern SDL_Texture *Flag, *Square, *Mine, *Blank;
extern SDL_Texture *Win, *Lose, *continueGame, *buttonContinueGame1, *buttonContinueGame2;
extern SDL_Texture *Num[9];
extern SDL_Texture *numMine[11];
extern bool cont;
extern bool quit;
extern int mode;
extern int startX;
extern int startY;
extern int endX;
extern int endY;
extern int stepX;
extern int stepY;
extern int Row;
extern int Column;
extern int countTmpMine;
extern Mix_Chunk *Boom;
extern Mix_Chunk *Failed;
extern Mix_Chunk *Succeeded;
extern Mix_Chunk *Button;
extern Mix_Chunk *ClickLeft;
extern Mix_Chunk *ClickRight;

SDL_Texture *loadTexture(string path);
bool init();
bool loadImage();
bool loadAudio();
void loadScreen(SDL_Texture *img, int width, int height);
void renderTexture(SDL_Texture *img, int startX, int startY, int width, int height);
void close();