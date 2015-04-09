/*
    Written by Julian Tu, 2015-04-09
    Outputs a bmp file of a visual illusion
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "declarations.h"
#include "bmp_header.h"

int temp[4]; // Placeholder

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
    // TODO
    return 0;
}

int calculateBoxType(int xPos, int yPos) {
    // Makes the assumption that we're already in the circle
    // Returns black or white
    return 0; // Placeholder
}

int calculateBox(int colour, int subdivisions[NUM_SMALL_SQUARES]) {
    // subdivisions is an array of 2 ints that specifies where the
    // contrasting box colours will go
    int boundaries[4];
    calculateBoundaries(subdivisions, boundaries);
    return 0; // Placeholder
}

void calculateBoundaries(int *subdivisions, int *boundaries) {
    // Write into boundaries[] the hardcoded relative boundaries of
    // the requested squares
    int i = 0;
    while (i < NUM_SMALL_SQUARES) {
        int location = subdivisions[i];
        if (location == 0) {
            /* some code */
        } else if (location == 1) {
            /* some code */
        } else if (location == 2) {
            /* some code */
        } else if (location == 3) {
            /* some code */
        } else if (location == 4) {
            /* some code */
        } else if (location == 5) {
            /* some code */
        } else if (location == 6) {
            /* some code */
        } else if (location == 7) {
            /* some code */
        } else if (location == 8) {
            /* some code */
        } else if (location == 9) {
            /* some code */
        }
        i++;
    }
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
