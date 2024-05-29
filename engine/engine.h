#include <SDL2/SDL.h>

struct render_object {
        SDL_Texture *texture;
        SDL_Rect src; //texture src
        int rotation; 
};

#define MAX_VERTICES 8

struct game_object {
        struct render_object *render;
        SDL_Rect position; //bounding box
        //int z_index; //where is more appropriate to put this field?
        //int lifepoints; // -1 means indestructible. Better to keep this in a game state data structure(?)
        int rotation;
        unsigned int vsize;
        //fixed dim otherwise cannot be used on arrays - C standard §6.7.2.1
        SDL_FPoint vertices[MAX_VERTICES]; 
};

//TODO: group_object (a composition of several game_object)

struct render_object * load_render_obj(SDL_Renderer *renderer, 
                                       char bmp_texture_path[], 
                                       SDL_Rect src,
                                       int rotation); 

struct game_object * load_game_obj(struct render_object *render,
                                   SDL_Rect position,
                                   int rotation,
                                   unsigned int vsize,
                                   SDL_FPoint vertices[vsize]);
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

#define MAX_FLYING_BULLETS 16

//TODO: let the game implementation define its own state
struct game_state {
        struct game_object *p1;
        struct game_object *p2;
        struct game_object *bullets[MAX_FLYING_BULLETS];
        unsigned int ssize;
        struct game_object *surroundings[];
};

//TODO: setup flags
//void update_state(struct game_state *state, short movement) {
//        // x += cos(rad(degrees)) * SPEED * direction
//        // y += sin(rad(degrees)) * SPEED 
//}



