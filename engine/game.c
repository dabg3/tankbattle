#include "engine.h"
#include "internals.h"

#define CONCURRENT_CHANGES 8

        // this is gonna be moved somewhere
        //struct game_state_info new = allocate_game_state();
        //memcpy(new.state, state, new.size);

SDL_bool handle_input(SDL_Event event, 
                       void (*actions[CONCURRENT_CHANGES])(struct game_state *)) {
        SDL_Scancode code = event.key.keysym.scancode;
        if (event.type == SDL_QUIT) {
                return SDL_TRUE;
        }
        if (code >= SDL_NUM_SCANCODES || get_action(code) == NULL) {
                return SDL_FALSE;
        }
        if (event.type == SDL_KEYDOWN) {
                printf("down %d\n", code);
                ptrdiff_t i = 0;
                for (; actions[i] != get_action(code) 
                                && i < CONCURRENT_CHANGES; i++) {}
                if (i < CONCURRENT_CHANGES) {
                       return SDL_FALSE; //already present 
                }
                // insert
                for (i = 0; actions[i] != NULL 
                                && i < CONCURRENT_CHANGES; i++) {}
                // TODO if (i >= CONCURRENT_CHANGES) {error}
                actions[i] = get_action(code);
                printf("%lu\n", i);
        } else if (event.type == SDL_KEYUP) {
                printf("up %d\n", code);
                ptrdiff_t i = 0;
                for (; actions[i] != get_action(code) 
                                && i < CONCURRENT_CHANGES; i++) {}
                // TODO if (i >= CONCURRENT_CHANGES) {error}
                printf("%lu\n", i);
                actions[i] = NULL;
        }
        return SDL_FALSE;
}

void apply_inputs(struct game_state *state, 
                  void (*actions[CONCURRENT_CHANGES])(struct game_state *state)) {
        for (ptrdiff_t i = 0; i < CONCURRENT_CHANGES; i++) {
                if (actions[i] != NULL) {
                        actions[i](state);
                }
        }
}

void update_obj(struct game_object *obj) {
        if (obj->update) {
                obj->update(obj);
        }
}

#define MS_PER_FRAME 32 

void launch_game(SDL_Renderer *renderer) {
        struct game_state_info state_info = allocate_game_state();
        struct game_state *state = state_info.state;
        init_game_state(state);
        SDL_Event event;
        SDL_bool quit = SDL_FALSE;
        void (*actions[CONCURRENT_CHANGES])(struct game_state *) = { NULL };
        Uint64 frame = 0;
        while(!quit) {
                Uint64 tick = SDL_GetTicks();
                while (SDL_PollEvent(&event)) {
                        quit = handle_input(event, actions);
                }
                apply_inputs(state, actions);
                apply_game_objs(update_obj);
                redraw(renderer, state);
                // gdb bug ? SDL_Delay(tick + MS_PER_FRAME - SDL_GetTicks());
                frame++;

        }
        empty_and_free_game_objs();
        destroy_game_state(state);
}
