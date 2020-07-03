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
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
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
   //Iterate through rows
    for (int i = 0; i < height; i++)
    {
        //Iterate through columns
        for (int j = 0; j < (width / 2); j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = blue;
            image[i][width - j - 1].rgbtGreen = green;
            image[i][width - j - 1].rgbtRed = red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE t[height][width];
     //Iterate through rows
    for (int i = 0; i < height; i++)
    {
        //Iterate through columns
        for (int j = 0; j < width; j++)
        {
            int sb =  0;
            int sg =  0;
            int sr =  0;
            float count = 0.0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k < 0 || i + k > height - 1 || j + l < 0 || j + l > width - 1)
                        continue;

                    sb += image[i + k][j + l].rgbtBlue;
                    sg += image[i + k][j + l].rgbtGreen;
                    sr += image[i + k][j + l].rgbtRed;
                    count++;
                }
            }
            t[i][j].rgbtBlue = round(sb/count);
            t[i][j].rgbtGreen = round(sg/count);
            t[i][j].rgbtRed = round(sr/count);
        }
    }
    //Iterate through rows
    for (int i = 0; i < height; i++)
    {
        //Iterate through columns
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = t[i][j].rgbtBlue;
            image[i][j].rgbtGreen = t[i][j].rgbtGreen;
            image[i][j].rgbtRed = t[i][j].rgbtRed;
        }
    }
    return;
}

// sets edges to black
int edge(int a)
{
    if (a > 255)
    {
        a = 255;
    }
    return a;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0 ,0}, {1, 2, 1}};

    RGBTRIPLE t[height + 2][width + 2];

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || j == 0 || i == height + 1 || j == width + 1)
            {
                t[i][j].rgbtBlue = 0;
                t[i][j].rgbtGreen = 0;
                t[i][j].rgbtRed = 0;
            }
            else
                t[i][j] = image[i - 1][j - 1];
        }
    }

    RGBTRIPLE t2[height + 2][width + 2];

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
            t2[i][j] = t[i][j];
    }

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            float blueGx = 0.0, greenGx = 0.0, redGx = 0.0;
            float blueGy = 0.0, greenGy = 0.0, redGy = 0.0;

            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    for (int p = 0; p < 2; p++)
                    {
                        blueGx += t[i + k][j + h].rgbtBlue * Gx[k + 1][h + 1];
                        greenGx += t[i + k][j + h].rgbtGreen * Gx[k + 1][h + 1];
                        redGx += t[i  + k][j + h].rgbtRed * Gx[k + 1][h + 1];
                    }
                }
            }
            t2[i][j].rgbtBlue = edge(round(sqrt(blueGx * blueGx + blueGy * blueGy)));
            t2[i][j].rgbtGreen = edge(round(sqrt(greenGx * greenGx + greenGy * greenGy)));
            t2[i][j].rgbtRed = edge(round(sqrt(redGx * redGx + redGy * redGy)));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            image[i][j] = t2[i + 1][j + 1];
    }
}