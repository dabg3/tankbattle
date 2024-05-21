#include <SDL2/SDL.h>

struct game_object {
        SDL_Texture *texture;
        SDL_Rect pos; //bounding box
        int rotation;
        unsigned int v_size;
        SDL_FPoint vertices[];
};

struct game_object * load_obj(SDL_Renderer *renderer, 
                              char bmp_texture_path[], 
                              SDL_Rect dest,
                              int rotation,
                              int v_size,
                              SDL_FPoint vertices[v_size]) {
        SDL_Surface *s = SDL_LoadBMP(bmp_texture_path);
        // TODO sanity checks
        if (s == NULL) {
                printf("%s\n", SDL_GetError());
        }
        SDL_Texture *t= SDL_CreateTextureFromSurface(renderer, s);
        SDL_FreeSurface(s);
        size_t obj_size = sizeof(struct game_object) + sizeof(SDL_FPoint) * v_size;
        struct game_object *obj = malloc(obj_size);
        *obj = (struct game_object) {t, dest, rotation, v_size};
        memcpy(obj->vertices, vertices, sizeof(SDL_FPoint) * v_size);
        return obj;
}


