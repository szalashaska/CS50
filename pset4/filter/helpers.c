#include "helpers.h"
#include <math.h>
typedef struct
{
    int  Blue;
    int  Green;
    int  Red;
}
RGB;

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

            //calculate average colour value and assign values to buffer array
            blured[i][j].rgbtBlue = roundf(sum_blue / counter);
            blured[i][j].rgbtGreen = roundf(sum_green / counter);
            blured[i][j].rgbtRed = roundf(sum_red / counter);
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
    RGB buffer_x[height][width];
    //buffer array y
    RGB buffer_y[height][width];
    //Sobel matrix in direction x
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    //Sobel matrix in direction y
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    //buffer variables, matrixes
    RGBTRIPLE arr[3][3];
    RGB bufferGx[3][3];
    RGB bufferGy[3][3];
    RGB sum_Gx, sum_Gy;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Zeroing the sum before every iteration
            sum_Gx.Blue = sum_Gy.Blue = sum_Gx.Green = sum_Gy.Green = sum_Gx.Red = sum_Gy.Red = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int row = i - 1 + k;
                    int col = j - 1 + l;
                    //check for border condition
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        arr[k][l].rgbtBlue = image[row][col].rgbtBlue;
                        arr[k][l].rgbtGreen = image[row][col].rgbtGreen;
                        arr[k][l].rgbtRed = image[row][col].rgbtRed;
                    }
                    //if we are over the border of image
                    else
                    {
                        arr[k][l].rgbtBlue = 0;
                        arr[k][l].rgbtGreen = 0;
                        arr[k][l].rgbtRed = 0;
                    }
                    //multiply surrounding pixel matrix by Sobel matrix, count the sum
                    //X direction
                    bufferGx[k][l].Blue = arr[k][l].rgbtBlue * Gx[k][l];
                    sum_Gx.Blue += bufferGx[k][l].Blue;
                    bufferGx[k][l].Green = arr[k][l].rgbtGreen * Gx[k][l];
                    sum_Gx.Green += bufferGx[k][l].Green;
                    bufferGx[k][l].Red = arr[k][l].rgbtRed * Gx[k][l];
                    sum_Gx.Red += bufferGx[k][l].Red;
                    //Y direction
                    bufferGy[k][l].Blue = arr[k][l].rgbtBlue * Gy[k][l];
                    sum_Gy.Blue += bufferGy[k][l].Blue;
                    bufferGy[k][l].Green = arr[k][l].rgbtGreen * Gy[k][l];
                    sum_Gy.Green += bufferGy[k][l].Green;
                    bufferGy[k][l].Red = arr[k][l].rgbtRed * Gy[k][l];
                    sum_Gy.Red += bufferGy[k][l].Red;
                }
            }
            //assign calculated values to buffer matrix
            buffer_x[i][j].Blue = sum_Gx.Blue;
            buffer_y[i][j].Blue = sum_Gy.Blue;
            buffer_x[i][j].Green = sum_Gx.Green;
            buffer_y[i][j].Green = sum_Gy.Green;
            buffer_x[i][j].Red = sum_Gx.Red;
            buffer_y[i][j].Red = sum_Gy.Red;
        }
    }
    //variables
    double combined_blue, combined_green, combined_red;
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            //combine values from x and y direction into one value
            combined_blue = round(sqrt(pow(buffer_x[m][n].Blue, 2) + pow(buffer_y[m][n].Blue, 2)));
            combined_green = round(sqrt(pow(buffer_x[m][n].Green, 2) + pow(buffer_y[m][n].Green, 2)));
            combined_red = round(sqrt(pow(buffer_x[m][n].Red, 2) + pow(buffer_y[m][n].Red, 2)));
            //capp the values at 255
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
            //assign values back to image
            image[m][n].rgbtBlue = combined_blue;
            image[m][n].rgbtGreen = combined_green;
            image[m][n].rgbtRed = combined_red;
        }
    }
    return;
}
