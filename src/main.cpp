#include <curses.h>
#include <unistd.h>

#include <string>
#include <cstdlib>
#include <ctime>

#include "fish.hpp"

#define MAX_FISH 10

using std::string;

void toUpperCStr(char*);
void render_water(const unsigned int);
void render_depth();
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

    const unsigned int TANK_W = (col - 5), TANK_H = (row - 6);
    render_depth();
    render_water(TANK_W);

    Fish* fishes[MAX_FISH];
    short currentFishes = 0;

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

            mvprintw(translate_pos_y(f->get_pos_y()), translate_pos_x(f->get_pos_x()), f->get_g_erase().c_str());
            f->simulate();
            attron(COLOR_PAIR(s + 1));
            mvprintw(translate_pos_y(f->get_pos_y()), translate_pos_x(f->get_pos_x()), f->get_g_curr().c_str());
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

void render_water(const unsigned int TANK_W){

    char water_pat[] = {'.', '-', '.', '_'};

    for(int i = 0; i < (getmaxx(stdscr) - 2); i++){

        mvaddch(1, i + 1, water_pat[i % 4]);

    }

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

void render_depth(){

    int tank_bottom_y = getmaxy(stdscr) - 1;
    int tank_r_wall_x = getmaxx(stdscr) - 1;  

    mvaddch(tank_bottom_y - 1, 1, '/');
    mvaddch(tank_bottom_y - 1, tank_r_wall_x - 1, '\\');
    mvaddch(tank_bottom_y - 2, 2, ACS_LLCORNER);
    mvaddch(tank_bottom_y - 2, tank_r_wall_x - 2, ACS_LRCORNER);

    for(int i = 3; i < tank_r_wall_x - 2; i++){
        mvaddch(tank_bottom_y - 2, i, ACS_HLINE);
    }

    for(int i = tank_bottom_y - 3; i > 0; i--){
        mvaddch(i, 2, ACS_VLINE);
    }
    
    for(int i = tank_bottom_y - 3; i > 0; i--){
        mvaddch(i, tank_r_wall_x - 2, ACS_VLINE);
    }

}