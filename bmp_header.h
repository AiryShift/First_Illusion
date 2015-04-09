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
