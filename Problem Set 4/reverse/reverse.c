#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: reverse intput.wav output.wav");
    }

    // Open input file for reading
    char * inputFile = argv[1];
    FILE * inputPointer = fopen(inputFile, "rb");
    if (inputPointer == NULL)
    {
        printf("Could not open %s.\n", inputFile);
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inputPointer);

    // Use check_format to ensure WAV format
    if (check_format(header) == 0)
    {
        printf("Not a wave file");
        return 1;
    }

    if (header.audioFormat != 1)
    {
        printf("Not a wave file");
        return 1;
    }

    // Open output file for writing
    char * outputFile = argv[2];
    FILE * outputPointer = fopen(outputFile, "wb");
    if (outputPointer == NULL)
    {
        printf("Could not open %s.\n", outputFile);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, outputPointer);

    // Use get_block_size to calculate size of block
    int intBlockSize = get_block_size(header);

    // Write reversed audio to file
    //Use "fseek" to find last part of file
    if (fseek(inputPointer, intBlockSize, SEEK_END))
    {
        return 1;
    }

    BYTE reversedAudio[intBlockSize];
    while (ftell(inputPointer) - intBlockSize > sizeof(header))
    {
        if (fseek(inputPointer, - 2 * intBlockSize, SEEK_CUR))
        {
            return 1;
        }
        fread(reversedAudio, intBlockSize, 1, inputPointer);
        fwrite(reversedAudio, intBlockSize, 1, outputPointer);
    }

    fclose(outputPointer);
    fclose(inputPointer);
}

int check_format(WAVHEADER header)
{
    //Check the file formant for the word "WAVE"
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    //Calculates number of bit per channel
    int intSize = header.numChannels * header.bitsPerSample / 8;
    return intSize;
}