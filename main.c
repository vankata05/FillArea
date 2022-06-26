//TODO:https://docs.google.com/document/d/1DVcA-gwjVwGf8gYfUe60yy0n8JewBGVcRMir9GPIF_4/edit
#include<stdio.h>
#include<stdlib.h>

typedef struct BITMAP_header {
    char name[2];//should be == BM
    unsigned int size;//using unsigned int becaude sizeof(int)=4 in my pc and we oly need 2 acording to wikipedia
    int garbage;//data that is not needed
    unsigned int image_offset;//tells us where the image starts
} BITMAP_header;

void openbmpfile(){
    FILE *fp = fopen("sample_640×426.bmp", "rb");
    BITMAP_header header;
    fread(&header, sizeof(BITMAP_header), 1, fp);//cuz we cant use fscanf in a binary file
    printf("%c%c", header.name[0], header.name[1]);
    fclose(fp);
}

int main(){
    openbmpfile();
    return 0;
}