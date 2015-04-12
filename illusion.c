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
#include "declarations.h"
#include "bmp.h"
#include <tests.h>

int main(int argc, char *argv[]) {
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
