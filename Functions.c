#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BMP.h"

//reads the rgb values of all the pixels in the image
Image readImage(FILE *fp, int height, int width, int image_offset){
    Image img;
    fseek(fp, image_offset, SEEK_SET);//SEEK_SET moves file pointer position to the beginning of the file.
    img.rgb = (RGB**)malloc(height*sizeof(RGB*));//using sizeof(void*) cuz this can point to objects of any type
    img.height = height;
    img.width = width;

    for(int i = height - 1; i >= 0; i--){		//going backwards cuz image info starts from bottom to top
        img.rgb[i] = (RGB*)malloc(width*sizeof(RGB));
		//for(int n = 0; n < width; i++)
		    //fread(&img.rgb[i][n], sizeof(unsigned char), 1, fp);
	    fread(img.rgb[i], sizeof(RGB), width, fp);
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
    scanf("%c", &rgb.red);
    scanf("%c", &rgb.green);
    scanf("%c", &rgb.blue);

    for(int a = x1; a <= x2; a++){
        for(int b = y1; b <= y2; b++){
            img.rgb[a][b] = rgb;
        }
    }
    
    return img;
}



File openFile(char* filename){
    FILE *fp = fopen("sample_640x426.bmp", "rb");
    File file;

    fread(file.header.name, sizeof(char), 2, fp);
    fread(&file.header.size, sizeof(unsigned int), 3, fp);
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
        printf("%d", (int)strlen(file.header.name));
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
    FILE *fp;
    fp = fopen(filename, "w");

    if(fp == NULL){
        printf("Error creating file!!!");
        exit(0);
    }

    fwrite(file.header.name, sizeof(char), 2, fp);
    fwrite(&file.header.size, sizeof(unsigned int), 3, fp);
    fwrite(&file.dibheader, sizeof(DIBheader), 1, fp);
    fseek(fp, file.header.image_offset, SEEK_SET);
    
    for(int y = file.image.height - 1; y >= 0; y--){
		/*for(int x = 0; x < file.image.width - 1; x++){
			printf("Pixel x(%d) y(%d): rgb(%d, %d, %d)\n", x, y, file.image.rgb[y][x].red, file.image.rgb[y][x].green, file.image.rgb[y][x].blue);
			fwrite(&file.image.rgb[y][x].blue, sizeof(unsigned char), file.image.width, fp);
			fwrite(&file.image.rgb[y][x].green, sizeof(unsigned char), file.image.width, fp);
			fwrite(&file.image.rgb[y][x].red, sizeof(unsigned char), file.image.width, fp);
		}*/
		fwrite(file.image.rgb[y], sizeof(RGB), file.image.width, fp);
    }
    fclose(fp);
}
