#include "engine.h"
#include "internals/internals.h"

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

struct mem_node *render_objs_head;

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
        append_obj(&render_objs_head, obj);
        return obj;
}

struct render_object * get_render_obj(ptrdiff_t index) {
        return get_obj(&render_objs_head, index);
}

void destroy_render_obj(struct render_object *obj) {
        if (obj == NULL) {
                return;
        }
        struct mem_node *n = render_objs_head;
        for (; n && n->obj != obj; n = n->next) {}
        if (n == NULL) {
                return;
        }
        n->obj = NULL;
        free(obj);
}

struct mem_node *game_objs_head;

struct game_object * load_game_obj(struct render_object *render,
                                   SDL_FRect position,
                                   int rotation,
                                   unsigned int vsize,
                                   SDL_FPoint vertices[vsize],
                                   void (*update)(struct game_object *obj)) {
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
        obj->update = update;
        append_obj(&game_objs_head, obj);
        return obj;
}

void destroy_game_obj(struct game_object *obj) {
        if (obj == NULL) {
                return;
        }
        struct mem_node *n = game_objs_head;
        for (; n && n->obj != obj; n=n->next) {}
        if (n == NULL) {
                return;
        }
        // delete indipendently ? destroy_render_obj(obj->render);
        n->obj = NULL;
        free(obj);
}
