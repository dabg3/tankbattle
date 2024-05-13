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

int async_draw(void *d) {
        Uint32* data = (Uint32 *) d;
        int i = 0;
        int color = 0xFFFFFFFF; //white
        while (color > 0xFF000000 && i < 640*480) {
                data[i++] = color;
                if (i == 640 * 480) {
                        i = 0;
                        color -= 10;
                }
                SDL_Delay(1);
        }
        return 0;
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Surface *surface =  SDL_CreateRGBSurfaceWithFormat(0, 
                                                               640, 480, 
                                                               32, 
                                                               SDL_PIXELFORMAT_ARGB8888);
        SDL_Texture *texture = SDL_CreateTexture(renderer,
                                                 SDL_PIXELFORMAT_ARGB8888,
                                                 SDL_TEXTUREACCESS_STREAMING,
                                                 640, 480);
        SDL_bool quit = SDL_FALSE;
        SDL_Event event;
        Uint32 *pixels = surface->pixels;
        SDL_CreateThread(async_draw, "draw", pixels);
        while(!quit) {
                SDL_RenderClear(renderer);
                SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof (Uint32));
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
        }
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        printf("%s\n", SDL_GetError());
        return 0;
}
