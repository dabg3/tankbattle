#include <SDL2/SDL.h>

struct State {
        SDL_Rect tank1_pos;
        SDL_Rect tank2_pos;
        int tank1_rotation_deg;
        int tank2_rotation_deg;
};

struct State * init_game_state();

