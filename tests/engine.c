#include "unity.h"
#include <SDL2/SDL.h>
#include "engine.h"

void setUp() {
        // called before each test
}

void tearDown() {
        // called after each test
}

#define VERT_NUM 2
void test1() {
        SDL_FPoint vertices[VERT_NUM] = {{0, 1}, {2, 3}};
        SDL_Rect dest = {0, 0, 10, 10};
        struct game_object *obj = load_obj(NULL, "", dest, 0, VERT_NUM, vertices);
        for(int i = 0; i < VERT_NUM; i++) {
                TEST_ASSERT_EQUAL_FLOAT(vertices[i].x, obj->vertices[i].x);
                TEST_ASSERT_EQUAL_FLOAT(vertices[i].y, obj->vertices[i].y);
                TEST_ASSERT_TRUE(&vertices[i] != &obj->vertices[i]);
        }
        free(obj);
}

int main() {
        UNITY_BEGIN();
        RUN_TEST(test1);
        return UNITY_END();
}
