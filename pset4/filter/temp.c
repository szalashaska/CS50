#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average = 0;
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            // count the average of three coulors
            average = roundf((image[i][k].rgbtBlue + image[i][k].rgbtGreen + image[i][k].rgbtRed) / 3.0);
            //assign average to all colours
            image[i][k].rgbtBlue = average;
            image[i][k].rgbtGreen = average;
            image[i][k].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //create 2D buffer array
    RGBTRIPLE reverse[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            //assign values for buffer in reflected order
            reverse[i][(width - 1) - k].rgbtBlue = image[i][k].rgbtBlue;
            reverse[i][(width - 1) - k].rgbtGreen = image[i][k].rgbtGreen;
            reverse[i][(width - 1) - k].rgbtRed = image[i][k].rgbtRed;
        }
    }
    for (int l = 0; l < height; l++)
    {
        for (int m = 0; m < width; m++)
        {
            //assign reflected values back to orginal image
            image[l][m].rgbtBlue = reverse[l][m].rgbtBlue;
            image[l][m].rgbtGreen = reverse[l][m].rgbtGreen;
            image[l][m].rgbtRed = reverse[l][m].rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //buffer array
    RGBTRIPLE blured[height][width];
    //other values for calculation purpuses
    float sum_blue;
    float sum_green;
    float sum_red;
    float average_blue;
    float average_green;
    float average_red;
    int counter;
    //loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum_blue = 0;
            sum_green = 0;
            sum_red = 0;
            counter = 0;
            //calculate average of surrounding colour values
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    //include corner situations
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        sum_blue += image[k][l].rgbtBlue;
                        sum_green += image[k][l].rgbtGreen;
                        sum_red += image[k][l].rgbtRed;
                        counter++;
                    }
                }
            }

            //calculate average colour value
            average_blue = roundf(sum_blue / counter);
            average_green = roundf(sum_green / counter);
            average_red = roundf(sum_red / counter);

            //assign values to buffer array
            blured[i][j].rgbtBlue = average_blue;
            blured[i][j].rgbtGreen = average_green;
            blured[i][j].rgbtRed = average_red;
        }
    }

    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            //assign blured values back to orginal image
            image[m][n].rgbtBlue = blured[m][n].rgbtBlue;
            image[m][n].rgbtGreen = blured[m][n].rgbtGreen;
            image[m][n].rgbtRed = blured[m][n].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //buffer array x
    RGBTRIPLE buffer_x[height][width];
    //buffer array y
    RGBTRIPLE buffer_y[height][width];

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    RGBTRIPLE arr[3][3];
    RGBTRIPLE bufferGx[3][3];
    RGBTRIPLE bufferGy[3][3];
    RGBTRIPLE sum_Gx;
    RGBTRIPLE sum_Gy;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum_Gx.rgbtBlue = 0;
            sum_Gx.rgbtGreen = 0;
            sum_Gx.rgbtRed = 0;

            sum_Gy.rgbtBlue = 0;
            sum_Gy.rgbtGreen = 0;
            sum_Gy.rgbtRed = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if ((i - 1) + k >= 0 && (i - 1) + k < height && (j - 1) + l >= 0 && (j - 1) + l < width)
                    {
                        arr[k][l].rgbtBlue = image[(i - 1) + k][(j - 1) + l].rgbtBlue;
                        arr[k][l].rgbtGreen = image[(i - 1) + k][(j - 1) + l].rgbtGreen;
                        arr[k][l].rgbtRed = image[(i - 1) + k][(j - 1) + l].rgbtRed;
                    }
                    else
                    {
                        arr[k][l].rgbtBlue = 0;
                        arr[k][l].rgbtGreen = 0;
                        arr[k][l].rgbtRed = 0;
                    }

                    bufferGx[k][l].rgbtBlue = arr[k][l].rgbtBlue * Gx[k][l];
                    sum_Gx.rgbtBlue += bufferGx[k][l].rgbtBlue;

                    bufferGx[k][l].rgbtGreen = arr[k][l].rgbtGreen * Gx[k][l];
                    sum_Gx.rgbtGreen += bufferGx[k][l].rgbtGreen;

                    bufferGx[k][l].rgbtRed = arr[k][l].rgbtRed * Gx[k][l];
                    sum_Gx.rgbtRed += bufferGx[k][l].rgbtRed;

                    bufferGy[k][l].rgbtBlue = arr[k][l].rgbtBlue * Gy[k][l];
                    sum_Gy.rgbtBlue += bufferGy[k][l].rgbtBlue;

                    bufferGy[k][l].rgbtGreen = arr[k][l].rgbtGreen * Gy[k][l];
                    sum_Gy.rgbtGreen += bufferGy[k][l].rgbtGreen;

                    bufferGy[k][l].rgbtRed = arr[k][l].rgbtRed * Gy[k][l];
                    sum_Gy.rgbtRed += bufferGy[k][l].rgbtRed;
                }
            }
            buffer_x[i][j].rgbtBlue = sum_Gx.rgbtBlue;
            buffer_x[i][j].rgbtGreen = sum_Gx.rgbtGreen;
            buffer_x[i][j].rgbtRed = sum_Gx.rgbtRed;

            buffer_y[i][j].rgbtBlue = sum_Gy.rgbtBlue;
            buffer_y[i][j].rgbtGreen = sum_Gy.rgbtGreen;
            buffer_y[i][j].rgbtRed = sum_Gy.rgbtRed;
        }
    }

    double combined_blue;
    double combined_green;
    double combined_red;
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            combined_blue = sqrt(pow(buffer_x[m][n].rgbtBlue, 2) + pow(buffer_y[m][n].rgbtBlue, 2));
            combined_green = sqrt(pow(buffer_x[m][n].rgbtGreen, 2) + pow(buffer_y[m][n].rgbtGreen, 2));
            combined_red = sqrt(pow(buffer_x[m][n].rgbtRed, 2) + pow(buffer_y[m][n].rgbtRed, 2));

            combined_blue = round(combined_blue);
            combined_green = round(combined_green);
            combined_red = round(combined_red);

            if (combined_blue > 255)
            {
                combined_blue = 255;
            }
            if (combined_green > 255)
            {
                combined_green = 255;
            }
            if (combined_red > 255)
            {
                combined_red = 255;
            }
            image[m][n].rgbtBlue = combined_blue;
            image[m][n].rgbtGreen = combined_green;
            image[m][n].rgbtRed = combined_red;
        }
    }

    return;
}
