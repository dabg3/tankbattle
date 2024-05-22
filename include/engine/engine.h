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

//texture properties
//https://github.com/libsdl-org/SDL/blob/main/include/SDL3/SDL_render.h#L654
//
//#define SDL_PROP_TEXTURE_CREATE_COLORSPACE_NUMBER           "colorspace"
//#define SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER               "format"
//#define SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER               "access"
//#define SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER                "width"
//#define SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER               "height"
//#define SDL_PROP_TEXTURE_CREATE_SDR_WHITE_POINT_FLOAT       "SDR_white_point"
//#define SDL_PROP_TEXTURE_CREATE_HDR_HEADROOM_FLOAT          "HDR_headroom"
//#define SDL_PROP_TEXTURE_CREATE_D3D11_TEXTURE_POINTER       "d3d11.texture"
//#define SDL_PROP_TEXTURE_CREATE_D3D11_TEXTURE_U_POINTER     "d3d11.texture_u"
//#define SDL_PROP_TEXTURE_CREATE_D3D11_TEXTURE_V_POINTER     "d3d11.texture_v"
//#define SDL_PROP_TEXTURE_CREATE_D3D12_TEXTURE_POINTER       "d3d12.texture"
//#define SDL_PROP_TEXTURE_CREATE_D3D12_TEXTURE_U_POINTER     "d3d12.texture_u"
//#define SDL_PROP_TEXTURE_CREATE_D3D12_TEXTURE_V_POINTER     "d3d12.texture_v"
//#define SDL_PROP_TEXTURE_CREATE_METAL_PIXELBUFFER_POINTER   "metal.pixelbuffer"
//#define SDL_PROP_TEXTURE_CREATE_OPENGL_TEXTURE_NUMBER       "opengl.texture"
//#define SDL_PROP_TEXTURE_CREATE_OPENGL_TEXTURE_UV_NUMBER    "opengl.texture_uv"
//#define SDL_PROP_TEXTURE_CREATE_OPENGL_TEXTURE_U_NUMBER     "opengl.texture_u"
//#define SDL_PROP_TEXTURE_CREATE_OPENGL_TEXTURE_V_NUMBER     "opengl.texture_v"
//#define SDL_PROP_TEXTURE_CREATE_OPENGLES2_TEXTURE_NUMBER    "opengles2.texture"
//#define SDL_PROP_TEXTURE_CREATE_OPENGLES2_TEXTURE_UV_NUMBER "opengles2.texture_uv"
//#define SDL_PROP_TEXTURE_CREATE_OPENGLES2_TEXTURE_U_NUMBER  "opengles2.texture_u"
//#define SDL_PROP_TEXTURE_CREATE_OPENGLES2_TEXTURE_V_NUMBER  "opengles2.texture_v"
//#define SDL_PROP_TEXTURE_CREATE_VULKAN_TEXTURE_NUMBER       "vulkan.texture"

//texture->magic = &SDL_texture_magic;
//texture->colorspace = (SDL_Colorspace)SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_COLORSPACE_NUMBER, default_colorspace);
//texture->format = format;
//texture->access = access;
//texture->w = w;
//texture->h = h;
//texture->color.r = 1.0f;
//texture->color.g = 1.0f;
//texture->color.b = 1.0f;
//texture->color.a = 1.0f;
//texture->scaleMode = SDL_SCALEMODE_LINEAR;
//texture->view.pixel_w = w;
//texture->view.pixel_h = h;
//texture->view.viewport.w = -1;
//texture->view.viewport.h = -1;
//texture->view.scale.x = 1.0f;
//texture->view.scale.y = 1.0f;
//texture->renderer = renderer;
//texture->next = renderer->textures;

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
                                       int rotation) {
        SDL_Surface *s = SDL_LoadBMP(bmp_texture_path);
        if (s == NULL) {
                return NULL;
        }
        SDL_Texture *t= SDL_CreateTextureFromSurface(renderer, s);
        SDL_FreeSurface(s);
        if (t == NULL) {
                return NULL;
        }
        struct render_object *obj = malloc(sizeof(struct render_object));
        *obj = (struct render_object) {t, src, rotation};
        return obj;
}

// TODO: if vertices array is empty, initialize vertices according to 'initial_pos' rect
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

enum rotation {
        CLOCKWISE = 1,
        COUNTERCLOCKWISE = -1
};

enum direction {
        // TODO: remove N_ (new), fix clash with enum movement
        N_FORWARD = 1,
        N_BACKWARD = -1
};



