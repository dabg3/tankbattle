#include "engine.h"

SDL_Texture * load_texture(SDL_Renderer *renderer,
                           char bmp_texture_path[]) {
        SDL_Surface *s = SDL_LoadBMP(bmp_texture_path);
        if (s == NULL) {
                return NULL;
        }
        SDL_Texture *t= SDL_CreateTextureFromSurface(renderer, s);
        SDL_FreeSurface(s);
        if (t == NULL) {
                return NULL;
        }
        return t;
}

struct render_object * load_render_obj(SDL_Texture *texture, 
                                       SDL_Rect *srcrect,
                                       int rotation) {
        struct render_object *obj = malloc(sizeof(struct render_object));
        obj->texture = texture;
        obj->rotation = rotation;
        if (srcrect == NULL) {
                int tw = 5, th = 10;
                if (SDL_QueryTexture(texture, NULL, NULL, &tw, &th) != 0) {
                        return NULL;
                }
                SDL_Rect r = {0, 0, tw, th};
                srcrect = &r;
        }
        memcpy(&obj->srcrect, srcrect, sizeof(SDL_Rect));
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
