#include <iostream>
#include <windows.h>
#include "Player.hpp"
#include "GameState.hpp"


using namespace std;

void revertString(string *str,int left, int right){
    if((left >= right)){
        return;
    }
    else{
        char tmp = (*str)[left];
        (*str)[left] = (*str)[right];
        (*str)[right] = tmp;
        revertString(str,++left,--right);
    }
}

int main(){
    string str = "anna";
    cout<<str<<endl;
    revertString(&str,0,str.length()-1);
    cout<<str<<endl;
    return 0;
}


/*
void ShowConsoleCursor(bool showFlag);




int main() {
    ShowConsoleCursor(false);
    GameState* MyGame = new GameState();
    MyGame->SetGameState(MENU);







    return 0;
}


void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}*/