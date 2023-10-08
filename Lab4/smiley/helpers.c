#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int intRow = 0; intRow < width; intRow++)
    {
        for (int intColumn = 0; intColumn < height; intColumn++)
        {
            if (image[intColumn][intRow].rgbtRed == 0 && image[intColumn][intRow].rgbtGreen == 0 && image[intColumn][intRow].rgbtBlue == 0)
            {
                image[intColumn][intRow].rgbtRed = 125;
                image[intColumn][intRow].rgbtGreen = 52;
                image[intColumn][intRow].rgbtBlue = 235;
            }
        }
    }
}
