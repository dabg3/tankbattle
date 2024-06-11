#include "unity.h"
#include <SDL2/SDL.h>
#include "engine.h"
#include "internals/internals.h"

#define NODES_COUNT 5

int nodes_count;
void *nodes[NODES_COUNT];

void setUp() {
        // called before each test
        nodes_count = 0;
        for (int i = 0; i < NODES_COUNT; i++) {
                nodes[i] = NULL;
        }
}

void tearDown() {
        // called after each test
        //collect_garbage_game_objs();
}

void count_nodes(void *obj) {
        nodes[nodes_count++] = obj;
}

void testGameObjsList_append() {
        struct game_object *n1= malloc(sizeof(struct game_object));
        struct game_object *n2= malloc(sizeof(struct game_object));
        //append_game_obj(n1);
        //append_game_obj(n2);
        //apply_game_objs(count_nodes);
        TEST_ASSERT_EQUAL(2, nodes_count);
        TEST_ASSERT_TRUE(nodes[0] == n1);
        TEST_ASSERT_TRUE(nodes[1] == n2);
}

void testGameObjsList_removeMiddle() {
        struct game_object *n1= malloc(sizeof(struct game_object));
        struct game_object *n2= malloc(sizeof(struct game_object));
        struct game_object *n3= malloc(sizeof(struct game_object));
        //append_game_obj(n1);
        //append_game_obj(n2);
        //append_game_obj(n3);
        destroy_game_obj(n2); //collect_garbage() after this
        //apply_game_objs(count_nodes);
        TEST_ASSERT_EQUAL(2, nodes_count);
        TEST_ASSERT_TRUE(nodes[0] == n1);
        TEST_ASSERT_TRUE(nodes[1] == n3);
}

void testGameObjsList_removeMiddleThenAppend() {
        struct game_object *n1= malloc(sizeof(struct game_object));
        struct game_object *n2= malloc(sizeof(struct game_object));
        struct game_object *n3= malloc(sizeof(struct game_object));
        //append_game_obj(n1);
        //append_game_obj(n2);
        //append_game_obj(n3);
        destroy_game_obj(n2);
        //append_game_obj(n2); //n2 is garbage. Fix!
        //apply_game_objs(count_nodes);
        TEST_ASSERT_EQUAL(3, nodes_count);
        TEST_ASSERT_TRUE(nodes[0] == n1);
        TEST_ASSERT_TRUE(nodes[1] == n3);
        TEST_ASSERT_TRUE(nodes[2] == n2);
}

int main() {
        UNITY_BEGIN();
        RUN_TEST(testGameObjsList_append);
        //RUN_TEST(testGameObjsList_removeMiddle);
        //RUN_TEST(testGameObjsList_removeMiddleThenAppend);
        return UNITY_END();
}
