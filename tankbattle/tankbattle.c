#include "tankbattle.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

void load_render_objs(SDL_Renderer *renderer) {
        // load tank 1
        char tank1_bmp[] = "../assets/tank_green.bmp";
        SDL_Texture *tank1_txtr = load_texture(renderer, tank1_bmp);
        load_render_obj(tank1_txtr, NULL, -90); 
        // load tank 2
        char tank2_bmp[] = "../assets/tank_red.bmp";
        SDL_Texture *tank2_txtr = load_texture(renderer, tank2_bmp);
        load_render_obj(tank2_txtr, NULL, -90);
        // load bullet
        char bullet_bmp[] = "../assets/bullet.bmp";
        SDL_Texture *bullet_txtr = load_texture(renderer, bullet_bmp);
        load_render_obj(bullet_txtr, NULL, -90);
}

struct game_state * allocate_game_state() {
        return malloc(sizeof(struct game_state));
}

void destroy_game_state(struct game_state *state) {
        destroy_game_obj(state->p1);
        destroy_game_obj(state->p2);
        for (int i = 0; i < MAX_FLYING_BULLETS; i++) {
                destroy_game_obj(state->bullets[i]);
        }
        for(int i = 0; i < state->ssize; i++) {
                destroy_game_obj(state->surroundings[i]);
        }
        free(state);
}

void init_game_state(struct game_state *state) {
        SDL_Rect p1pos = {0, 0, 40, 50};
        struct game_object *p1 = 
                load_game_obj(get_render_obj(0), p1pos, 0, 0, NULL);
        SDL_Rect p2pos = {600, 240, 40, 50};
        struct game_object *p2 = 
                load_game_obj(get_render_obj(1), p2pos, 0, 0, NULL);
        state->p1 = p1;
        state->p2 = p2;
        state->ssize = 0;
}

// TODO: actual implementation
struct game_state * rotate_p1_right(struct game_state *state) {
        struct game_state *new = malloc(sizeof(struct game_state));
        memcpy(new->p1, state->p1, sizeof(struct game_object));
        new->p1->rotation += RIGHT;
        return new;
}

void redraw(SDL_Renderer *renderer, struct game_state *state) {
        SDL_RenderClear(renderer);
        // draw p1
        struct game_object *p1 = state->p1;
        SDL_RenderCopyEx(renderer, p1->render->texture, 
                                   &p1->render->srcrect, 
                                   &p1->position, 
                                   p1->rotation, 
                                   NULL, 0); 
        //draw p2
        struct game_object *p2 = state->p2;
        SDL_RenderCopyEx(renderer, p2->render->texture, 
                                   &p2->render->srcrect, 
                                   &p2->position, 
                                   p2->rotation, 
                                   NULL, 0); 
        SDL_RenderPresent(renderer);
}

int main(void) {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_CreateWindowAndRenderer(0, 0, 
                                    SDL_WINDOW_FULLSCREEN_DESKTOP, 
                                    &window, &renderer);
        if (window == NULL || renderer == NULL) {
                printf("error: %s\n", SDL_GetError());
        }
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        // engine stuff
        load_render_objs(renderer);
        launch_game(renderer);
        // end
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        printf("%s\n", SDL_GetError());
        return 0;
}
