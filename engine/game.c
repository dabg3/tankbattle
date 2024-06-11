#include "engine.h"
#include "internals/internals.h"

#define CONCURRENT_CHANGES 8

        // this is gonna be moved somewhere
        //struct game_state_info new = allocate_game_state();
        //memcpy(new.state, state, new.size);

SDL_bool handle_input(SDL_Event event, 
                      struct action actions[CONCURRENT_CHANGES]) {
        SDL_Scancode code = event.key.keysym.scancode;
        if (event.type == SDL_QUIT) {
                return SDL_TRUE;
        }
        if (code >= SDL_NUM_SCANCODES || get_action(code).fn == NULL) {
                return SDL_FALSE;
        }
        if (event.type == SDL_KEYDOWN) {
                printf("down %d\n", code);
                ptrdiff_t i = 0;
                for (; actions[i].fn != get_action(code).fn 
                                && i < CONCURRENT_CHANGES; i++) {}
                if (i < CONCURRENT_CHANGES) {
                       return SDL_FALSE; //already present 
                }
                // insert
                for (i = 0; actions[i].fn != NULL 
                                && i < CONCURRENT_CHANGES; i++) {}
                // TODO if (i >= CONCURRENT_CHANGES) {error}
                actions[i] = get_action(code);
                printf("%lu\n", i);
        } else if (event.type == SDL_KEYUP) {
                printf("up %d\n", code);
                ptrdiff_t i = 0;
                for (; actions[i].fn != get_action(code).fn 
                                && i < CONCURRENT_CHANGES; i++) {}
                // TODO if (i >= CONCURRENT_CHANGES) {error}
                printf("%lu\n", i);
                actions[i] = (struct action) {NULL};
        }
        return SDL_FALSE;
}

void apply_inputs(struct game_state *state, 
                  struct action actions[CONCURRENT_CHANGES],
                  Uint64 tick) {
        for (ptrdiff_t i = 0; i < CONCURRENT_CHANGES; i++) {
                if (actions[i].fn == NULL) {
                        continue;
                }
                if (actions[i].last_invocation && actions[i].last_invocation + actions[i].msdelay > tick) {
                        continue;
                }
                actions[i].fn(state);
                actions[i].last_invocation = tick;
        }
}

void update_obj(void *o) {
        struct game_object *obj = o;
        if (obj->update) {
                obj->update(obj);
        }
}

#define MS_PER_FRAME 32 

#include "internals/mem.h"

void launch_game(SDL_Renderer *renderer) {
        struct game_state_info state_info = allocate_game_state();
        struct game_state *state = state_info.state;
        init_game_state(state);
        SDL_Event event;
        SDL_bool quit = SDL_FALSE;
        struct action actions[CONCURRENT_CHANGES] = { NULL };
        Uint64 frame = 0;
        while(!quit) {
                Uint64 tick = SDL_GetTicks();
                while (SDL_PollEvent(&event)) {
                        quit = handle_input(event, actions);
                }
                apply_inputs(state, actions, tick);
                apply(&game_objs_head, update_obj);
                // gdb bug ? SDL_Delay(tick + MS_PER_FRAME - SDL_GetTicks());
                collect_garbage(&game_objs_head);
                collect_garbage(&render_objs_head);
                redraw(renderer);
                frame++;
        }
        destroy_game_state(state);
}
