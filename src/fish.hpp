#ifndef FISH_HPP
#define FISH_HPP

#include <string>
#include <cmath>

using std::string;

typedef class _fish {

    public:
        _fish(const int, const int, const unsigned int, const unsigned int);
        _fish(const unsigned int, const unsigned int);

        void simulate();

        int true_y();

        int get_pos_x() { return this->pos_x; }
        int get_pos_y() { return this->pos_y; }

        string get_g_curr() { return this->g_curr; }
        string get_g_erase() { return this->g_erase; }

    private:
        string g_right;
        string g_left;

        int pos_x, pos_y;
        int vel_x, vel_y;
        unsigned int max_x, max_y;

        string g_curr;
        string g_erase;

        void set_pos_x(const int);
        void set_pos_y(const int);
        void set_graphics(string, string);
        void gen_g_erase();

} Fish;

_fish::_fish(const int pos_x, const int pos_y, const unsigned int max_x, const unsigned int max_y){

    this->max_x = max_x - (this->g_curr.size() + 1);
    this->max_y = max_y;

    set_pos_x(pos_x);
    set_pos_y(pos_y);
    
    this->vel_x = 0;
    this->vel_y = 0;

    set_graphics("><>", "<><");
    gen_g_erase();

}

_fish::_fish(const unsigned int max_x, const unsigned int max_y){

    this->max_x = max_x - (this->g_curr.size() + 1);
    this->max_y = max_y;

    set_pos_x(rand() % this->max_x);
    set_pos_y(rand() % this->max_y);

    this->vel_x = 0;
    this->vel_y = 0;

    set_graphics("><>", "<><");
    gen_g_erase();

}

/**
 * This method simulates the fish's activities with random numbers.
 * Make sure srand() is seeded.
*/
void _fish::simulate(){

    // direction calcs
    this->vel_y = (rand() % 3) - 1; // -1 to 1;
    
    if(this->vel_y){ // if y isn't zero

        short s = rand() % 2;

        if(s){
            this->vel_x = this->vel_y;
        } else {
            this->vel_x = this->vel_y * -1;
        }

    } else {
        this->vel_x = (rand() % 3) - 1; // -1 to 1;
    }

    // appling velocities
    this->pos_x += this->vel_x;
    this->pos_y += this->vel_y;

    // out of bounds errors
    if(pos_x > this->max_x || pos_x < 0){
        this->pos_x -= this->vel_x * 2;
    }

    if(pos_y > this->max_y || pos_y < 0){
        this->pos_y -= this->vel_y * 2;
    }

    // setting fish graphic
    switch(this->vel_x){
        case -1: // heading left;
            this->g_curr = this->g_left;
            break;
        case 1: // heading right;
            this->g_curr = this->g_right;
            break;
    }

}

int _fish::true_y(){

    return -1 * (this->pos_y - this->max_y);

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

#endif