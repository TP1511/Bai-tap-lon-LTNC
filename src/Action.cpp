#include "Action.hpp"

int mousePress(SDL_MouseButtonEvent &button) {
    if(button.button == SDL_BUTTON_LEFT) {
        return 1;
    } else if(button.button == SDL_BUTTON_RIGHT) {
        return 2;
    }
    return 0;
}

void humanInput(bool &quit, int &chooseRow, int &chooseCol) {
    SDL_Event e;
    while(1) {
        if(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = 1;
                close();
                exit(0);
            } else if(e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;
                if(y < startY || y > endY || x < startX || x > endX) {
                    continue;
                }
                chooseCol = (x - startX) / stepX + 1;
                chooseRow = (y - startY) / stepY + 1;
                if(chooseCol > Column) {
                    chooseCol = Column;
                }
                if(chooseRow > Row) {
                    chooseRow = Row;
                }
                return;
            }
        }
    }
}

int calcMode(int x, int y) { 
    if(x >= 299 && x <= 702) {
        if(y >= 151 && y <= 245) {
            Mix_PlayChannel(-1,Button,0);
            return 1;
        } else if(y >= 351 && y <= 446) {
            Mix_PlayChannel(-1,Button,0);
            return 2;
        } else if(y >= 571 && y <= 663) {
            Mix_PlayChannel(-1,Button,0);
            return 3;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

void humanChooseMode(bool &quit, int &mode) {
    SDL_Event e;
    while(mode < 1 || mode > 3) {
        if(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = 1;
                close();
                exit(0);
            } else if(e.type == SDL_MOUSEBUTTONDOWN) {
                mode = calcMode(e.button.x,e.button.y);
            } else if(e.type == SDL_MOUSEMOTION) {
                int x = e.button.x;
                int y = e.button.y;
                if(x >= 299 && y >= 151 && x <= 702 && y <= 245) {
                    loadScreen(modeEasy,WIDTH,HEIGHT);
                } else if(x >= 229 && y >= 351 && x <= 702 && y <= 446) {
                    loadScreen(modeMed,WIDTH,HEIGHT);
                } else if(x >= 299 && y >= 571 && x <= 702 && y <= 663) {
                    loadScreen(modeHard,WIDTH,HEIGHT);
                } else {
                    loadScreen(ChooseMode,WIDTH,HEIGHT);
                }
            }
        }
    }
    SDL_Delay(500);
}

void startGame(bool &quit) {
    loadScreen(InitScreen,1000,800);
    SDL_Delay(800);
    SDL_Event e;
    while(!quit) {
        if(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = 1;
                close();
                exit(0);
            } else if(e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;
                if(x >= 322 && y >= 329 && x <= 677 && y <= 429) {
                    Mix_PlayChannel(-1,Button,0);
                    SDL_Delay(500);
                    return;
                } else if(x >= 338 && y >= 506 && x <= 654 && y <= 624) {
                    quit = 1;
                    Mix_PlayChannel(-1,Button,0);
                    SDL_Delay(200);
                    close();
                    exit(0);
                }
            } else if(e.type == SDL_MOUSEMOTION) {
                int x = e.button.x;
                int y = e.button.y;
                if(x >= 322 && y >= 329 && x <= 677 && y <= 429) {
                    loadScreen(StartGame1,WIDTH,HEIGHT);
                } else if(x >= 338 && y >= 506 && x <= 654 && y <= 624) {
                    loadScreen(StartGame2,WIDTH,HEIGHT);
                } else {
                    loadScreen(StartGameDefault,WIDTH,HEIGHT);
                }
            }
        }
    }
}

void showTmpMine(int countTmpMine) {
    int w = 22;
    int h = 23;
    int startX = 0;
    int startY = 0;
    if(mode == 1) {
        startX = 176;
        startY = 31;
    } else if(mode == 2) {
        startX = 302;
        startY = 45;
    } else {
        startX = 465;
        startY = 45;
    }
    if(countTmpMine < 0) {
        renderTexture(Blank,startX,startY,w,h);
        renderTexture(numMine[10],startX,startY + 9,18,6);
        countTmpMine = -countTmpMine;
    } else {
        renderTexture(numMine[0],startX,startY,w,h);
    }
    renderTexture(numMine[countTmpMine / 10],startX + w + 3,startY,w,h);
    renderTexture(numMine[countTmpMine % 10],startX + 2 * w + 6,startY,w,h);
}

bool continuePlay(bool &quit) {
    SDL_Event e;
    loadScreen(continueGame,1000,800);
    while(!quit) {
        if(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = 1;
                close();
                exit(0);
            } else {
                int x = e.button.x;
                int y = e.button.y;
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    if(x >= 308 && y >= 502 && x <= 676 && y <= 568) {
                        Mix_PlayChannel(-1,Button,0);
                        SDL_Delay(200);
                        return 1; 
                    } else if(x >= 308 && y >= 659 && x <= 676 && y <= 725) {
                        Mix_PlayChannel(-1,Button,0);
                        SDL_Delay(200);
                        return 0;
                    }
                    // cout << x << " " << y << "\n"; 
                } else if(e.type == SDL_MOUSEMOTION) {
                    if(x >= 308 && y >= 502 && x <= 676 && y <= 568) {
                        loadScreen(buttonContinueGame1,1000,800);
                    } else if(x >= 308 && y >= 659 && x <= 676 && y <= 725) {
                        loadScreen(buttonContinueGame2,1000,800);
                    } else {
                        loadScreen(continueGame,1000,800);      
                    }
                }
            }
        }
    }
    return 1;
}