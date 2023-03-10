#pragma once
#include "InitGame.hpp"
#include "InGame.hpp"
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_events.h>

int calcMode(int x, int y);
void humanChooseMode(bool &quit, int &mode);
void humanInput(bool &quit, int &chooseRow, int &chooseCol);
int mousePress(SDL_MouseButtonEvent &button);
void startGame(bool &quit);
void showTmpMine(int countTmpMine);
bool continuePlay(bool &quit);