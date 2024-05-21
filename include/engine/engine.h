#include <SDL2/SDL.h>

// 0 degrees rotation means the object is oriented right as trigonometry standard
// clockwise rotation is used:
// https://en.wikipedia.org/wiki/Rotation_matrix#Non-standard_orientation_of_the_coordinate_system
// TODO: separate game_object (representing a static object) from movible_object (extension of game_object)
//  - add another rotation field in movible_object that conforms to what's written above
//  - the rotation in game_object can be used to render the object in the right direction
//      i.e if the bitmap image is oriented south, a -90 degree rotation can 
//          be set to match initial 0 degree movible_object rotation.
//          Equally, let the image face south but then set movible_object rotation to 90

// struct inheritance 
// http://www.deleveld.dds.nl/inherit.htm

struct game_object {
        //? int lifepoints; -1 means indestructible
        SDL_Texture *texture;
        SDL_Rect pos; //bounding box
        int rotation; 
        unsigned int v_size;
        SDL_FPoint vertices[];
};

struct movible_object {
        int rotation;
        struct game_object base;
};

// awful stuff
struct composed_object {
        unsigned int size;
        union {
                struct game_object base;
                struct movible_object movible;
        } objects[];
};

// TODO: if vertices array is empty, initialize vertices according to 'dest' rect
struct game_object * load_obj(SDL_Renderer *renderer, 
                              char bmp_texture_path[], 
                              SDL_Rect dest,
                              int rotation,
                              int v_size,
                              SDL_FPoint vertices[v_size]) {
        SDL_Surface *s = SDL_LoadBMP(bmp_texture_path);
        // TODO sanity checks
        if (s == NULL) {
                printf("%s\n", SDL_GetError());
        }
        SDL_Texture *t= SDL_CreateTextureFromSurface(renderer, s);
        SDL_FreeSurface(s);
        size_t obj_size = sizeof(struct game_object) + sizeof(SDL_FPoint) * v_size;
        struct game_object *obj = malloc(obj_size);
        *obj = (struct game_object) {t, dest, rotation, v_size};
        memcpy(obj->vertices, vertices, sizeof(SDL_FPoint) * v_size);
        return obj;
}

enum rotation {
        CLOCKWISE = 1,
        COUNTERCLOCKWISE = -1
};

enum direction {
        // TODO: remove N_ (new), fix clash with enum movement
        N_FORWARD = 1,
        N_BACKWARD = -1
};



