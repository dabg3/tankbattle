#include "unity.h"
#include <SDL2/SDL.h>
#include "engine.h"
#include "internals.h"

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
        empty_and_free_game_objs();
}

void count_nodes(struct game_object *obj) {
        nodes[nodes_count++] = obj;
}

void testGameObjsList_append() {
        struct game_object *n= malloc(sizeof(struct game_object));
        append_game_obj(n);
        append_game_obj(n);
        apply_game_objs(count_nodes);
        TEST_ASSERT_EQUAL(2, nodes_count);
        for (int i = 0; i < 2; i++) {
                TEST_ASSERT_TRUE(nodes[i] == n);
        }
}

void testGameObjsList_removeMiddle() {
        struct game_object *n1= malloc(sizeof(struct game_object));
        struct game_object *n2= malloc(sizeof(struct game_object));
        struct game_object *n3= malloc(sizeof(struct game_object));
        append_game_obj(n1);
        append_game_obj(n2);
        append_game_obj(n3);
        remove_game_obj(n2);
        apply_game_objs(count_nodes);
        TEST_ASSERT_EQUAL(2, nodes_count);
        TEST_ASSERT_TRUE(nodes[0] == n1);
        TEST_ASSERT_TRUE(nodes[1] == n3);
}

void testGameObjsList_removeMiddleThenAppend() {
        struct game_object *n1= malloc(sizeof(struct game_object));
        struct game_object *n2= malloc(sizeof(struct game_object));
        struct game_object *n3= malloc(sizeof(struct game_object));
        append_game_obj(n1);
        append_game_obj(n2);
        append_game_obj(n3);
        remove_game_obj(n2);
        append_game_obj(n2);
        apply_game_objs(count_nodes);
        TEST_ASSERT_EQUAL(3, nodes_count);
        TEST_ASSERT_TRUE(nodes[0] == n1);
        TEST_ASSERT_TRUE(nodes[1] == n3);
        TEST_ASSERT_TRUE(nodes[2] == n2);
}

int main() {
        UNITY_BEGIN();
        RUN_TEST(testGameObjsList_append);
        RUN_TEST(testGameObjsList_removeMiddle);
        RUN_TEST(testGameObjsList_removeMiddleThenAppend);
        return UNITY_END();
}
