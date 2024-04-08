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

        int spawn_pos_x, spawn_pos_y;
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

#endif