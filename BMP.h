#ifndef header_file  
#define header_file 

typedef struct Header {
    char name[2];//should be == BM
    unsigned int size;//using unsigned int becaude sizeof(int)=4 in my pc and we oly need 2 acording to wikipedia
    int garbage;//data that is not needed
    unsigned int image_offset;//tells us where the image starts
} Header;

typedef struct DIBheader {
    unsigned int header_size;//size of the header
    unsigned int width;//width in pixels
    unsigned int height;//height in pixels
    unsigned short int colorplanes;
    unsigned short int bitsperpixel;
    unsigned int compression;//we need it to be zero in order to hot have compression
    unsigned int image_size;
    unsigned int temp[4];//used when writing to file
} DIBheader;

typedef struct RGB {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} RGB;

typedef struct Image {
    int height;
    int width;
    RGB **rgb;
} Image;

typedef struct File {
    Header header;
    DIBheader dibheader;
    Image image;
} File;

#endif