#include "engine.h"

SDL_bool process_input(SDL_Event event, struct game_state *state) {
        SDL_Scancode code = event.key.keysym.scancode;
        if (event.type == SDL_QUIT) {
                return SDL_TRUE;
        }
        if (code >= SDL_NUM_SCANCODES || get_action(code) == NULL) {
                return SDL_FALSE;
        }
        return SDL_FALSE;
}

void launch_game(SDL_Renderer *renderer) {
        struct game_state *state = allocate_game_state();
        init_game_state(state);
        SDL_Event event;
        SDL_bool quit = SDL_FALSE;
        while(!quit) {
                while (!quit && SDL_PollEvent(&event)) {
                        quit = process_input(event, state);
                }
                redraw(renderer, state);
        }
        destroy_game_state(state);
}
