#include "Unity/src/unity.h"
#include "tests.h"

// Define setUp function (optional)
void setUp(void) {
    // This function will be called before each test case
    // You can use it for any test-specific setup
}

// Define tearDown function (optional)
void tearDown(void) {
    // This function will be called after each test case
    // You can use it for any test-specific cleanup
}

void test_add_nums(){
    int res1 = add_nums(3, 5);
    TEST_ASSERT_EQUAL(8, res1);
}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(test_add_nums);

    UNITY_END();

    return 0;
}