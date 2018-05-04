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

    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    int buffer[4];

    fread(buffer, 512, 1, inptr);

    if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0)
        {
            printf("It's a true");
            sprintf(filename, "%03i.jpg", 2)
            FILE *img = fopen(filename, "w");
        }

    fclose(inptr);

    return 0;
}