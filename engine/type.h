#include <SDL2/SDL.h>

struct render_object {
        SDL_Texture *texture;
        SDL_Rect srcrect; 
        int rotation; 
};

#ifndef MAX_VERTICES
#define MAX_VERTICES 8
#endif

struct game_object {
        struct render_object *render;
        SDL_FRect position; //bounding box
        double rotation;
        unsigned int vsize;
        //fixed dim otherwise cannot be used on arrays - C standard §6.7.2.1
        SDL_FPoint vertices[MAX_VERTICES]; 
        void (*update)(struct game_object *);
};
