#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gval;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            gval = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = gval;
        }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            // use the provided formula
            int Rval = (int) round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int Gval = (int) round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int Bval = (int) round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // check : if value of color more than 255 set it as 255
            image[i][j].rgbtGreen = fmin(255, Gval);
            image[i][j].rgbtBlue = fmin(255, Bval);
            image[i][j].rgbtRed = fmin(255, Rval);
        }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width / 2; j++) // if you didn't divied by 2 the array will reflect twice so totaly it will not reflect
        {
            temp = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = temp;
        }

    return;
}

// function to calculate the pixel blur value
RGBTRIPLE blr(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    RGBTRIPLE blurval;
    int a, b;
    int Rsum = 0;
    int Gsum = 0;
    int Bsum = 0;
    float cnt = 0.0;
    // loop for coordinates to get the value of the filter
    for (a = i - 1; a < i + 2; a++)
    {
        for (b = j - 1; b < j + 2; b++)
        {
            if (a < 0 || a > (height - 1) || b < 0 || b > (width - 1))
            {
                continue;
            }
            // the change will be of image not copy but calculation
            // will apply in copy since its carry the true value
            Rsum += copy[a][b].rgbtRed;
            Gsum += copy[a][b].rgbtGreen;
            Bsum += copy[a][b].rgbtBlue;
            cnt++;
        }
    }
    blurval.rgbtBlue = round(Bsum / cnt);
    blurval.rgbtGreen = round(Gsum / cnt);
    blurval.rgbtRed = round(Rsum / cnt);

    return blurval;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // copy the value of image into copy
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // call blr function to get the value of new blured pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blr(i, j, height, width, copy);
        }
    }
    return;
}
