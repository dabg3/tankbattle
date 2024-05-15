#include "unity.h"
#include "calc.h"
#include "tankbattle.h"

void setUp() {
        // called before each test
}

void tearDown() {
        // called after each test
}

void test_inclination() {
        TEST_ASSERT_EQUAL(0, inclination_ratio(-90));
        TEST_ASSERT_EQUAL(0, inclination_ratio(90));
        TEST_ASSERT_EQUAL(1, inclination_ratio(0));
        TEST_ASSERT_EQUAL(1, inclination_ratio(180));
        TEST_ASSERT_EQUAL(0.5, inclination_ratio(45));
}

void test_quadrant() {
        TEST_ASSERT_EQUAL(3, quadrant(1));
        TEST_ASSERT_EQUAL(4, quadrant(-1));
        TEST_ASSERT_EQUAL(1, quadrant(-90));
        TEST_ASSERT_EQUAL(2, quadrant(91));
        TEST_ASSERT_EQUAL(quadrant(-91), quadrant(269));
        TEST_ASSERT_EQUAL(3, quadrant(721));
}

void test_mod() {
        TEST_ASSERT_EQUAL(3, mod(-1, 4));
}

void test_rotation() {
        SDL_FPoint p = {0, 0};
        SDL_FPoint center = {1, 1};

        SDL_FPoint p1 = rotate(p, center, 180);

        TEST_ASSERT_EQUAL(2, p1.x);
        TEST_ASSERT_EQUAL(2, p1.y);
}

void test_line_intersection() {
        struct line line1 = {0, 0, 5, 5};
        struct line line2 = {2, 0, 0, 2};
        SDL_bool expected = SDL_TRUE;

        SDL_bool res = check_line_intersection(line1, line2);

        TEST_ASSERT_EQUAL(expected, res);
}


int main() {
        UNITY_BEGIN();
        RUN_TEST(test_inclination);
        RUN_TEST(test_quadrant);
        RUN_TEST(test_mod);
        RUN_TEST(test_rotation);
        RUN_TEST(test_line_intersection);
        return UNITY_END();
}
