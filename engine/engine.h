#include <SDL2/SDL.h>

/* types */

struct render_object {
        SDL_Texture *texture;
        SDL_Rect srcrect; 
        int rotation; 
};

#ifndef PREALLOCATED_RENDER_OBJS
#define PREALLOCATED_RENDER_OBJS 8
#endif

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
};

SDL_Texture * load_texture(SDL_Renderer *renderer, 
                           char bmp_texture_path[]);

struct render_object * load_render_obj(SDL_Texture *texture,
                                       SDL_Rect *srcrect,
                                       int rotation); 

struct render_object * get_render_obj(ptrdiff_t index);

void destroy_render_obj(struct render_object *obj); 

struct game_object * load_game_obj(struct render_object *render,
                                   SDL_FRect position,
                                   int rotation,
                                   unsigned int vsize,
                                   SDL_FPoint vertices[vsize]);

void destroy_game_obj(struct game_object *obj);

/* game */

struct game_state;

struct game_state_info {
        struct game_state *state;
        size_t size;
};

struct game_state_info allocate_game_state();

void destroy_game_state(struct game_state *state);

void init_game_state(struct game_state *state);

void launch_game(SDL_Renderer *renderer);

void redraw(SDL_Renderer *renderer, struct game_state *state);

/* input handling */

void register_action(SDL_Scancode scancode, void (*action)(struct game_state *));

void delete_action(SDL_Scancode scancode);

void (*get_action(SDL_Scancode scancode))(struct game_state *);

/* movement */

enum rotation_direction {
        CLOCKWISE = 1,
        COUNTERCLOCKWISE = -1
};

enum move_direction {
        FORWARD = 1,
        BACKWARD = -1
};

void rotate_game_obj(struct game_object *obj, 
                     enum rotation_direction direction, 
                     double rotation);

void move_game_obj(struct game_object *obj, 
                   enum move_direction direction, 
                   int movement);

//void update_state(struct game_state *state, short movement) {
//        // x += cos(rad(degrees)) * SPEED * direction
//        // y += sin(rad(degrees)) * SPEED * direction
//}



