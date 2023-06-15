#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            RGBTRIPLE *pixel = &image[column][row];
            // Check if the pixel is black
            if (pixel->rgbtBlue == 0 &&
                pixel->rgbtGreen == 0 &&
                pixel->rgbtRed == 0)
            {
                // Change the color of black pixel
                pixel->rgbtBlue = 150;
                pixel->rgbtGreen = 129;
                pixel->rgbtRed = 100;
            }
        }
    }
}