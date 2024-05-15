#include "tankbattle.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void log_hw_info() {
        printf("current driver: %s\n", SDL_GetCurrentVideoDriver());
        printf("SDL drivers available:\n");
        for(int i = 0; i < SDL_GetNumVideoDrivers(); i++) {
                printf("- %s\n", SDL_GetVideoDriver(i));
        }
}

void log_win_info(SDL_Window *window) {
        int w = 0, h = 0;
        SDL_GetWindowSizeInPixels(window, &w, &h);
        printf("window title: %s\n", SDL_GetWindowTitle(window));
        printf("window size: %d x %d\n", w, h);
        SDL_GetWindowPosition(window, &w, &h);
        printf("window pos: %d x %d\n", w, h);
}

struct global_state * init_game_state(SDL_Texture *textures[]) {
        SDL_FRect tank1_pos = { 0, 0, 20, 25};
        SDL_FRect tank2_pos = { 600, 240, 20, 25};
        struct global_state *state = malloc(sizeof(struct global_state));
        state->tanks[0].pos = tank1_pos;
        state->tanks[0].rotation_deg = 0;
        state->tanks[0].move_direction = NONE;
        state->tanks[0].rotation_direction = NONE;
        state->textures[0] = textures[0];
        state->tanks[1].pos = tank2_pos;
        state->tanks[1].rotation_deg = 0;
        state->tanks[1].move_direction= NONE;
        state->tanks[1].rotation_direction= NONE;
        state->textures[1] = textures[1];
        return state;
}

// this may be simplified with some trigonometry
void move(struct global_state* state) {
        int x_direction;
        int y_direction;
        int q = quadrant(state->tanks[0].rotation_deg);
        switch (q) {
                case TOP_LEFT:
                        x_direction = 1;
                        y_direction = -1;
                        break;
                case TOP_RIGHT:
                        x_direction = -1;
                        y_direction = -1;
                        break;
                case BOTTOM_LEFT:
                        x_direction = -1;
                        y_direction = 1;
                        break;
                case BOTTOM_RIGHT:
                        x_direction = 1;
                        y_direction = 1;
                        break;
        }
        float incl = inclination_degrees90(state->tanks[0].rotation_deg) * M_PI / 180;
        float inc_x = TANK_SPEED * cosf(incl) * state->tanks[0].move_direction;
        float inc_y = TANK_SPEED * sinf(incl) * state->tanks[0].move_direction;
        state->tanks[0].pos.x += inc_x * x_direction;
        state->tanks[0].pos.y += inc_y * y_direction;
        state->tanks[0].rotation_deg += state->tanks[0].rotation_direction;
        if (check_collision(state->tanks[0].pos, state->tanks[0].rotation_deg, 
                            state->tanks[1].pos, state->tanks[1].rotation_deg)) {
                // rollback
                state->tanks[0].pos.x -= inc_x * x_direction;
                state->tanks[0].pos.y -= inc_y * y_direction;
                state->tanks[0].rotation_deg -= state->tanks[0].rotation_direction;
        }
}

int main(void) {
        SDL_Init(SDL_INIT_VIDEO);
        log_hw_info();
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
        if (window == NULL || renderer == NULL) {
                printf("error: %s\n", SDL_GetError());
        }
        log_win_info(window);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, 640, 480);
        // load background TODO: better paths
        SDL_Surface *background_srfc = SDL_LoadBMP("../assets/grass.bmp");
        SDL_Texture *background_txtr = SDL_CreateTextureFromSurface(renderer, background_srfc);
        SDL_FreeSurface(background_srfc);
        // load tank 1
        SDL_Surface *tank1_srfc = SDL_LoadBMP("../assets/tank_green.bmp");
        SDL_Texture *tank1_txtr = SDL_CreateTextureFromSurface(renderer, tank1_srfc);
        SDL_FreeSurface(tank1_srfc);
        // load tank 2
        SDL_Surface *tank2_srfc = SDL_LoadBMP("../assets/tank_red.bmp");
        SDL_Texture *tank2_txtr = SDL_CreateTextureFromSurface(renderer, tank2_srfc);
        SDL_FreeSurface(tank2_srfc);
        // top margin for scoreboard
        SDL_Rect bckg_placement = {0, 40, 640, 440};

        SDL_Texture *textures[] = {tank1_txtr, tank2_txtr};
        struct global_state *state = init_game_state(textures);
        
        Uint64 tick = SDL_GetTicks64();

        SDL_Event event;
        SDL_bool quit = SDL_FALSE;
        while(!quit) {
                // ugly input processor
                while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                                case SDL_QUIT:
                                        quit = SDL_TRUE;
                                        break;
                                case SDL_KEYDOWN:
                                        if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                                                state->tanks[0].rotation_direction = RIGHT;
                                                break;
                                        } 
                                        if(event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                                                state->tanks[0].rotation_direction = LEFT;
                                                break;
                                        } 
                                        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                                                state->tanks[0].move_direction = FORWARD;
                                                break;
                                        }
                                        if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                                                state->tanks[0].move_direction = BACKWARD;
                                                break;
                                        }
                                case SDL_KEYUP:
                                        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT 
                                                        || event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                                                state->tanks[0].rotation_direction = NONE;
                                                break;
                                        }
                                        if (event.key.keysym.scancode == SDL_SCANCODE_UP
                                                        || event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                                                state->tanks[0].move_direction = NONE;
                                                break;
                                        }
                        }
                }
                // ugly state update
                move(state);
                // ugly rendering
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, background_txtr, NULL, &bckg_placement);
                for (int i = 0; i < 2; i++) {
                        SDL_RenderCopyExF(renderer, state->textures[i], NULL, &state->tanks[i].pos, state->tanks[i].rotation_deg, NULL, 0);
                }
                SDL_RenderPresent(renderer);
                // static 60fps
                tick += 1000 / 60;
                Uint64 delay_time = tick - SDL_GetTicks64();
                if (delay_time >= 0) {
                        SDL_Delay(delay_time);
                } else {
                        printf("WARNING: game is running slower than fps set\n");
                }
        }
        free(state);
        SDL_DestroyTexture(background_txtr);
        SDL_DestroyTexture(tank1_txtr);
        SDL_DestroyTexture(tank2_txtr);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        printf("%s\n", SDL_GetError());
        return 0;
}
