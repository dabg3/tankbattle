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

void draw_initial_position(SDL_Surface *surface) {
        Uint32 *pixels = surface->pixels;
        for (int i = 0; i < 640*480; i++) {
                pixels[i] = 0xFF948B89;
        }
        // draw tank
        Uint32 tank_color = 0xFFA4C035;
        int border_offset_px = 40;
        Uint32* start_top_left = pixels + 240 * 640 + border_offset_px;
        for (int i = 0; i < 10; i++) {
                Uint32 *row_pos = (start_top_left + (i * 640));
                for (int j = 0; j < 20; j++) {
                        *(row_pos + j) = tank_color;
                }
        }
        // TODO: cannon
        Uint32 cannon_color = 0xFF44633F;
        start_top_left += 4 * 640 + 12;
        for (int i = 0; i < 2; i++) {
                Uint32* row_pos = (start_top_left + (i * 640));
                for (int j = 0; j < 15; j++) {
                        *(row_pos + j) = cannon_color;
                }                                           
        }
        // draw wall
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
        SDL_Surface *surface =  SDL_CreateRGBSurfaceWithFormat(0, 
                                                               640, 480, 
                                                               32, 
                                                               SDL_PIXELFORMAT_ARGB8888);
        draw_initial_position(surface);
        SDL_Texture *texture = SDL_CreateTexture(renderer,
                                                 SDL_PIXELFORMAT_ARGB8888,
                                                 SDL_TEXTUREACCESS_STREAMING,
                                                 640, 480);
        SDL_Event event;
        SDL_bool quit = SDL_FALSE;
        Uint32 *pixels = surface->pixels;
        while(!quit) {
                while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                                case SDL_QUIT:
                                        quit = SDL_TRUE;
                                        break;
                        }
                }
                SDL_RenderClear(renderer);
                SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof (Uint32));
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
                SDL_Delay(10);
        }
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        printf("%s\n", SDL_GetError());
        return 0;
}
