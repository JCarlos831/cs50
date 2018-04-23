# Questions

## What's `stdint.h`?

TODO
`stdint.h` is a header file allowing programmers to write more portable code by providing a set of typedefs that specify exact-width
integer types, together with the minimum and maximum allowable values for each type, using macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

TODO
These are signed and unsigned integer types with fixed widths. The signed integer types have no padding bits (`int32_t`).

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

TODO
`BYTE` is a single byte
`DWORD` is 4 bytes
`LONG` is 4 bytes
`WORD` is 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

TODO
The first two bits are the file type.  They must be BM.

## What's the difference between `bfSize` and `biSize`?

TODO
`bfSize` is the size, in bytes, of the bitmap file.
`biSize` is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

TODO
If `biHeight` is negative, indicating a top-down DIB, biCompression must be either BI_RGB or BI_BITFIELDS. Top-down DIBs cannot be compressed.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

TODO
`biBitCount` is the number of bits-per-pixel. The biBitCount member of the BITMAPINFOHEADER structure determines the number of bits
that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

TODO
`fopen` may return `NULL` if it could not open the file to be read or it could not be created (written to).

## Why is the third argument to `fread` always `1` in our code?

TODO
The third argument in `fread` is asking for the number of elements. In this code only `1` element is asked for.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

TODO
The value for `padding` is 3.

## What does `fseek` do?

TODO
`fseek` skips over padding , if any.

## What is `SEEK_CUR`?

TODO
It moves the file pointer to a given location.
