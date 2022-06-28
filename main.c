//TODO:https://docs.google.com/document/d/1DVcA-gwjVwGf8gYfUe60yy0n8JewBGVcRMir9GPIF_4/edit
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Functions.c"
#include"BMP.h"

#define FILENAME "sample_640x426.bmp"

int main(){
    char filename[32];
    int option;
    printf("Please enter file name:");
    scanf("%s", &filename[0]);
    File file = openFile(filename);
    //printf("%d:%d:%d", file.image.rgb[1]->red, file.image.rgb[1]->green, file.image.rgb[1]->blue);

    while(true){
        system("clear");
        printf("1.FillArea\n2.GetFileInfo\n3.Save & Exit\n");
        scanf("%d", &option);
        system("clear");

        if(option == 1){
            file.image = FillArea(file.image);
        }
        if(option == 2){
            printInfo(file.header, file.dibheader, file.image);
            getchar();
            getchar();
        }
        if(option == 3){
            char newfilename[32];
            printf("Enter the name of the new file:");
            scanf("%s", newfilename);
            writeImage(file, newfilename);
            freeImage(file.image);
            return 0;
        }
    }
}
