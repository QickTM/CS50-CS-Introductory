#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //Go through each row and column for the value of bits
    for (int intColumn = 0; intColumn < height; intColumn++)
    {
        for (int intRow = 0; intRow < width; intRow++)
        {
            int RedX = 0;
            int GreenX = 0;
            int BlueX = 0;

            int RedY = 0;
            int GreenY = 0;
            int BlueY = 0;

            //Loop through the neighbouring pixles
            for (int intX = 0; intX < 3; intX++)
            {
                for (int intY = 0; intY < 3; intY++)
                {
                    //Check to see if pixles are valid
                    if (intColumn - 1 + intX < 0 || intColumn - 1 + intX > height - 1 || intRow - 1 + intY < 0 || intRow - 1 + intY > width - 1)
                    {
                        continue;
                    }

                    //Calculate "Gx" for their colours
                    RedX = RedX + (image[intColumn - 1 + intX][intRow - 1 + intY]).rgbtRed * Gx[intX][intY];
                    GreenX = GreenX + (image[intColumn - 1 + intX][intRow - 1 + intY]).rgbtGreen * Gx[intX][intY];
                    BlueX = BlueX + (image[intColumn - 1 + intX][intRow - 1 + intY]).rgbtBlue * Gx[intX][intY];

                    //Calculate "Gy" for their colours
                    RedY = RedY + (image[intColumn - 1 + intX][intRow - 1 + intY]).rgbtRed * Gy[intX][intY];
                    GreenY = GreenY + (image[intColumn - 1 + intX][intRow - 1 + intY]).rgbtGreen * Gy[intX][intY];
                    BlueY = BlueY + (image[intColumn - 1 + intX][intRow - 1 + intY]).rgbtBlue * Gy[intX][intY];
                }
            }

            //Calculate the sqr root of Gx2 and Gy2
            int intRed = round(sqrt((RedX * RedX) + (RedY * RedY)));
            int intGreen = round(sqrt((GreenX * GreenX) + (GreenY * GreenY)));
            int intBlue = round(sqrt((BlueX * BlueX) + (BlueY * BlueY)));

            //Cap the value of RGB at 255 when more than 255 after calculaiton
            if (intRed > 255)
            {
                intRed = 255;
            }

            if (intGreen > 255)
            {
                intGreen = 255;
            }

            if (intBlue > 255)
            {
                intBlue = 255;
            }

            //Put all thse colour values into the copy of the image "rgbTemp"
            rgbTemp[intColumn][intRow].rgbtRed = intRed;
            rgbTemp[intColumn][intRow].rgbtGreen = intGreen;
            rgbTemp[intColumn][intRow].rgbtBlue = intBlue;
        }
    }

    //Paste the copu image into the original image
    for (int intColumn = 0; intColumn < height; intColumn++)
    {
        for (int intRow = 0; intRow < width; intRow++)
        {
            image[intColumn][intRow].rgbtRed = rgbTemp[intColumn][intRow].rgbtRed;
            image[intColumn][intRow].rgbtGreen = rgbTemp[intColumn][intRow].rgbtGreen;
            image[intColumn][intRow].rgbtBlue = rgbTemp[intColumn][intRow].rgbtBlue;
        }
    }
    return;
}
