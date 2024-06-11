#include <SDL2/SDL.h>
#include "type.h"

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
                                   SDL_FPoint vertices[vsize],
                                   void (*update)(struct game_object *obj));

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

//void update_game_state(struct game_state *state); moved on engine-side

void launch_game(SDL_Renderer *renderer);

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
                   double movement);
