#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./<program name> <name of forensic image>\n");
        return 1;
    }

    char *infile = argv[1];

    FILE *inptr = fopen(&infile, "r");

    // if (inptr == NULL)
    // {
    //     fprintf(stderr, "Could not open %s.\n", infile);
    //     return 2;
    // }

    // int buffer[4];

    // fread(buffer, 512, 1, inptr);

    printf(buffer[0]);
    // if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    //     {
    //         printf("It's a match");
    //         // sprintf(infile, "%03i.jpg", 2);
    //         // FILE *img = fopen(infile, "w");

    //         // if (img == NULL)
    //         // {
    //         //     fprintf(stderr, "Could not open %s.\n", img);
    //         //     return 3;
    //         // }

    //         fwrite(inptr, 512, 1, img);

    //         fclose(img);
    //     }
    //     else
    //     {
    //         fread(buffer, 512, 1, inptr);
    //     }

    fclose(inptr);

    return 0;
}