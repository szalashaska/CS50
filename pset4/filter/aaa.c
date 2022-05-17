
#include <math.h>
#include <stdio.h>
#include "bmp.h"

typedef struct
{
    int  Blue;
    int  Green;
    int  Red;
}
RGB;

int main(void)
{
    int height = 3;
    int width = 3;
    RGBTRIPLE image[3][3];

    image[0][0].rgbtBlue = 25;
    image[0][1].rgbtBlue = 30;
    image[0][2].rgbtBlue = 80;
    image[1][0].rgbtBlue = 90;
    image[1][1].rgbtBlue = 100;
    image[1][2].rgbtBlue = 90;
    image[2][0].rgbtBlue = 40;
    image[2][1].rgbtBlue = 30;
    image[2][2].rgbtBlue = 10;





    //buffer array x
    RGB buffer_x[height][width];
    //buffer array y
    RGB buffer_y[height][width];

    int Gx[][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    RGBTRIPLE arr[3][3];
    RGB bufferGx[3][3];
    RGB bufferGy[3][3];
    RGB sum_Gx;
    RGB sum_Gy;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum_Gx.Blue = 0;
            //sum_Gx.rgbtGreen = 0;
            //sum_Gx.rgbtRed = 0;

            sum_Gy.Blue = 0;
            //sum_Gy.rgbtGreen = 0;
            //sum_Gy.rgbtRed = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int row = i - 1 + k;
                    int col = j - 1 + l;

                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        arr[k][l].rgbtBlue = image[row][col].rgbtBlue;
                    }
                    else
                    {
                        arr[k][l].rgbtBlue = 0;
                    }
                    //printf("for img[%i][%i] -> arr [%i][%i] = %i\n", i, j, k, l, arr[k][l].rgbtBlue);

                    bufferGx[k][l].Blue = arr[k][l].rgbtBlue * Gx[k][l];
                    sum_Gx.Blue += bufferGx[k][l].Blue;
                    printf("for img[%i][%i] -> buffGx[%i][%i] => %i = %i * %i\n", i, j, k, l, bufferGx[k][l].Blue, arr[k][l].rgbtBlue, Gx[k][l]);

                    bufferGy[k][l].Blue = arr[k][l].rgbtBlue * Gy[k][l];
                    sum_Gy.Blue += bufferGy[k][l].Blue;
                }
            }

            buffer_x[i][j].Blue = sum_Gx.Blue;
            buffer_y[i][j].Blue = sum_Gy.Blue;

        }
    }


    double combined_blue;

    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            combined_blue = sqrt(pow(buffer_x[m][n].Blue, 2) + pow(buffer_y[m][n].Blue, 2));

            combined_blue = round(combined_blue);

            if (combined_blue > 255)
            {
                combined_blue = 255;
            }

            image[m][n].rgbtBlue = combined_blue;
        }
    }
    for (int z = 0; z < height; z++)
    {
        for (int y = 0; y < width; y++)
        {
            printf("updatedimage [%i][%i] = %i\n", z, y, image[z][y].rgbtBlue);
        }
    }

}

