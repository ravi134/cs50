#include "helpers.h"
#include <math.h>

//Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Iterate through rows
    for (int i = 0; i < height; i++)
    {
        //Iterate through columns
        for (int j = 0; j < width; j++)
        {
            //determine average
            float avg = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed / 3;
            int average = round(avg);

            //set colors to appropriate grayscale
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
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
