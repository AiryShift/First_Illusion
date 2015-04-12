/*
    Written by Julian Tu, 2015-04-09
    Outputs a bmp file of a visual illusion

    BMP file is 1024x1024 pixels
    Has an external border of 17 pixels, leaving internal square of
    990 * 990
    The sqaure is subdivided into chessboard of 5 * 5
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
#define PIXEL_MAXVAL 255
#define SQUARE_LOWER_BOUND 17
#define SQUARE_UPPER_BOUND 1007
#define BIG_SUBSQUARE_SIZE 198
#define NUM_SMALL_SQUARES 2
#define BMP_FILE "illusion1024_15.bmp"

#define BLACK 0
#define WHITE 255

typedef unsigned char bits8;
typedef unsigned short bits16;
typedef unsigned int bits32;

typedef struct _boundaries {
    int firstLower;
    int firstUpper;
    int secondLower;
    int secondUpper;
} boundaries;

int inSqaure(int xPos, int yPos);
int inCircle(int xPos, int yPos);
int calculateBoxType(int xPos, int yPos);
int calculateBox(int colour, int subdivisions[NUM_SMALL_SQUARES]);
void calculateBoundaries(int *subdivisions, int *boundaries);
bits8 determineSquareColour(int xPos, int yPos);
int reverseModulus(int x, int y);

void writeHeader(FILE *file);

void runTests(void);
void testReverseModulus(void);


int main(int argc, char *argv[]) {
    runTests();
    FILE *outputFile;

    outputFile = fopen(BMP_FILE, "wb");
    assert((outputFile != NULL) && "Cannot open file");

    writeHeader(outputFile);
    // testReverseModulus();

    int bytesPrinted = 0;
    int xPos = 0;
    int yPos = 0;
    bits8 byte;
    // Each iteration prints a pixel
    while (bytesPrinted < TOTAL_NUM_BYTES) {
        if (inSqaure(xPos, yPos)) {
            if (inCircle(xPos, yPos)) {
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
                byte = rand() % PIXEL_MAXVAL;
                fwrite(&byte, sizeof byte, 1, outputFile);
                i++;
            }
        }
        // Increment the bytesPrinted counter and position trackers
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

int inSqaure(int xPos, int yPos) {
    return (xPos < SQUARE_UPPER_BOUND && xPos >= SQUARE_LOWER_BOUND &&
            yPos >= SQUARE_LOWER_BOUND && yPos < SQUARE_UPPER_BOUND);
}

int inCircle(int xPos, int yPos){
    return 0;
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

int reverseModulus(int x, int y) {
    // Calculates python's y // x
    int runningTotal = 0;
    int timesAdded = 0;
    while (runningTotal <= y) {
        runningTotal += x;
        timesAdded++;
    }
    return timesAdded - 1;
}

void writeHeader(FILE *file) {
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

void runTests(void) {
    testReverseModulus();
}

void testReverseModulus(void) {
    int a = 5;
    int b = 6;
    assert(reverseModulus(a, b) == 1);
    a = 6;
    b = 2;
    assert(reverseModulus(a, b) == 0);
    assert(reverseModulus(b, a) == 3);
}
