#include "engine.h"

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
