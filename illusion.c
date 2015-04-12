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

typedef struct _boundaries {
    int firstLower;
    int firstUpper;
    int secondLower;
    int secondUpper;
} boundaries;

typedef struct _coordinate {
    int xPos;
    int yPos;
} coordinate;

typedef struct _rgb {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} rgb;

int inSqaure(coordinate checking);
int inCircle(coordinate checking);
rgb determineSquareColor(coordinate checking);
rgb randColor(void);
void writePixel(FILE *file, rgb colorFormat);
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

    int bytesPrinted = 0;
    coordinate currentPosition = {0, 0};
    rgb colorFormat;
    // Each iteration prints a pixel
    while (bytesPrinted < TOTAL_NUM_BYTES) {
        if (inSqaure(currentPosition)) {
            if (inCircle(currentPosition)) {
                // shit happens
            } else { // In chessboard-like part of square
                colorFormat = determineSquareColor(currentPosition);
                writePixel(outputFile, colorFormat);
            }
        } else { // In decorative background
            colorFormat = randColor();
            writePixel(outputFile, colorFormat);
        }
        // Increment the bytesPrinted counter and position trackers
        currentPosition.xPos++;
        if (currentPosition.xPos == SIZE) {
            currentPosition.xPos = 0;
            currentPosition.yPos++;
        }
        bytesPrinted += BYTES_PER_PIXEL;
    }
    fclose(outputFile);
    return EXIT_SUCCESS;
}

int inSqaure(coordinate checking) {
    return (checking.xPos < SQUARE_UPPER_BOUND && checking.xPos >= SQUARE_LOWER_BOUND &&
            checking.yPos < SQUARE_UPPER_BOUND && checking.yPos >= SQUARE_LOWER_BOUND);
}

int inCircle(coordinate checking){
    return 0;
}

rgb determineSquareColor(coordinate checking) {
    unsigned char byteColour;
    checking.xPos -= SQUARE_LOWER_BOUND;
    checking.yPos -= SQUARE_LOWER_BOUND;
    if (checking.xPos % (2 * BIG_SUBSQUARE_SIZE) < BIG_SUBSQUARE_SIZE) {
        if (checking.yPos % (2 * BIG_SUBSQUARE_SIZE) < BIG_SUBSQUARE_SIZE) {
            byteColour = WHITE;
        } else {
            byteColour = BLACK;
        }
    } else {
        if (checking.yPos % (2 * BIG_SUBSQUARE_SIZE) < BIG_SUBSQUARE_SIZE) {
            byteColour = BLACK;
        } else {
            byteColour = WHITE;
        }
    }
    rgb pixelColor = {byteColour, byteColour, byteColour};
    return pixelColor;
}

rgb randColor(void) {
    rgb pixel = {rand() % PIXEL_MAXVAL + 1, rand() % PIXEL_MAXVAL + 1, rand() % PIXEL_MAXVAL + 1};
    return pixel;
}

void writePixel(FILE *file, rgb colorFormat) {
    fwrite(&colorFormat.blue, sizeof colorFormat.blue, 1, file);
    fwrite(&colorFormat.green, sizeof colorFormat.green, 1, file);
    fwrite(&colorFormat.red, sizeof colorFormat.red, 1, file);
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
    unsigned short magicNumber = MAGIC_NUMBER;
    fwrite(&magicNumber, sizeof magicNumber, 1, file);

    unsigned int fileSize = OFFSET + (SIZE * SIZE * BYTES_PER_PIXEL);
    fwrite(&fileSize, sizeof fileSize, 1, file);

    unsigned int reserved = 0;
    fwrite(&reserved, sizeof reserved, 1, file);

    unsigned int offset = OFFSET;
    fwrite(&offset, sizeof offset, 1, file);

    unsigned int dibHeaderSize = DIB_HEADER_SIZE;
    fwrite(&dibHeaderSize, sizeof dibHeaderSize, 1, file);

    unsigned int width = SIZE;
    fwrite(&width, sizeof width, 1, file);

    unsigned int height = SIZE;
    fwrite(&height, sizeof height, 1, file);

    unsigned short planes = NUMBER_PLANES;
    fwrite(&planes, sizeof planes, 1, file);

    unsigned short bitsPerPixel = BITS_PER_PIXEL;
    fwrite(&bitsPerPixel, sizeof bitsPerPixel, 1, file);

    unsigned int compression = NO_COMPRESSION;
    fwrite(&compression, sizeof compression, 1, file);

    unsigned int imageSize = (SIZE * SIZE * BYTES_PER_PIXEL);
    fwrite(&imageSize, sizeof imageSize, 1, file);

    unsigned int hResolution = PIX_PER_METRE;
    fwrite(&hResolution, sizeof hResolution, 1, file);

    unsigned int vResolution = PIX_PER_METRE;
    fwrite(&vResolution, sizeof vResolution, 1, file);

    unsigned int numColors = NUM_COLORS;
    fwrite(&numColors, sizeof numColors, 1, file);

    unsigned int importantColors = NUM_COLORS;
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
    a = 6;
    b = 6;
    assert(reverseModulus(a, b) == 1);
}
