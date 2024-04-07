#ifndef FISH_HPP
#define FISH_HPP

#include <string>
#include <cmath>

using std::string;

typedef struct _fish {

    public:
        int pos_x, pos_y;
        int vel_x, vel_y;

        unsigned int max_x, max_y;

        string g_curr;
        string g_erase;

        _fish(const int, const int, const unsigned int, const unsigned int);

        void simulate();
        int true_y();

    private:
        string g_right;
        string g_left;

} Fish;

_fish::_fish(const int pos_x, const int pos_y, const unsigned int max_x, const unsigned int max_y){

    this->pos_x = pos_x;
    this->pos_y = pos_y;

    this->vel_x = 0;
    this->vel_y = 0;

    this->g_left = "<><";
    this->g_right = "><>";
    this->g_curr = this->g_right;
    this->g_erase = "";

    for(int i = 0; i < this->g_curr.size(); i++){
        this->g_erase += " ";
    }

    this->max_x = max_x - (this->g_curr.size() + 1);
    this->max_y = max_y;

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

#endif