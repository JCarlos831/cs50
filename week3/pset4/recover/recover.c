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

    char *sdCard = argv[1];

    FILE *sdCardPtr = fopen(sdCard, "r");

    if (sdCardPtr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", sdCard);
        return 2;
    }

    // size of each block
    int size = 512;

    // set buffer array
    int buffer[512];

   // jpeg counter
    int jpeg = 0;

    char *newCard = NULL;

    // while reading each 512 byte block...
    while (fread(buffer, size, 1, sdCardPtr)) {
        // check for a jpg by matching the first 4 bytes of a block
        // is this the start of a new jpg?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                printf("It's a match");

                // sprintf(infile, "%03i.jpg", jpeg);
                sprintf(newCard, "%03i.jpg", jpeg);

                FILE *img = fopen(newCard, "w");

                fwrite(sdCardPtr, size, 1, img);
                jpeg++;
            }
            else
            {

            }

                // if a jpeg has already been found and then another is found
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                {
                    fclose(img);

                    FILE *img = fopen(newCard, "w");

                    fopen(newCard, "w");

                    sprintf(newCard, "%03i.jpg", jpeg);

                    fwrite(sdCardPtr, 512, 1, img);
                    jpeg++;
                    fclose(img);
                }
        }

    fclose(sdCardPtr);

    return 0;
}
