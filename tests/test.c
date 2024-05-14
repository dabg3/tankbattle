#include "unity.h"
#include "calc.h"

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


int main() {
        UNITY_BEGIN();
        RUN_TEST(test_inclination);
        RUN_TEST(test_quadrant);
        RUN_TEST(test_mod);
        return UNITY_END();
}
