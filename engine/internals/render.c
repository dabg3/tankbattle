#include "internals.h"
#include "mem.h"
#include "type.h"

static SDL_Renderer *renderer;

void render_obj(void *o) {
        struct game_object *obj = o;
        SDL_RenderCopyExF(renderer, obj->render->texture, 
                                    &obj->render->srcrect, 
                                    &obj->position, 
                                    obj->rotation + obj->render->rotation, 
                                    NULL, 0); 

}

void redraw(SDL_Renderer *r) {
        renderer = r;
        SDL_RenderClear(renderer);
        apply(&game_objs_head, render_obj);
        SDL_RenderPresent(renderer);
}
