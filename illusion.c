/*
    Written by Julian Tu, 2015-04-09
    Outputs a bmp file of a visual illusion
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL (BYTES_PER_PIXEL*8)
#define NUMBER_PLANES 1
#define PIX_PER_METRE 2835
#define MAGIC_NUMBER 0x4d42
#define NO_COMPRESSION 0
#define OFFSET 54
#define DIB_HEADER_SIZE 40
#define NUM_COLORS 0

#define SIZE 1024
#define TOTAL_NUM_BYTES (SIZE*SIZE*BYTES_PER_PIXEL)
#define SQUARE_LOWER_BOUND 17
#define SQUARE_UPPER_BOUND 1007
#define BIG_SUBSQUARE_SIZE 66
#define BMP_FILE "illusion1024_15.bmp"

#define BLACK 0
#define WHITE 255

typedef unsigned char bits8;
typedef unsigned short bits16;
typedef unsigned int bits32;

void writeHeader(FILE *file);
bits8 determineSquareColour(int xPos, int yPos);

int main(int argc, char *argv[]) {
    // check that the types have the size i'm relying on here
    assert(sizeof(bits8) == 1);
    assert(sizeof(bits16) == 2);
    assert(sizeof(bits32) == 4);

    FILE *outputFile;

    outputFile = fopen(BMP_FILE, "wb");
    assert((outputFile != NULL) && "Cannot open file");

    writeHeader(outputFile);

    int bytesPrinted = 0;
    int xPos = 0;
    int yPos = 0;
    bits8 byte;
    while (bytesPrinted < TOTAL_NUM_BYTES) {
        // If P(xPos, yPos) is in the sqaure
        if (xPos < SQUARE_UPPER_BOUND && xPos >= SQUARE_LOWER_BOUND &&
            yPos >= SQUARE_LOWER_BOUND && yPos < SQUARE_UPPER_BOUND) {
            if (0/* Inside the circle (inside the square) */) {
                // shit happens
            } else { // In chessboard-like part of square
                byte = determineSquareColour(xPos, yPos);
                int i = 0;
                while (i < BYTES_PER_PIXEL) {
                    fwrite(&byte, sizeof byte, 1, outputFile);
                    i++;
                }
            }
        } else { // In decorative background
            int i = 0;
            while (i < BYTES_PER_PIXEL) {
                byte = rand() % 255; // Max value of a pixel
                fwrite(&byte, sizeof byte, 1, outputFile);
                i++;
            }
        }

        xPos++;
        if (xPos == SIZE) {
            xPos = 0;
            yPos++;
        }
        bytesPrinted += 3;
    }
    fclose(outputFile);
    return EXIT_SUCCESS;
}

void writeHeader(FILE *file) {
    assert(sizeof(bits8) == 1);
    assert(sizeof(bits16) == 2);
    assert(sizeof(bits32) == 4);

    bits16 magicNumber = MAGIC_NUMBER;
    fwrite(&magicNumber, sizeof magicNumber, 1, file);

    bits32 fileSize = OFFSET + (SIZE * SIZE * BYTES_PER_PIXEL);
    fwrite(&fileSize, sizeof fileSize, 1, file);

    bits32 reserved = 0;
    fwrite(&reserved, sizeof reserved, 1, file);

    bits32 offset = OFFSET;
    fwrite(&offset, sizeof offset, 1, file);

    bits32 dibHeaderSize = DIB_HEADER_SIZE;
    fwrite(&dibHeaderSize, sizeof dibHeaderSize, 1, file);

    bits32 width = SIZE;
    fwrite(&width, sizeof width, 1, file);

    bits32 height = SIZE;
    fwrite(&height, sizeof height, 1, file);

    bits16 planes = NUMBER_PLANES;
    fwrite(&planes, sizeof planes, 1, file);

    bits16 bitsPerPixel = BITS_PER_PIXEL;
    fwrite(&bitsPerPixel, sizeof bitsPerPixel, 1, file);

    bits32 compression = NO_COMPRESSION;
    fwrite(&compression, sizeof compression, 1, file);

    bits32 imageSize = (SIZE * SIZE * BYTES_PER_PIXEL);
    fwrite(&imageSize, sizeof imageSize, 1, file);

    bits32 hResolution = PIX_PER_METRE;
    fwrite(&hResolution, sizeof hResolution, 1, file);

    bits32 vResolution = PIX_PER_METRE;
    fwrite(&vResolution, sizeof vResolution, 1, file);

    bits32 numColors = NUM_COLORS;
    fwrite(&numColors, sizeof numColors, 1, file);

    bits32 importantColors = NUM_COLORS;
    fwrite(&importantColors, sizeof importantColors, 1, file);
}

bits8 determineSquareColour(int xPos, int yPos) {
    bits8 byteColour;
    xPos -= SQUARE_LOWER_BOUND;
    yPos -= SQUARE_LOWER_BOUND;
    if (xPos % (2 * BIG_SUBSQUARE_SIZE) < BIG_SUBSQUARE_SIZE) {
        if (yPos % (2 * BIG_SUBSQUARE_SIZE) < BIG_SUBSQUARE_SIZE) {
            byteColour = WHITE;
        } else {
            byteColour = BLACK;
        }
    } else {
        if (yPos % (2 * BIG_SUBSQUARE_SIZE) < BIG_SUBSQUARE_SIZE) {
            byteColour = BLACK;
        } else {
            byteColour = WHITE;
        }
    }
    return byteColour;
}
