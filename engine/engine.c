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

void destroy_render_obj(struct render_object *obj) {
        if (obj == NULL) {
                return;
        }
        SDL_DestroyTexture(obj->texture);
        free(obj);
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


void destroy_game_obj(struct game_object *obj) {
        if (obj == NULL) {
                return;
        }
        destroy_render_obj(obj->render);
        free(obj);
}

/* input handling */

static struct game_state * (*actions[SDL_NUM_SCANCODES])(struct game_state *);

void register_action(SDL_Scancode scancode, 
                     struct game_state * (*action)(struct game_state *)) {
        actions[scancode] = action;
}

void delete_action(SDL_Scancode scancode) {
        actions[scancode] = NULL;
}

/* game */

SDL_bool process_input(SDL_Event event, struct game_state *state) {
        SDL_Scancode code = event.key.keysym.scancode;
        if (event.type == SDL_QUIT) {
                return SDL_TRUE;
        }
        if (code >= SDL_NUM_SCANCODES || actions[code] == NULL) {
                return SDL_FALSE;
        }
        return SDL_FALSE;
}

void launch_game(SDL_Renderer *renderer) {
        struct game_state *state = init_game_state(render_objs);
        SDL_Event event;
        SDL_bool quit = SDL_FALSE;
        while(!quit) {
                while (!quit && SDL_PollEvent(&event)) {
                        quit = process_input(event, state);
                }
                redraw(renderer, state);
        }
}



