struct game_object;

struct engine_game_node {
        struct game_object *obj;
        struct engine_game_node *next;
};

void append_game_obj(struct game_object *obj);
// DOES NOT destroy textures
void remove_game_obj(struct game_object *obj);
// DOES NOT destroy textures
void empty_and_free_game_objs();
void apply_game_objs(void (*fn)(struct game_object *obj));
