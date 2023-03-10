#include "InGame.hpp"

InGame::InGame() {
    row = 0;
    col = 0;
    mine = 0;
}

void InGame::initialize(int mode) {
    if(mode == 1) {
        Row = 9;
        Column = 9;
        setSize(9,9);
        setNumMine(10);
        loadScreen(Easy,252,320);
        startX = 0;
        startY = 86;
        endX = 251;
        endY = 319;
    } else if(mode == 2) {
        Row = 16;
        Column = 16;
        setSize(16,16);
        setNumMine(40);
        loadScreen(Medium,448,527);
        startX = 0;
        startY = 110;
        endX = 447;
        endY = 526;
    } else {
        Row = 16;
        Column = 30;
        setSize(16,30);
        setNumMine(99);
        loadScreen(Hard,840,527);
        startX = 0;
        startY = 110;
        endX = 839;
        endY = 526;
    }
    for(int i = 1; i <= getRow(); i++) {
        for(int j = 1; j <= getCol(); j++) {
            a[i][j] = '-';
            b[i][j] = false;
        }
    }
    countTmpMine = getMine();
    setMine(getMine());
}

int InGame::getCol() {
    return col;
}

int InGame::getRow() {
    return row;
}

void InGame::setNumMine(int m) {
    mine = m;
}

int InGame::getMine() {
    return mine;
}

void InGame::setSize(int n, int m) {
    row = n;
    col = m;
}

void InGame::setFlag(int r, int c) {
    if(a[r][c] == '*') {
        mine--;
    } else if(a[r][c] == '@') {
        if(b[r][c] == true) {
            a[r][c] = '*';
            mine++;
        } else {
            a[r][c] = '-';
        }
        countTmpMine++;
        renderTexture(Square,stepX * (c - 1) + startX,stepY * (r - 1) + startY,stepX,stepY);
        return;
    } else if(a[r][c] >= '0' && a[r][c] <= '9') {
        return;
    }
    renderTexture(Flag,stepX * (c - 1) + startX,stepY * (r - 1) + startY,stepX,stepY);
    a[r][c] = '@';
    countTmpMine--;
}

void InGame::setMine(int n) {
    srand(time(NULL));
    for(int i = 0; i < n; i++) {
        int x = rand() % row + 1;
        int y = rand() % col + 1;
        if(a[x][y] == '-') {
            a[x][y] = '*';
            b[x][y] = true;
            if(i == n) {
                break;
            }
        } else {
            i--;
        }
    }
}
        
bool InGame::checkValid(int r, int c) {
    return r >= 1 && r <= row && c >= 1 && c <= col;
}

bool InGame::checkMine(int r, int c) {
    return a[r][c] == '*';
}

bool InGame::checkNum(int r, int c) {
    return a[r][c] >= '0' && a[r][c] <= '9';
}
    
bool InGame::checkUnoccupied(int r, int c) {
    return a[r][c] == '-';
}

bool InGame::checkFlagRightPos(int r, int c) {
    for(int i = 0; i < 8; i++) {
        int newr = moveRow[i] + r;
        int newc = moveCol[i] + c;
        if(checkValid(newr,newc) && b[newr][newc] == true && a[newr][newc] != '@' && a[r][c] >= '0' && a[r][c] <= '9') {
            return false;
        }
    }
   return true;
}

int InGame::countFlag(int r, int c) {
    int count = 0;
    for(int i = 0; i < 8; i++) {
        int newr = moveRow[i] + r;
        int newc = moveCol[i] + c;
        if(checkValid(r,c) && checkValid(newr,newc) && a[newr][newc] == '@') {
            count++;
        }
    }
    return count;
}

int InGame::countMine(int r, int c) {
    int count = 0;
    for(int i = 0; i < 8; i++) {
        int newr = moveRow[i] + r;
        int newc = moveCol[i] + c;
        if(checkValid(r,c) && checkValid(newr,newc) && b[newr][newc] == true) {
            count++;
        }
    }
    return count;
}

void InGame::openFieldOccupied(int r, int c) {
    if(checkValid(r,c)) {
        for(int i = 0; i < 8; i++) {
            int newr = moveRow[i] + r;
            int newc = moveCol[i] + c;
            if(checkValid(newr,newc) && a[newr][newc] == '-') {
                int count = countMine(newr,newc);
                if(count == 0) {
                    openFieldEmpty(newr,newc);
                } else {
                    a[newr][newc] = (char)(count + 48);
                    SDL_Delay(2);
                    renderTexture(Num[count],stepX*(newc-1)+startX,stepY*(newr-1)+startY,stepX,stepY);
                }
            }
        }
    }
}

void InGame::openFieldEmpty(int r, int c) {
    if(!checkValid(r,c) || a[r][c] != '-') {
        return;
    } else {
        int tmpMine = countMine(r,c);
        a[r][c] = (char)(tmpMine + 48);
        SDL_Delay(2);
        renderTexture(Num[tmpMine],stepX*(c-1)+startX,stepY*(r-1)+startY,stepX,stepY);
        for(int i = 0; i < 4; i++) {
            int newr = openRow[i] + r;
            int newc = openCol[i] + c;
            if(tmpMine == 0) {
                int cheor[4] = {-1,-1,1,1};
                int cheoc[4] = {-1,1,1,-1};
                for(int j = 0; j < 4; j++) {
                    int newCheor = r + cheor[j];
                    int newCheoc = c + cheoc[j];
                    if(checkValid(newCheor,newCheoc) && a[newCheor][newCheoc] == '-') {
                        openFieldEmpty(newCheor,newCheoc);
                    }
                }
                openFieldEmpty(newr, newc);
            } 
        }
    }
}

void InGame::handleGame(int chooseRow, int chooseCol, bool &quit, bool &lose) {
    SDL_Event e;
    int choice = 0;
    while(choice == 0) {
        choice = mousePress(e.button);
        if(e.type == SDL_QUIT) {
            quit = 1;
            return;
        }
        if(choice == 1 && checkValid(chooseRow,chooseCol)) {
            Mix_PlayChannel(-1,ClickLeft,0);
            if(checkMine(chooseRow,chooseCol)) {
                Mix_PlayChannel(-1,Boom,0);
                lose = true;
                return;
            } else if(!checkFlagRightPos(chooseRow,chooseCol) && checkNum(chooseRow,chooseCol) 
                && countFlag(chooseRow,chooseCol) == countMine(chooseRow,chooseCol)) {
                lose = true;
                Mix_PlayChannel(-1,Boom,0);
                return;
            } else if(checkFlagRightPos(chooseRow,chooseCol) && checkNum(chooseRow,chooseCol) 
                && countFlag(chooseRow,chooseCol) == countMine(chooseRow,chooseCol)) {
                openFieldOccupied(chooseRow,chooseCol);
            } else if(checkUnoccupied(chooseRow,chooseCol)) {
                openFieldEmpty(chooseRow,chooseCol);
            }
        } else if(choice == 2 && checkValid(chooseRow,chooseCol)) {
            Mix_PlayChannel(-1,ClickRight,0);
            setFlag(chooseRow,chooseCol);
        }
    }
}

void InGame::printAll() {
    for(int i = 1; i <= row; i++) {
        for(int j = 1; j <= col; j++) {
            if(b[i][j] == true) {
                SDL_Delay(10);
                renderTexture(Mine,stepX*(j-1)+startX,stepY*(i-1)+startY,stepX,stepY);
            }
        }
    }
}