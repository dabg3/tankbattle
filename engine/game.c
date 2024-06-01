#include "engine.h"

SDL_bool process_input(SDL_Event event, struct game_state *state) {
        SDL_Scancode code = event.key.keysym.scancode;
        if (event.type == SDL_QUIT) {
                return SDL_TRUE;
        }
        if (code >= SDL_NUM_SCANCODES || get_action(code) == NULL) {
                return SDL_FALSE;
        }
        // with collision detection
        //struct game_state_info new = allocate_game_state();
        //memcpy(new.state, state, new.size);
        get_action(code)(state);
        return SDL_FALSE;
}

void launch_game(SDL_Renderer *renderer) {
        struct game_state_info state_info = allocate_game_state();
        struct game_state *state = state_info.state;
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
