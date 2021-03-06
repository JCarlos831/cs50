// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize scale infile outfile\n");
        return 1;
    }

    // scale
    int n = atoi(argv[1]);

    // check scale is between 0 and 100
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Please enter a number between 0 and 100.\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // Original bi.biWidth & bi.biHeight
    long origWidth = bi.biWidth;
    long origHeight = bi.biHeight;
    // printf("Original Width: %lu & Original Height: %lu.\n", origWidth, origHeight);

    // New bi.biWidth
    bi.biWidth *= n;
    bi.biHeight *= n;
    // printf("new width: %d & new height: %d.\n", bi.biWidth, bi.biHeight);

    // Original padding for scanlines
    int origPadding = (4 - (origWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // New padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // New bi.biSizeImage
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);

    // New bf.bfSize
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines so use infile's height
    for (int i = 0, biHeight = labs(origHeight); i < biHeight; i++)
    {
        // vertical scale for outfile
        for (int m = 0; m < n; m++)
        {
            // iterate over pixels in infile's scanline
            for (int j = 0; j < origWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add outfile's padding
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }

            // set cursor back if m is less than scale using the infile's width multiplied by the size of the RGBTRIPLE
            // (total number of bytes on that scanline) to get the number of bytes needed to go back from the cursor's
            // current position
            if (m < n - 1)
            {
                fseek(inptr, -(origWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }

        }

        // skip over infile's padding, if any
        fseek(inptr, origPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}