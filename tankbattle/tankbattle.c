#include "tankbattle.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>

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

struct game_state_info allocate_game_state() {
        size_t size = sizeof(struct game_state);
        struct game_state_info new = { malloc(size), size };
        return new;
}

void destroy_game_state(struct game_state *state) {
        // game_object(s) are freed by the engine      
}

void init_game_state(struct game_state *state) {
        SDL_FRect p1pos = {0, 0, 40, 50};
        struct game_object *p1 = 
                load_game_obj(get_render_obj(0), p1pos, 0, 0, NULL, NULL);
        SDL_FRect p2pos = {600, 240, 40, 50};
        struct game_object *p2 = 
                load_game_obj(get_render_obj(1), p2pos, 0, 0, NULL, NULL);
        state->p1 = p1;
        state->p2 = p2;
        for (int i = 0; i < MAX_FLYING_BULLETS; i++) {
                state->bullets[i] = NULL;
        }
        state->ssize = 0;
}

void rotate_p1_left(struct game_state *state) {
        rotate_game_obj(state->p1, COUNTERCLOCKWISE, TANK_ROTATE_SPEED);
}

void rotate_p1_right(struct game_state *state) {
        rotate_game_obj(state->p1, CLOCKWISE, TANK_ROTATE_SPEED);
}

void move_p1_forward(struct game_state *state) {
        move_game_obj(state->p1, FORWARD, TANK_MOVE_SPEED);
}

void move_p1_backward(struct game_state *state) {
        move_game_obj(state->p1, BACKWARD, TANK_MOVE_SPEED);
}

void update_bullet(struct game_object *obj) {
        move_game_obj(obj, FORWARD, BULLET_SPEED);
}

void fire_bullet_p1(struct game_state *state) {
        // find first available slot
        ptrdiff_t i = 0;
        for(; state->bullets[i] != NULL && i < MAX_FLYING_BULLETS; i++) {}
        // instance bullets
        double w = 5;
        double h = 15;
        double x = state->p1->position.x + state->p1->position.w / 2 - w / 2;
        double y = state->p1->position.y + state->p1->position.h / 2 - h / 2;
        SDL_FRect pos = {x, y, w, h};
        state->bullets[i] = load_game_obj(get_render_obj(2), pos, state->p1->rotation, 0, NULL, update_bullet);
        move_game_obj(state->bullets[i], FORWARD, 15);
}

void redraw(SDL_Renderer *renderer, struct game_state *state) {
        //TODO: pass game_object(s) to the engine for rendering
        // too many details exposed
        SDL_RenderClear(renderer);
        // draw p1
        struct game_object *p1 = state->p1;
        SDL_RenderCopyExF(renderer, p1->render->texture, 
                                   &p1->render->srcrect, 
                                   &p1->position, 
                                   p1->rotation + p1->render->rotation, 
                                   NULL, 0); 
        //draw p2
        struct game_object *p2 = state->p2;
        SDL_RenderCopyExF(renderer, p2->render->texture, 
                                   &p2->render->srcrect, 
                                   &p2->position, 
                                   p2->rotation + p2->render->rotation, 
                                   NULL, 0); 
        // draw bullets
        for (int i = 0; i < MAX_FLYING_BULLETS; i++) {
                if (state->bullets[i] == NULL) {
                        continue;
                }
                struct game_object *b = state->bullets[i];
                SDL_RenderCopyExF(renderer, b->render->texture, 
                                  &b->render->srcrect, 
                                  &b->position, 
                                  b->rotation + b->render->rotation, 
                                  NULL, 0); 
        }
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
        register_action(SDL_SCANCODE_RIGHT, &rotate_p1_right);
        register_action(SDL_SCANCODE_LEFT, &rotate_p1_left);
        register_action(SDL_SCANCODE_UP, &move_p1_forward);
        register_action(SDL_SCANCODE_DOWN, &move_p1_backward);
        register_action(SDL_SCANCODE_SPACE, &fire_bullet_p1);
        load_render_objs(renderer);
        launch_game(renderer);
        // end
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        printf("%s\n", SDL_GetError());
        return 0;
}
