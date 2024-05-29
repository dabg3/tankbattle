#include "engine.h"

struct render_object * load_render_obj(SDL_Renderer *renderer,
                                       char bmp_texture_path[], 
                                       SDL_Rect src,
                                       int rotation) {
        SDL_Surface *s = SDL_LoadBMP(bmp_texture_path);
        if (s == NULL) {
                return NULL;
        }
        SDL_Texture *t= SDL_CreateTextureFromSurface(renderer, s);
        SDL_FreeSurface(s);
        if (t == NULL) {
                return NULL;
        }
        struct render_object *obj = malloc(sizeof(struct render_object));
        *obj = (struct render_object) {t, src, rotation};
        return obj;
}

struct game_object * load_game_obj(struct render_object *render,
                                   SDL_Rect position,
                                   int rotation,
                                   unsigned int vsize,
                                   SDL_FPoint vertices[vsize]) {
        // render may be null in case the object is present but invisible 
        //TODO: sanity check on position
        if (vsize > MAX_VERTICES) {
                return NULL; //TODO: error msg
        }
        struct game_object *obj = malloc(sizeof(struct game_object));
        *obj = (struct game_object) {render, position, rotation, vsize};
        if (vertices == NULL) {
                vertices = (SDL_FPoint []) {
                        {position.x, position.y},
                        {position.x + position.w, position.y},
                        {position.x + position.w, position.y + position.h},
                        {position.x, position.y + position.h},
                };
                obj->vsize = 4;
        }
        memcpy(obj->vertices, vertices, sizeof(SDL_FPoint) * obj->vsize);
        return obj;
}

