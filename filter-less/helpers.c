#include "helpers.h"

#include <math.h>

int sepia_int(double sepia_double);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            RGBTRIPLE pixel = image[row][col];
            int red = pixel.rgbtRed;
            int green = pixel.rgbtGreen;
            int blue = pixel.rgbtBlue;

            /* Take the average of the red, green, and blue values to
            determine the shade of grey for the new pixel. */
            int gray = round((red + green + blue) / 3.0);
            image[row][col].rgbtRed = gray;
            image[row][col].rgbtGreen = gray;
            image[row][col].rgbtBlue = gray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            RGBTRIPLE pixel = image[row][col];
            int red = pixel.rgbtRed;
            int green = pixel.rgbtGreen;
            int blue = pixel.rgbtBlue;

            double sepia_red_temp = 0.393*red + 0.769*green + 0.189*blue;
            int sepia_red = sepia_int(sepia_red_temp);
            double sepia_green_temp = 0.349*red + 0.686*green + 0.168*blue;
            int sepia_green = sepia_int(sepia_green_temp);
            double sepia_blue_temp = 0.272*red + 0.534*green + 0.131*blue;
            int sepia_blue = sepia_int(sepia_blue_temp);

            image[row][col].rgbtRed = sepia_red;
            image[row][col].rgbtGreen = sepia_green;
            image[row][col].rgbtBlue = sepia_blue;
        }
    }
}

int sepia_int(double sepia_double)
{
    int sepia_int = round(sepia_double);

    /* Red, green, and blue values are capped at 255,
    the maximum value for an 8-bit color value. */
    if (sepia_int > 255)
    {
        sepia_int = 255;
    }

    return sepia_int;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            // Swap the values of pixels on opposite sides of a row.
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width - 1 - col];
            image[row][width - 1 - col] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy the image.
    RGBTRIPLE image_copy[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image_copy[row][col] = image[row][col];
        }
    }

    // Read pixels' colors from copy but write pixels' colors in image.
    /* Box blur, take each pixel and, for each color value, giving it a
    new value by averaging the color values of neighboring pixels. */
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            /* The new value of each pixel would be the average of the
            values of all of the pixels that are within 1 row and
            column of the original pixel. */
            int red_sum = 0;
            int green_sum = 0;
            int blue_sum = 0;
            double count = 0;

            for (int box_row = -1; box_row < 2; box_row++)
            {
                for (int box_col = -1; box_col < 2; box_col++)
                {
                    int row_index = row + box_row;
                    int col_index = col + box_col;

                    if (row_index >= 0
                        && row_index <= height - 1
                        && col_index >= 0
                        && col_index <= width - 1)
                    {
                        red_sum += image_copy[row_index][col_index].rgbtRed;
                        green_sum += image_copy[row_index][col_index].rgbtGreen;
                        blue_sum += image_copy[row_index][col_index].rgbtBlue;
                        count++;
                    }
                }
            }

            int avg_red = round(red_sum / count);
            int avg_green = round(green_sum / count);
            int avg_blue = round(blue_sum / count);

            image[row][col].rgbtRed = avg_red;
            image[row][col].rgbtGreen = avg_green;
            image[row][col].rgbtBlue = avg_blue;
        }
    }
}