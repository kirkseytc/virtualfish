#include <curses.h>
#include <unistd.h>

#include <string>
#include <cstdlib>
#include <ctime>

#include "fish.hpp"

#define MAX_FISH 10
#define COLOR_ORANGE 8
#define COLOR_BROWN 9

using std::string;

void INIT_COLOR_PAIRS();
void toUpperCStr(char*);
void render_water();
int translate_pos_x(const int);
int translate_pos_y(const int);

int main(void){

    srand(time(0));

    initscr();

    if(has_colors() == false){
        endwin();
        printf("Terminal doesn't support colors.\n");
        return 0;
    }
    start_color();
    
    INIT_COLOR_PAIRS();

    cbreak();
    noecho();
    halfdelay(1);
    curs_set(0);

    const unsigned int row = getmaxy(stdscr);
    const unsigned int col = getmaxx(stdscr);

    if(row < 24 || col < 80){
        endwin();
        printf("Terminal to small. Resize (min: 80 cols x 26 lines, current: %d cols and %d lines) and re-run.\n", col, row);
        return 0;
    }

    attron(A_BOLD);
    box(stdscr, 0, 0);
    attroff(A_BOLD);

    const unsigned int TANK_W = (col - 5), TANK_H = (row - 6);
    render_water();

    Fish* fishes[MAX_FISH];
    short currentFishes = 0;


    while(true){

        char inputChar = getch();

        if(inputChar == 27 || inputChar == 58){ // ESC or : Pressed

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
                    short color = rand() % 7 + 1;
                    fishes[currentFishes] = new Fish(TANK_W, TANK_H, color);
                    currentFishes++;
                } else {
                    mvprintw((row - 1), 0, "Max Fish Capacity Reached.");
                    refresh();
                    sleep(2);
                }
            }

            if(strIn == "CLEAR" || strIn == "C"){
                
                for(short s = 0; s < currentFishes; s++){
                    
                    Fish* f = fishes[s];

                    mvprintw(translate_pos_y(f->get_pos_y()), translate_pos_x(f->get_pos_x()), f->get_g_erase().c_str());

                    delete f;

                }

                currentFishes = 0;

            }

            if(strIn == "MAX" || strIn == "M"){

                for(short s = currentFishes; s < MAX_FISH; s++){

                    short color = rand() % 7 + 1;
                    fishes[currentFishes] = new Fish(TANK_W, TANK_H, color);
                    currentFishes++;

                }

            }

            noecho();
            curs_set(0);
            halfdelay(1);
            box(stdscr, 0, 0);
        }

        for(short s = 0; s < currentFishes; s++){

            Fish* f = fishes[s];

            mvprintw(translate_pos_y(f->get_pos_y()), translate_pos_x(f->get_pos_x()), f->get_g_erase().c_str());
            f->simulate();
            attron(COLOR_PAIR(f->get_color()) | A_BOLD);
            mvprintw(translate_pos_y(f->get_pos_y()), translate_pos_x(f->get_pos_x()), f->get_g_curr().c_str());
            attroff(COLOR_PAIR(f->get_color()) | A_BOLD);

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

void render_water(){

    char water_pat[] = {'.', '-', '.', '_'};

    attron(COLOR_PAIR(6) | A_BOLD);

    for(int i = 0; i < (getmaxx(stdscr) - 2); i++){

        mvaddch(1, i + 1, water_pat[i % 4]);

    }

    attroff(COLOR_PAIR(6) | A_BOLD);

}

int translate_pos_x(const int x){

    return (x + 3);

}

int translate_pos_y(const int y){

    int t_pos = y;
    t_pos += 3;

    unsigned int scr_height = getmaxy(stdscr) - 1;

    t_pos -= scr_height;

    t_pos *= -1;

    return t_pos;

}

void INIT_COLOR_PAIRS(){

    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);

}