//write test for the following functions
//readImage - reads the rgb values of all the pixels in the image
//freeImage - frees the dynamicly allocated memory
//printInfo - prints some info about the file from the headers
//FillArea - fills the area between two points with a given color
//openFile - opens the file and checks if it is valid
//writeImage - writes the image to a file
#include "./Unity/src/unity.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
// #include"Functions.c"
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
    file.image = FillArea(file.image);
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
    UNITY_BEGIN();

    RUN_TEST(test_readImage);
    RUN_TEST(test_freeImage);
    RUN_TEST(test_printInfo);
    RUN_TEST(test_FillArea);
    RUN_TEST(test_openFile);
    RUN_TEST(test_writeImage);

    UNITY_END();

    return 0;
}