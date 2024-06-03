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

static struct render_object *render_objs[PREALLOCATED_RENDER_OBJS];

static ptrdiff_t render_objs_size = PREALLOCATED_RENDER_OBJS;
static ptrdiff_t render_objs_count = 0; 

struct render_object * load_render_obj(SDL_Texture *texture, 
                                       SDL_Rect *srcrect,
                                       int rotation) {
        struct render_object *obj = malloc(sizeof(struct render_object));
        //TODO: check size and reallocate if required
        //if (render_objs_size == render_objs_count) ...
        render_objs[render_objs_count++] = obj;
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

struct render_object * get_render_obj(ptrdiff_t index) {
        if (index >= render_objs_size) {
                return NULL;
        }
        return render_objs[index];
}

void destroy_render_obj(struct render_object *obj) {
        if (obj == NULL) {
                return;
        }
        if (obj->texture) {
                SDL_DestroyTexture(obj->texture);
        }
        free(obj);
}

struct game_object * load_game_obj(struct render_object *render,
                                   SDL_FRect position,
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

void destroy_game_obj(struct game_object *obj) {
        if (obj == NULL) {
                return;
        }
        destroy_render_obj(obj->render);
        free(obj);
}

/* input handling */

static void (*actions[SDL_NUM_SCANCODES])(struct game_state *);

void register_action(SDL_Scancode scancode, 
                     void (*action)(struct game_state *)) {
        actions[scancode] = action;
}

void delete_action(SDL_Scancode scancode) {
        actions[scancode] = NULL;
}

void (*get_action(SDL_Scancode scancode))(struct game_state *) {
        return actions[scancode];
}

/* movement */

void rotate_game_obj(struct game_object *obj, 
                     enum rotation_direction direction, 
                     double rotation) {
        obj->rotation += rotation * direction;
}

#include <math.h>

void move_game_obj(struct game_object *obj, 
                   enum move_direction direction, 
                   double movement) {
        double rotation_degrees = obj->rotation;
        double inc_x = cos(rotation_degrees * (M_PI / 180)) * movement * direction;
        double inc_y = sin(rotation_degrees * (M_PI / 180)) * movement * direction;
        obj->position.x += inc_x;
        obj->position.y += inc_y;
}






