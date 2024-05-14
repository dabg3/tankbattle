#include "unity.h"
#include "movements.h"

void setUp() {
        // called before each test
}

void tearDown() {
        // called after each test
}

void test_inclination() {
        TEST_ASSERT_EQUAL(0, inclination(-90));
}


int main() {
        UNITY_BEGIN();
        RUN_TEST(test_inclination);
        return UNITY_END();
}
