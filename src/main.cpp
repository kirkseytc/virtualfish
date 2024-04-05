#include <curses.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using std::string;

const char FISH_RIGHT[] = ">< >";
const char FISH_LEFT[] = "< ><";

typedef struct _vector2d {

    int x;
    int y;

    _vector2d(int x, int y){
        this->x = x;
        this->y = y;
    }

} VECTOR2D;

void toUpperCStr(char*);

int main(void){

    srand(time(0));

    initscr();
    cbreak();
    noecho();
    halfdelay(1);
    curs_set(0);

    box(stdscr, 0, 0);

    const unsigned int row = getmaxy(stdscr);
    const unsigned int col = getmaxx(stdscr);

    const unsigned int tankWidth = col - 7;
    const unsigned int tankHeight = row - 3;

    VECTOR2D fishPos(0,tankHeight);
    VECTOR2D fishVel(1,0);
    bool fishFlip = false;

    while(true){

        if(getch() == 27){ // ESC Pressed

            echo();
            curs_set(1);

            char userIn[col - 2];

            WINDOW* inputWin = newwin(1, col, (row - 1), 0);
            wprintw(inputWin, ": ");
            wgetnstr(inputWin, userIn, col - 3);

            toUpperCStr(userIn);

            string strIn(userIn);

            if(strIn == "QUIT" || strIn == "Q"){
                break;
            }

            wclear(inputWin);
            delwin(inputWin);
            noecho();
            curs_set(0);
            box(stdscr, 0, 0);
        }

        mvprintw((fishPos.y + 1), (fishPos.x + 1), "    ");

        fishVel.y = (rand()% 3) - 1;

        if((fishPos.y == 0 && fishVel.y == -1) || (fishPos.y == tankHeight && fishVel.y == 1)){
            fishVel.y *= -1;
        }

        if(fishPos.x == tankWidth){
            fishVel.x = -1;
            fishFlip = true;
        } else if (fishPos.x == 0){
            fishVel.x = 1;
            fishFlip = false;
        }

        fishPos.x += fishVel.x;
        fishPos.y += fishVel.y;

        if(fishFlip){
            mvprintw((fishPos.y + 1), (fishPos.x + 1), FISH_LEFT);
        } else {
            mvprintw((fishPos.y + 1), (fishPos.x + 1), FISH_RIGHT);
        }        

        refresh();
    }

    endwin();
    return 0;
}

void toUpperCStr(char* cstr){

    if(cstr == nullptr){
        return;
    }

    char* currChar = cstr;

    while(*currChar != '\0'){

        *currChar = toupper(*currChar);
        currChar++;

    }

    return;

}