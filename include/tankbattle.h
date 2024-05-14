#include <SDL2/SDL.h>

enum movement {
        NONE = 0,
        FORWARD = 1,
        BACKWARD = -1,
        RIGHT = 1,
        LEFT = -1,
};

struct tank_state {
        SDL_FRect pos;
        int rotation_deg;
        enum movement move_direction;
        enum movement rotation_direction;
};

struct global_state {
        SDL_Texture *textures[2];
        struct tank_state tanks[2];
};

struct global_state * init_game_state(SDL_Texture *textures[]);
void move(struct tank_state* state);

