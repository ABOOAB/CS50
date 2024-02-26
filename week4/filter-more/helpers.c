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

// Blur image
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

RGBTRIPLE sobl(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    RGBTRIPLE sobVal;
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int GxR = 0, GxG = 0, GxB = 0, GyR = 0, GyG = 0, GyB = 0;

    for (int r = 0; r < 3; r++)
        for (int k = 0; k < 3; k++)
        {
            if (i - 1 + r < 0 || i - 1 + r > height - 1 || j - 1 + k < 0 || j - 1 + k > width - 1)
            {
                continue;
            }
            GxR += Gx[r][k] * copy[i - 1 + r][j - 1 + k].rgbtRed;
            GyR += Gy[r][k] * copy[i - 1 + r][j - 1 + k].rgbtRed;
            GxG += Gx[r][k] * copy[i - 1 + r][j - 1 + k].rgbtGreen;
            GyG += Gy[r][k] * copy[i - 1 + r][j - 1 + k].rgbtGreen;
            GxB += Gx[r][k] * copy[i - 1 + r][j - 1 + k].rgbtBlue;
            GyB += Gy[r][k] * copy[i - 1 + r][j - 1 + k].rgbtBlue;
        }

    int blue = round(sqrt(GxB * GxB + GyB * GyB));
    int green = round(sqrt(GxG * GxG + GyG * GyG));
    int red = round(sqrt(GxR * GxR + GyR * GyR));

    sobVal.rgbtBlue = (blue > 255) ? 255 : blue;
    sobVal.rgbtGreen = (green > 255) ? 255 : green;
    sobVal.rgbtRed = (red > 255) ? 255 : red;

    return sobVal;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = sobl(i, j, height, width, copy);
        }
    }

    return;
}
