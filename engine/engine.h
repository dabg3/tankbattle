#include <SDL2/SDL.h>

struct render_object {
        SDL_Texture *texture;
        SDL_Rect srcrect; 
        int rotation; 
};

#ifndef PREALLOCATED_RENDER_OBJS
#define PREALLOCATED_RENDER_OBJS 8
#endif

static struct render_object *render_objs[PREALLOCATED_RENDER_OBJS];

#ifndef MAX_VERTICES
#define MAX_VERTICES 8
#endif

struct game_object {
        struct render_object *render;
        SDL_Rect position; //bounding box
        int rotation;
        unsigned int vsize;
        //fixed dim otherwise cannot be used on arrays - C standard §6.7.2.1
        SDL_FPoint vertices[MAX_VERTICES]; 
};

SDL_Texture * load_texture(SDL_Renderer *renderer, 
                           char bmp_texture_path[]);

struct render_object * load_render_obj(SDL_Texture *texture,
                                       SDL_Rect *srcrect,
                                       int rotation); 

void destroy_render_obj(struct render_object *obj); 

struct game_object * load_game_obj(struct render_object *render,
                                   SDL_Rect position,
                                   int rotation,
                                   unsigned int vsize,
                                   SDL_FPoint vertices[vsize]);

void destroy_game_obj(struct game_object *obj);

/* game */

struct game_state;

struct game_state * init_game_state(struct render_object *render_objs[]);

void destroy_game_state(struct game_state *state);

void launch_game(SDL_Renderer *renderer);

void redraw(SDL_Renderer *renderer, struct game_state *state);

/* input handling */

void register_action(SDL_Scancode scancode, struct game_state * (*action)(struct game_state *));

void delete_action(SDL_Scancode scancode);

//enum rotation {
//        CLOCKWISE = 1,
//        COUNTERCLOCKWISE = -1
//};
//
//enum direction {
//        // TODO: remove N_ (new), fix clash with enum movement
//        N_FORWARD = 1,
//        N_BACKWARD = -1
//};



//TODO: setup flags
//void update_state(struct game_state *state, short movement) {
//        // x += cos(rad(degrees)) * SPEED * direction
//        // y += sin(rad(degrees)) * SPEED * direction
//}



