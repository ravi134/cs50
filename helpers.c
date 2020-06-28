#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through rows
    for (int i = 0; i < height  ;i++)
    {
        // Iterate through columns
        for (int j = 0; j < width ;j++)
        {
            // define pixel to manipulate
            RGBTRIPLE pix = image[i][j];
            int average = (round((pix.rgbtBlue + pix.rgbtGreen + pix.rgbtRed) / 3));
            pix.rgbtBlue = 50;
            pix.rgbtGreen = 50;
            pix.rgbtRed = 50;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
