#ifndef FISH_HPP
#define FISH_HPP

#define FISH_UP 1
#define FISH_DOWN -1
#define FISH_RIGHT 1
#define FISH_LEFT -1
#define FISH_FLIP -1

#define FISH_COLOR_MAX_ID 9

#include <string>

using std::string;

typedef class _fish {

    public:
        _fish(const unsigned int, const unsigned int, const short);

        void simulate();

        int get_pos_x() { return this->pos_x; }
        int get_pos_y() { return this->pos_y; }

        string get_g_curr() { return this->g_curr; }
        string get_g_erase() { return this->g_erase; }

        short get_color(){ return color; }

    private:
        string g_right;
        string g_left;

        int spawn_pos_x, spawn_pos_y;
        int pos_x, pos_y;
        double true_pos_x, true_pos_y;

        double vel_x, vel_y;
        double t_pos_x, t_pos_y;

        int max_x, max_y;

        short color;

        string g_curr;
        string g_erase;

        void set_pos_x(const int);
        void set_pos_y(const int);
        void set_graphics(string, string);
        void set_color(short color);
        void gen_g_erase();
        void fish_path();

} Fish;

#endif