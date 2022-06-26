//TODO:https://docs.google.com/document/d/1DVcA-gwjVwGf8gYfUe60yy0n8JewBGVcRMir9GPIF_4/edit
#include<stdio.h>
#include<stdlib.h>
#include"BMP.h"
#include"Functions.c"

#define FILENAME "sample_640x426.bmp"

int main(){
    char filename[32];
    int option;
    printf("Please enter file name:");
    scanf("%s", &filename);
    File file = openFile(filename);
    //printf("%d:%d:%d", file.image.rgb[1]->red, file.image.rgb[1]->green, file.image.rgb[1]->blue);
    start:
    system("cls");
    printf("1.FillArea\n2.GetFileInfo\n3.Save & Exit\n");
    scanf("%d", &option);
    system("cls");

    switch(option){
    case 1:
        file.image = FillArea(file.image);
        goto start;
        break;
    
    case 2:
        printInfo(file.header, file.dibheader, file.image);
        getchar();
        getchar();
        goto start;
        break;

    case 3:
        printf("Enter the name of the new file:");
        char newfilename[32];
        scanf("%s", &newfilename);
        writeImage(file, newfilename);
        break;
    
    default:
        goto start;
        break;
    }
    freeImage(file.image);
    return 0;
}