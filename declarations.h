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

void writeHeader(FILE *file);
int inSqaure(int xPos, int yPos);
int inCircle(int xPos, int yPos);
int calculateBoxType(int xPos, int yPos);
int calculateBox(int colour, int subdivisions[NUM_SMALL_SQUARES]);
void calculateBoundaries(int *subdivisions, int *boundaries);
bits8 determineSquareColour(int xPos, int yPos);
int reverseModulus(int x, int y);
void testReverseModulus(void);
