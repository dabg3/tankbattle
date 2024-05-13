#include "tankbattle.h"
#include <stdio.h>

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

struct State * init_game_state() {
        SDL_Rect tank1_pos = { 20, 240, 20, 25};
        SDL_Rect tank2_pos = { 600, 240, 20, 25};
        struct State *state = malloc(sizeof(struct State));
        state->tank1_pos = tank1_pos;
        state->tank1_rotation_deg = -90;
        state->tank2_pos = tank2_pos;
        state->tank2_rotation_deg = 90;
        return state;
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
        // load background
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

        struct State *state = init_game_state();

        SDL_Event event;
        SDL_bool quit = SDL_FALSE;
        while(!quit) {
                while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                                case SDL_QUIT:
                                        quit = SDL_TRUE;
                                        break;
                                case SDL_KEYDOWN:
                                        if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                                                state->tank1_pos.x += 1;
                                        } 
                        }
                }
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, background_txtr, NULL, NULL);
                SDL_RenderCopyEx(renderer, tank1_txtr, NULL, &state->tank1_pos, state->tank1_rotation_deg, NULL, 0);
                SDL_RenderCopyEx(renderer, tank2_txtr, NULL, &state->tank2_pos, state->tank2_rotation_deg, NULL, 0);
                SDL_RenderPresent(renderer);
                SDL_Delay(10);
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
