#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BMP.h"

//reads the rgb values of all the pixels in the image
Image readImage(FILE *fp, int height, int width, int image_offset){
    Image pic;
    fseek(fp, image_offset, SEEK_SET);//SEEK_SET moves file pointer position to the beginning of the file.
    pic.rgb = (RGB**) malloc(height*sizeof(void*));//using sizeof(void*) cuz this can point to objects of any type
    pic.height = height;
    pic.width = width;

    for (int i = height-1; i != 0; i--){//going backwards cuz image info starts from bottom to top
        pic.rgb[i] = (RGB*) malloc(width*sizeof(RGB));
        fread(pic.rgb[i], width, sizeof(RGB), fp);
    }
    
    return pic;
}

//frees the dynamicly allocated memory
void freeImage(Image pic){
    for (int i = pic.height-1; i != 0; i--){
        free(pic.rgb[i]);
    }
    free(pic.rgb);
}

File openFile(char* filename){
    FILE *fp = fopen("sample_640x426.bmp", "rb");
    DIBheader dibheader;
    Header header;
    Image img;

    fread(header.name, 2, 1, fp);
    fread(&header.size, 3*sizeof(int), 1, fp);
    fread(&dibheader, sizeof(DIBheader), 1, fp);
    //fread(&header, sizeof(header), 1, fp);//cuz we cant use fscanf in a binary file
    img = readImage(fp, dibheader.height, dibheader.width, header.image_offset);

    //check if the file is opened correctly
    if(fp == NULL){
        printf("Error opening file!!!");
        exit(0);
    }

    //checks if the file is the right type, more info in wiki
    if (header.name[0] != 'B' && header.name[2] != 'M'){
        fclose(fp);
        printf("BMP type diferent from BM!!!\n");
        printf("%s", header.name);
        printf("%d", strlen(header.name));
        exit(0);
    }

    //checks if the file is compressed
    if (dibheader.compression != 0){
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

    fclose(fp);
    freeImage(img);
    File file;
    return file;
}

void writeImage(Header header, DIBheader debheader){

}