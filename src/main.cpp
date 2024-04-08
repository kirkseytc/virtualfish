#include <curses.h>
#include <unistd.h>

#include <string>
#include <cstdlib>
#include <ctime>

#include "fish.hpp"

#define MAX_FISH 10

using std::string;

void toUpperCStr(char*);

int main(void){

    srand(time(0));

    initscr();

    if(has_colors() == false){
        endwin();
        printf("Terminal doesn't support colors.\n");
        return 0;
    }
    start_color();
    
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    init_pair(10, COLOR_BLUE, COLOR_BLACK);

    cbreak();
    noecho();
    halfdelay(1);
    curs_set(0);

    const unsigned int row = getmaxy(stdscr);
    const unsigned int col = getmaxx(stdscr);

    if(row < 26 || col < 80){
        endwin();
        printf("Terminal to small. Resize (min: 80 cols x 26 lines, current: %d cols and %d lines) and re-run.\n", col, row);
        return 0;
    }

    box(stdscr, 0, 0);

    const unsigned int TANK_W = (col - 3), TANK_H = (row - 3);

    Fish* fishes[MAX_FISH];
    short currentFishes = 0;

    for(short s = 0; s < MAX_FISH; s++){
        fishes[s] == nullptr;
    }

    while(true){

        if(getch() == 27){ // ESC Pressed

            echo();
            curs_set(1);
            halfdelay(0);

            char userIn[col - 2];

            for(unsigned int i = 0; i < col; i++){
                mvaddch((row - 1), i, ' ');
            }

            mvprintw((row - 1),0, ": ");
            getnstr(userIn, col - 3);

            toUpperCStr(userIn);

            string strIn(userIn);

            if(strIn == "QUIT" || strIn == "Q" || strIn == "EXIT"){
                break;
            }

            if(strIn == "FISH" || strIn == "F"){
                if(currentFishes < MAX_FISH){
                    fishes[currentFishes] = new Fish(TANK_W, TANK_H);
                    currentFishes++;
                } else {
                    mvprintw((row - 1), 0, "Max Fish Capacity Reached.");
                    refresh();
                    sleep(2);
                }
            }

            noecho();
            curs_set(0);
            halfdelay(1);
            box(stdscr, 0, 0);
        }

        for(short s = 0; s < currentFishes; s++){

            Fish* f = fishes[s];

            mvprintw((f->true_y() + 1), (f->get_pos_x() + 1), f->get_g_erase().c_str());
            f->simulate();
            attron(COLOR_PAIR(s + 1));
            mvprintw((f->true_y() + 1), (f->get_pos_x() + 1), f->get_g_curr().c_str());
            attroff(COLOR_PAIR(s + 1));

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