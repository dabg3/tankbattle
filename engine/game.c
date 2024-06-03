#include "engine.h"

#define CONCURRENT_CHANGES 8

        // this is gonna be moved somewhere
        //struct game_state_info new = allocate_game_state();
        //memcpy(new.state, state, new.size);

SDL_bool process_input(SDL_Event event, 
                       void (*action[CONCURRENT_CHANGES])(struct game_state *)) {
        SDL_Scancode code = event.key.keysym.scancode;
        if (event.type == SDL_QUIT) {
                return SDL_TRUE;
        }
        if (code >= SDL_NUM_SCANCODES || get_action(code) == NULL) {
                return SDL_FALSE;
        }
        if (event.type == SDL_KEYDOWN) {
                ptrdiff_t i = 0;
                for (; action[i] != get_action(code) 
                                && i < CONCURRENT_CHANGES; i++) {}
                if (i < CONCURRENT_CHANGES) {
                       return SDL_FALSE; //already present 
                }
                // insert
                for (i = 0; action[i] != NULL 
                                && i < CONCURRENT_CHANGES; i++) {}
                // TODO if (i >= CONCURRENT_CHANGES) {error}
                action[i] = get_action(code);
        } else if (event.type == SDL_KEYUP) {
                ptrdiff_t i = 0;
                for (; action[i] != get_action(code) 
                                && i < CONCURRENT_CHANGES; i++) {}
                // TODO if (i >= CONCURRENT_CHANGES) {error}
                action[i] = NULL;
        }
        return SDL_FALSE;
}

void launch_game(SDL_Renderer *renderer) {
        struct game_state_info state_info = allocate_game_state();
        struct game_state *state = state_info.state;
        init_game_state(state);
        SDL_Event event;
        SDL_bool quit = SDL_FALSE;
        void (*actions[CONCURRENT_CHANGES])(struct game_state *) = { NULL };
        while(!quit) {
                while (!quit && SDL_PollEvent(&event)) {
                        quit = process_input(event, actions);
                }
                // update state
                for (ptrdiff_t i = 0; i < CONCURRENT_CHANGES; i++) {
                        if (actions[i] != NULL) {
                                actions[i](state);
                        }
                }
                
                redraw(renderer, state);
        }
        destroy_game_state(state);
}
