#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;

// Set command line arguments
int main(int argc, char *argv[])
{
    // Check to see if there are not 2 command line arguments
    if (argc != 2)
    {
        // If not 2 arguments, display error message
        fprintf(stderr, "Usage: ./<program name> <name of forensic image>\n");
        return 1;
    }

    // Set the second command line argument (the file to be checked) to a variable
    char *infile = argv[1];

    // Create a file pointer and open the file to be read
    FILE *infileptr = fopen(infile, "r");

    // Check to see that the file pointer is NULL
    if (infileptr == NULL)
    {
        // If file pointer is NULL (meaning the card could not be open), display error message
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }


    // Create a buffer of 512 bytes
    BYTE buffer[512];

    // declare filename array of size 8 for filenames being produced (###.jpg\0).
    char filename[8];

    // Create file pointer for file that will be written to. Set to null, so that it is not assigned a garbage value
    FILE *img = NULL;

    // keep track of jpgs
    int jpg = 0;

    // while reading each indvidual block of 512 bytes...exit loop if there is no block of size 512 to read
    while (fread(&buffer, sizeof(buffer), 1, infileptr) == 1)
    {
        // check for a jpg by matching the first 4 bytes of a block
        // is this the start of a new jpg?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Create a filename for new jpg
            sprintf(filename, "%03i.jpg", jpg);

            // Open the file to be written to and allow it to be written to
            img = fopen(filename, "w");

            // Write out the file
            fwrite(buffer, sizeof(buffer), 1, img);

            // Increment the jpg counter
            jpg++;
        }
        // If the image is not null that means jpg is already open...continue to write until the start of next jpg header is found
        else if (img != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }

    }

    fclose(infileptr);
    fclose(img);

}
