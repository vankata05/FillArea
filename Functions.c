#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BMP.h"

//reads the rgb values of all the pixels in the image
Image readImage(FILE *fp, int height, int width, int image_offset){
    Image img;
    fseek(fp, image_offset, SEEK_SET);//SEEK_SET moves file pointer position to the beginning of the file.
    img.rgb = (RGB**) malloc(height*sizeof(void*));//using sizeof(void*) cuz this can point to objects of any type
    img.height = height;
    img.width = width;

    for (int i = height-1; i != 0; i--){//going backwards cuz image info starts from bottom to top
        img.rgb[i] = (RGB*) malloc(width*sizeof(RGB));
        fread(img.rgb[i], width, sizeof(RGB), fp);
    }
    
    return img;
}

//frees the dynamicly allocated memory
void freeImage(Image img){
    for (int i = img.height-1; i != 0; i--){
        free(img.rgb[i]);
    }
    free(img.rgb);
}

//prints some info about the file from the headers
void printInfo(Header header, DIBheader dibheader, Image img){
    printf("First two characters: %c%c\n", header.name[0], header.name[1]);
    printf("Size: %d\n", header.size);
    printf("Header size: %d\nWidth: %d\nHeight: %d\nColor planes: %d\nBits per pixel: %d\nCompression: %d\nImage size: %d\n", dibheader.header_size, dibheader.width, dibheader.height, dibheader.colorplanes, dibheader.bitsperpixel, dibheader.compression, dibheader.image_size);    
}

Image FillArea(Image img){
    RGB rgb;
    int x1, y1, x2, y2;
    printf("Enter the cordinates of the first point:");
    scanf("%d", &x1);
    scanf("%d", &y1);
    printf("Enter the cordinates of the second point:");
    scanf("%d", &x2);
    scanf("%d", &y2);
    printf("Enter the rgb values of the color to replace the existing one:");
    scanf("%d", &rgb.red);
    scanf("%d", &rgb.green);
    scanf("%d", &rgb.blue);

    for(int a = x1; a <= x2; a++){
        printf("Done!!!");
        for(int b = y1; b <= y2; b++){
            printf("Done!!!");
            //img.rgb[a][b] = rgb;
        }
    }
    
    printf("Done!!!");
    return img;
}



File openFile(char* filename){
    FILE *fp = fopen("sample_640x426.bmp", "rb");
    File file;/*
    DIBheader dibheader;
    Header header;
    Image img;*/

    fread(file.header.name, 2, 1, fp);
    fread(&file.header.size, 3*sizeof(int), 1, fp);
    fread(&file.dibheader, sizeof(DIBheader), 1, fp);
    //fread(&header, sizeof(header), 1, fp);//cuz we cant use fscanf in a binary file
    file.image = readImage(fp, file.dibheader.height, file.dibheader.width, file.header.image_offset);

    //check if the file is opened correctly
    if(fp == NULL){
        printf("Error opening file!!!");
        exit(0);
    }

    //checks if the file is the right type, more info in wiki
    if (file.header.name[0] != 'B' && file.header.name[2] != 'M'){
        fclose(fp);
        printf("BMP type diferent from BM!!!\n");
        printf("%s", file.header.name);
        printf("%d", strlen(file.header.name));
        exit(0);
    }

    //checks if the file is compressed
    if (file.dibheader.compression != 0){
        fclose(fp);
        printf("File is compressed!!!");
        exit(0);
    }

    /*
    printf("First two characters: %c%c\n", header.name[0], header.name[1]);
    printf("Size: %d\n", header.size);
    printf("Header size: %d\nWidth: %d\nHeight: %d\nColor planes: %d\nBits per pixel: %d\nCompression: %d\nImage size: %d\n", dibheader.header_size, dibheader.width, dibheader.height, dibheader.colorplanes, dibheader.bitsperpixel, dibheader.compression, dibheader.image_size);    
    printf("%d:%d:%d", img.rgb[1][1].red, img.rgb[1][1].green, img.rgb[1][1].blue);
    //*/
    //printf("%d:%d:%d", img.rgb[1][1].red, img.rgb[1][1].green, img.rgb[1][1].blue);
    //file.header = header;
    //file.dibheader = dibheader;
    //file.image = img;
    fclose(fp);
    //freeImage(file.image);
    return file;
}

void writeImage(File file, char* filename){
    filename = strcat(filename, ".bmp");
    FILE *fp = fopen(filename, "w");

    if(fp == NULL){
        printf("Error creating file!!!");
        exit(0);
    }

    fwrite(file.header.name, 2, 1, fp);
    fwrite(&file.header.size, 3*sizeof(int), 1, fp);
    fwrite(&file.dibheader, sizeof(DIBheader), 1, fp);
    
    for (int i = file.image.height-1; i != 0; i--){
        fwrite(&file.image.rgb[i], sizeof(RGB), file.image.width-1, fp);
    }

    fclose(fp);
}