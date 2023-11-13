#include "./Unity/src/unity.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"Functions.c"
#include"BMP.h"

void setUp(void) {
    // This function will be called before each test case
    // You can use it for any test-specific setup
}

void tearDown(void) {
    // This function will be called after each test case
    // You can use it for any test-specific cleanup
}

void test_readImage(){
    File file = openFile("sample_640x426.bmp");
    TEST_ASSERT_EQUAL(426, file.image.height);
    TEST_ASSERT_EQUAL(640, file.image.width);
    freeImage(file.image);
}

void test_freeImage(){
    File file = openFile("sample_640x426.bmp");
    freeImage(file.image);
    TEST_ASSERT_EQUAL(0, file.image.height);
    TEST_ASSERT_EQUAL(0, file.image.width);
}

void test_printInfo(){
    File file = openFile("sample_640x426.bmp");
    printInfo(file.header, file.dibheader, file.image);
    freeImage(file.image);
}

void test_FillArea(){
    File file = openFile("sample_640x426.bmp");

    freopen("test_FillArea_input.txt", "r", stdin);
    file.image = FillArea(file.image);
    writeImage(file, (char*)("why.bmp"));
    freeImage(file.image);
}

void test_openFile(){
    File file = openFile("sample_640x426.bmp");
    TEST_ASSERT_EQUAL(426, file.image.height);
    TEST_ASSERT_EQUAL(640, file.image.width);
    freeImage(file.image);
}

void test_writeImage(){
    File file = openFile("sample_640x426.bmp");
    writeImage(file, "test");
    freeImage(file.image);
}

int main(void){
    double time = clock();

    UNITY_BEGIN();

    // for(int i = 0; i < 100; i++){
    RUN_TEST(test_readImage);
    RUN_TEST(test_freeImage);
    RUN_TEST(test_printInfo);
    // }
    RUN_TEST(test_FillArea);
    RUN_TEST(test_openFile);
    RUN_TEST(test_writeImage);

    UNITY_END();

    printf("Time taken: %f\n", (clock() - time) / (double)CLOCKS_PER_SEC * 1000);

    return 0;
}