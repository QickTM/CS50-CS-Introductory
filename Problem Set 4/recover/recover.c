#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usgae: ./recover IMAGE\n");
        return 1;
    }

    //Open a file for reading
    FILE * inputFile = fopen(argv[1], "r");

    //Check to see if input file is valid
    if (inputFile == NULL)
    {
        printf("Could not open file");
        return 2;
    }

    //Put the block of 512 bytes into a array
    unsigned char buffer[512];

    //Track the number of images created
    int intCountImage = 0;

    //Pointer for the file of recovered images
    FILE * outputFile = NULL;

    //Allocate memory for the file name
    char * filename = malloc(8 * sizeof(char));

    //Read the 512bytes block
    while (fread(buffer, sizeof(char), 512, inputFile))
    {
        //Look for start of JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Write out the JPEG filenames
            sprintf(filename, "%03i.jpg", intCountImage);

            //Open the output file for to write
            outputFile = fopen(filename, "w");

            //Count the number of images created
            intCountImage++;
        }

        //Check to see if output was from a valid input
        if (outputFile != NULL)
        {
            fwrite(buffer, sizeof(char), 512, outputFile);
        }
    }
    fclose(outputFile);
    fclose(inputFile);
    free(filename);
    
    return 0;
}