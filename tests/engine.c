#include "unity.h"
#include <SDL2/SDL.h>
#include "engine.h"

void setUp() {
        // called before each test
}

void tearDown() {
        // called after each test
}

//void testLoadingRenderObj_nullSrcrect_initSrcrectFromTexture() {
//        SDL_Texture *texture; cannot be mocked due to texture_magic
//        struct render_object *obj = load_render_obj(texture, NULL, 0);
//        printf("%s\n", SDL_GetError());
//        TEST_ASSERT_TRUE(obj);
//        TEST_ASSERT_EQUAL_INT(0, obj->srcrect.x);
//        TEST_ASSERT_EQUAL_INT(0, obj->srcrect.y);
//        TEST_ASSERT_EQUAL_INT(100, obj->srcrect.w);
//        TEST_ASSERT_EQUAL_INT(100, obj->srcrect.h);
//}

#define VERT_NUM 2
void testLoadingGameObj_passedVertices_copyVertices() {
        SDL_FPoint vertices[VERT_NUM] = {{0, 1}, {2, 3}};
        SDL_FRect pos = {0, 0, 0, 0}; // TODO: should fail?
        struct game_object *obj = load_game_obj(NULL, pos, 0, VERT_NUM, vertices, NULL);
        for(int i = 0; i < VERT_NUM; i++) {
                TEST_ASSERT_EQUAL_FLOAT(vertices[i].x, obj->vertices[i].x);
                TEST_ASSERT_EQUAL_FLOAT(vertices[i].y, obj->vertices[i].y);
                TEST_ASSERT_TRUE(&vertices[i] != &obj->vertices[i]);
        }
        free(obj);
}

void testLoadingGameObj_noVertices_initVerticesFromPosRect() {
        SDL_FRect pos = {0, 0, 5, 10};
        struct game_object *obj = load_game_obj(NULL, pos, 0, 0, NULL, NULL);
        TEST_ASSERT_EQUAL_INT(4, obj->vsize);
        //top left
        TEST_ASSERT_EQUAL_FLOAT(0, obj->vertices[0].x);
        TEST_ASSERT_EQUAL_FLOAT(0, obj->vertices[0].y);
        //top right
        TEST_ASSERT_EQUAL_FLOAT(5, obj->vertices[1].x);
        TEST_ASSERT_EQUAL_FLOAT(0, obj->vertices[1].y);
        //bottom right 
        TEST_ASSERT_EQUAL_FLOAT(5, obj->vertices[2].x);
        TEST_ASSERT_EQUAL_FLOAT(10, obj->vertices[2].y);
        //bottom left 
        TEST_ASSERT_EQUAL_FLOAT(0, obj->vertices[3].x);
        TEST_ASSERT_EQUAL_FLOAT(10, obj->vertices[3].y);
}

int main() {
        UNITY_BEGIN();
        RUN_TEST(testLoadingGameObj_passedVertices_copyVertices);
        RUN_TEST(testLoadingGameObj_noVertices_initVerticesFromPosRect); 
        return UNITY_END();
}
