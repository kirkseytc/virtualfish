#include "fish.hpp"



_fish::_fish(const unsigned int max_x, const unsigned int max_y, const short color){

    set_color(color);

    set_graphics("><>", "<><");
    gen_g_erase();

    this->max_x = max_x - (this->g_curr.size() + 1);
    this->max_y = max_y;

    this->spawn_pos_x = rand() % this->max_x;
    this->spawn_pos_y = rand() % this->max_y;

    set_pos_x(this->spawn_pos_x);
    set_pos_y(this->spawn_pos_y);

    this->vel_x = 0;
    this->vel_y = 0;

    this->t_pos_x = this->pos_x;
    this->t_pos_y = this->pos_y;

    this->true_pos_x = pos_x;
    this->true_pos_y = pos_y;
}

/**
 * This method simulates the fish's activities with random numbers.
 * Make sure srand() is seeded.
*/
void _fish::simulate(){

    // direction calcs
    fish_path();

    // appling velocities
    this->true_pos_x += this->vel_x;
    this->true_pos_y += this->vel_y;

    // snaping positions to a grid.
    this->pos_x = (int)this->true_pos_x;
    this->pos_y = (int)this->true_pos_y;

    // setting fish graphic
    if(this->vel_x < 0){
        this->g_curr = this->g_left;
    } else {
        this->g_curr = this->g_right;
    }

}

void _fish::set_pos_x(const int pos_x){

    if(pos_x > this->max_x){

        this->pos_x = this->max_x;

    } else if (pos_x < 0){

        this->pos_x = 0;
 
    } else {

        this->pos_x = pos_x;

    }

}

void _fish::set_pos_y(const int pos_y){

    if(pos_y > this->max_y){

        this->pos_y = this->max_y;

    } else if (pos_y < 0){

        this->pos_y = 0;
 
    } else {

        this->pos_y = pos_y;

    }

}

void _fish::set_graphics(string g_right, string g_left){

    if(g_right.size() != g_left.size()){

        this->g_right = "><>";
        this->g_left = "<><";

    } else {

        this->g_right = g_right;
        this->g_left = g_left;

    }

    this->g_curr = this->g_right;

}

void _fish::gen_g_erase(){

    this->g_erase = "";

    for(unsigned short s = 0; s < g_curr.size(); s++){
        g_erase += " ";
    }

}

/**
 * This method helps the fish move in a less choatic manner.
 * 
 * TODO: Write actual pathing to be less choatic.
*/
void _fish::fish_path(){

    if((t_pos_x - true_pos_x) < 0.5 && (t_pos_y - true_pos_y) < 0.5){ // reached target, pick new target

        t_pos_x += rand() % 51 - 25; // -25 to 25
        t_pos_y += rand() % 21 - 10; // -10 to 10

        if(t_pos_x < 0){
            t_pos_x = 0;
        } else if(t_pos_x > max_x){
            t_pos_x = max_x;
        }

        if(t_pos_y < 0){
            t_pos_y = 0;
        } else if(t_pos_y > max_y){
            t_pos_y = max_y;
        }

        int speed = rand() % 5 + 5; // 5 to 10;

        vel_x = (double)(t_pos_x - pos_x) / (speed * 3);
        vel_y = (double)(t_pos_y - pos_y) / (speed * 3);

    } 

}

void _fish::set_color(short color){

    if(color < 1 || color > FISH_COLOR_MAX_ID){
        this->color = 1;
    } else {
        this->color = color;
    }

}