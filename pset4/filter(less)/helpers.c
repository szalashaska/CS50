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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed = 0;
    float sepiaGreen = 0;
    float sepiaBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            //calculate sepia values for colours and round them
            sepiaRed = round(.393 * image[i][k].rgbtRed + .769 * image[i][k].rgbtGreen + .189 * image[i][k].rgbtBlue);
            sepiaGreen = round(.349 * image[i][k].rgbtRed + .686 * image[i][k].rgbtGreen + .168 * image[i][k].rgbtBlue);
            sepiaBlue = round(.272 * image[i][k].rgbtRed + .534 * image[i][k].rgbtGreen + .131 * image[i][k].rgbtBlue);

            //check if sepia values are within range of 8-bit colour value
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
            //assign sepia values
            image[i][k].rgbtBlue = sepiaBlue;
            image[i][k].rgbtGreen = sepiaGreen;
            image[i][k].rgbtRed = sepiaRed;
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
