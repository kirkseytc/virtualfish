#include "fish.hpp"

_fish::_fish(const int pos_x, const int pos_y, const unsigned int max_x, const unsigned int max_y){

    set_graphics("><>", "<><");
    gen_g_erase();

    this->max_x = max_x - (this->g_curr.size() + 1);
    this->max_y = max_y - 1;

    set_pos_x(pos_x);
    set_pos_y(pos_y);
    
    this->vel_x = 0;
    this->vel_y = 0;

}

_fish::_fish(const unsigned int max_x, const unsigned int max_y){

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
    
}

/**
 * This method simulates the fish's activities with random numbers.
 * Make sure srand() is seeded.
*/
void _fish::simulate(){

    // direction calcs
    fish_path();

    // appling velocities
    this->pos_x += this->vel_x;
    this->pos_y += this->vel_y;

    // out of bounds errors
    if(pos_x > this->max_x || pos_x < 0){
        this->pos_x += this->vel_x * -2;
    }

    if(pos_y > this->max_y || pos_y < 0){
        this->pos_y += this->vel_y * -2;
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
*/
void _fish::fish_path(){

    int prev_vel_x = this->vel_x, prev_vel_y = this->vel_y;

    // bound cases

    if(this->pos_x == 0){ // left wall

        this->vel_x = FISH_RIGHT;

        if(this->pos_y == 0){ // LL corner
            this->vel_y = FISH_UP;
        } else if(this->pos_y == max_y){ // UL corner
            this->vel_y = FISH_DOWN;
        } else { // anywhere else on the wall

            char c = rand() % 2;
            
            if(c){
                this->vel_y = FISH_DOWN;
            } else {
                this->vel_y = FISH_UP;
            }

        }

        return;
    }

    if(this->pos_x == max_x){ // right wall

        this->vel_x = FISH_LEFT;

        if(this->pos_y == 0){ // LR corner
            this->vel_y = FISH_UP;
        } else if(this->pos_y == max_y){ // UR corner
            this->vel_y = FISH_DOWN;
        } else {

            char c = rand() % 2;

            if(c){
                this->vel_y = FISH_DOWN;
            } else {
                this->vel_y = FISH_UP;
            }

        }

        return;
    }

    if(this->pos_y == 0){

        this->vel_y = FISH_UP;
        this->vel_x *= FISH_FLIP;
        return;
    }

    if(this->pos_y == max_y){

        this->vel_y = FISH_DOWN;
        this->vel_x *= FISH_FLIP;
        return;
    }
    
    // normal cases

    switch (prev_vel_y) { // handles y velocity
        case -1: {

            char c1 = rand() % 2;

            if(c1){

                this->vel_y = 1;

            } else {

                this->vel_y = 0;

            }

            break;
        }
        case 0: {

            this->vel_y = (rand() % 3) - 1;
            break;
        }
        case 1: {

            char c2 = rand() % 2;

            if(c2){
            
                this->vel_y = -1;    

            } else {

                this->vel_y = 0;

            }

            break;
        }
    }

    if(this->vel_y){ // we're moving vertically

        switch(prev_vel_x){

            case -1: {

                if(this->vel_y == prev_vel_y){

                    char c3 = rand() % 2;

                    if(c3){

                        this->vel_x = -1;

                    } else {

                        this->vel_x = 1;

                    }

                } else {

                    this->vel_x = -1;

                }

                break;
            }
            case 0: {

                char c4 = rand() % 2;

                if(c4){

                    this->vel_x = -1;

                } else {

                    this->vel_x = 1;

                }

                break;
            }
            case 1: {

                if(this->vel_y == prev_vel_y){

                    char c5 = rand() % 2;

                    if(c5){

                        this->vel_x = -1;

                    } else {

                        this->vel_x = 1;

                    }

                } else {

                    this->vel_x = 1;

                }

                break;
            }
        }

    } else { 

        switch(prev_vel_x){
            
            case -1: {

                char c6 = rand() % 2;

                if(c6){

                    this->vel_x = -1;

                } else {

                    this->vel_x = 0;

                }

                break;
            }
            case 0: {
            
                this->vel_x = (rand() % 3) - 1;
                break;
            }
            case 1: {

                char c7 = rand() % 2;

                if(c7){

                    this->vel_x = 1;

                } else {

                    this->vel_x = 0;

                }

                break;
            }
        }

    }

}