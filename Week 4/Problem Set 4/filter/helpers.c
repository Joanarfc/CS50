#include "helpers.h"
#include <math.h>

// Copy the image from the tmp copy of the image to the original image
void copyImage(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE tmp[height][width])
{
    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            image[column][row] = tmp[column][row];
        }
    }
}

// Calculate the RGB average for the Grayscale function
int calculateGrayRGBAverage(int red, int green, int blue)
{
    float totalprop = 3.0;

    return round((red + green + blue) / totalprop);
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            int red = image[column][row].rgbtRed;
            int green = image[column][row].rgbtGreen;
            int blue = image[column][row].rgbtBlue;

            // Get the RGB average amount
            int averageRGB = calculateGrayRGBAverage(red, green, blue);

            // Set the RGB channels to have this average color
            image[column][row].rgbtBlue = averageRGB;
            image[column][row].rgbtGreen = averageRGB;
            image[column][row].rgbtRed = averageRGB;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            int sepiaRed = round(.393 * image[column][row].rgbtRed + .769 * image[column][row].rgbtGreen + .189 * image[column][row].rgbtBlue);
            int sepiaGreen = round(.349 * image[column][row].rgbtRed + .686 * image[column][row].rgbtGreen + .168 * image[column][row].rgbtBlue);
            int sepiaBlue = round(.272 * image[column][row].rgbtRed + .534 * image[column][row].rgbtGreen + .131 * image[column][row].rgbtBlue);

            // Check if the amount of red, green and blue > 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Set the RGB channels to have the new RGB colors
            copy[column][row].rgbtBlue = sepiaBlue;
            copy[column][row].rgbtGreen = sepiaGreen;
            copy[column][row].rgbtRed = sepiaRed;
        }
    }

    copyImage(height, width, image, copy);
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;

    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width / 2; row++)
        {
            tmp = image[column][row];
            image[column][row] = image[column][width - row - 1];
            image[column][width - row - 1] = tmp;
        }
    }
}

RGBTRIPLE calculateRGBAverage(int row, int column, int height, int width, RGBTRIPLE image[height][width])
{
    int totalRed = 0;
    int totalGreen = 0;
    int totalBlue  = 0;
    int count = 0;

    RGBTRIPLE average_RGB;

    // iterate through the 3x3 surrounding pixels
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int newColumn = column + i;
            int newRow = row + j;

            if (newRow >= 0 && newRow < height && newColumn >= 0 && newColumn < width)
            {
                totalRed += image[newColumn][newRow].rgbtRed;
                totalGreen += image[newColumn][newRow].rgbtGreen;
                totalBlue += image[newColumn][newRow].rgbtBlue;
                count++;
            }
        }
    }

    // Calculate the average color values
    average_RGB.rgbtRed = round((float)totalRed / count);
    average_RGB.rgbtGreen = round((float)totalGreen / count);
    average_RGB.rgbtBlue = round((float)totalBlue / count);

    return average_RGB;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[width][height];

    // Iterate through each pixel of the image array and copy each pixel to the new array copyoriginal
    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            tmp[column][row] = calculateRGBAverage(row, column, height, width, image);
        }
    }

    copyImage(height, width, image, tmp);
}