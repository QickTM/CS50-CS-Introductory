#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Go through each row and column for the value of bits
    for (int intRow = 0; intRow < width; intRow++)
    {
        for (int intColumn = 0; intColumn < height; intColumn++)
        {
            //Convert pixle color value to float type
            float flRed  = image[intColumn][intRow].rgbtRed;
            float flGreen = image[intColumn][intRow].rgbtGreen;
            float flBlue = image[intColumn][intRow].rgbtBlue;

            //Find avg value of RGB
            int intAvg = round((flRed + flGreen + flBlue) / 3);

            //Assign avg value ot RGB
            image[intColumn][intRow].rgbtRed = image[intColumn][intRow].rgbtGreen = image[intColumn][intRow].rgbtBlue = intAvg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Go through each row and column for the value of bits
    for (int intRow = 0; intRow < width; intRow++)
    {
        for (int intColumn = 0; intColumn < height; intColumn++)
        {
            //Convert pixle colour value to float type
            float flOrgRed  = image[intColumn][intRow].rgbtRed;
            float flOrgGreen = image[intColumn][intRow].rgbtGreen;
            float flOrgBlue = image[intColumn][intRow].rgbtBlue;

            int intSepiaRed = round(.393 * flOrgRed + .769 * flOrgGreen + .189 * flOrgBlue);
            int intSepiaGreen = round(.349 * flOrgRed + .686 * flOrgGreen + .168 * flOrgBlue);
            int intSepiaBlue = round(.272 * flOrgRed + .534 * flOrgGreen + .131 * flOrgBlue);

            //If the "sepia" colour values are more than 255, make them 255 as thatis the highest value of the colour
            if (intSepiaRed > 255)
            {
                intSepiaRed = 255;
            }

            if (intSepiaGreen > 255)
            {
                intSepiaGreen = 255;
            }

            if (intSepiaBlue > 255)
            {
                intSepiaBlue = 255;
            }

            //Update the color of the pixles in the image to the new "sepia" colours
            image[intColumn][intRow].rgbtRed = intSepiaRed;
            image[intColumn][intRow].rgbtGreen = intSepiaGreen;
            image[intColumn][intRow].rgbtBlue = intSepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Go through each row and column for the value of bits
    for (int intRow = 0; intRow < width / 2; intRow++)
    {
        for (int intColumn = 0; intColumn < height; intColumn++)
        {
            //Store pixle in and Array then replace the position with the opposite one ignoring the middle pixles using width / 2
            RGBTRIPLE rgbTemp = image[intColumn][intRow];
            image[intColumn][intRow] = image[intColumn][width- (intRow + 1)];
            image[intColumn][width- (intRow + 1)] = rgbTemp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Make a copy of the pixles in the image
    RGBTRIPLE rgbTemp[height][width];

    //Go through each row and column for the value of bits
    for (int intColumn = 0; intColumn < height; intColumn++)
    {
        for (int intRow = 0; intRow < width; intRow++)
        {
            rgbTemp[intColumn][intRow] = image[intColumn][intRow];
        }
    }


    for (int intColumn = 0; intColumn < height; intColumn++)
    {
        for (int intRow = 0; intRow < width; intRow++)
        {
            int intTotalRed, intTotalGreen, intTotalBlue;
            intTotalRed = intTotalGreen = intTotalBlue = 0;

            float flCounter = 0.00;

            //Get value of the pixles beside selected pixle
            //x and y are the coordinates
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int intCurrentX = intColumn + x;
                    int intCurrentY = intRow + y;

                    //Check for valid pixles beside the pixle
                    if (intCurrentX < 0 || intCurrentX > (height - 1) || intCurrentY < 0 || intCurrentY > (width - 1))
                    {
                        continue;
                    }

                    //Get the value of the pixles
                    intTotalRed += image[intCurrentX][intCurrentY].rgbtRed;
                    intTotalGreen += image[intCurrentX][intCurrentY].rgbtGreen;
                    intTotalBlue += image[intCurrentX][intCurrentY].rgbtBlue;

                    flCounter++;
                }

                //Calculate the avg value of the pixles
                rgbTemp[intColumn][intRow].rgbtRed = round(intTotalRed / flCounter);
                rgbTemp[intColumn][intRow].rgbtGreen = round(intTotalGreen / flCounter);
                rgbTemp[intColumn][intRow].rgbtBlue = round(intTotalBlue / flCounter);
            }
        }
    }

    //Paste the new values into the original image
    for (int intRow = 0; intRow < width; intRow++)
    {
        for (int intColumn = 0; intColumn < height; intColumn++)
        {
            image[intColumn][intRow].rgbtRed = rgbTemp[intColumn][intRow].rgbtRed;
            image[intColumn][intRow].rgbtGreen = rgbTemp[intColumn][intRow].rgbtGreen;
            image[intColumn][intRow].rgbtBlue = rgbTemp[intColumn][intRow].rgbtBlue;
        }
    }
    return;
}
