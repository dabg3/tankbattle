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


int main(void) {
        SDL_Init(SDL_INIT_VIDEO);
        log_hw_info();
        SDL_Window *window = SDL_CreateWindow("test", 
                                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                              1280, 720, 
                                              SDL_WINDOW_RESIZABLE & SDL_WINDOW_BORDERLESS);
        if (window == NULL) {
                printf("error: %s\n", SDL_GetError());
        } 
        log_win_info(window);
        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
        //SDL_Surface *surface = SDL_CreateRGBSurface(0,640, 480,32,0,0,0,0);
        //SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        //int res = SDL_RenderCopy(renderer, texture, NULL, NULL);
        //if (res != 0) {
        //        printf("%s\n", SDL_GetError());
        //}
        SDL_bool quit = SDL_FALSE;
        SDL_Event event;
        while(!quit) {
                SDL_RenderPresent(renderer);
                SDL_WaitEvent(&event);
                if (event.type == SDL_QUIT) {
                        quit = SDL_TRUE;
                }
        }
        //SDL_DestroyTexture(texture);
        //SDL_FreeSurface(surface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        printf("%s\n", SDL_GetError());
        return 0;
}
