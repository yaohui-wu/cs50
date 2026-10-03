#include "helpers.h"

#include <math.h>
#include <stdbool.h>

void copy_image(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width]);
bool is_valid_index(int row, int col, int height, int width);
int round_rgb(double rgb);

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
    RGBTRIPLE copy[height][width];
    copy_image(height, width, image, copy);

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

                    if (is_valid_index(row_index, col_index, height, width))
                    {
                        red_sum += copy[row_index][col_index].rgbtRed;
                        green_sum += copy[row_index][col_index].rgbtGreen;
                        blue_sum += copy[row_index][col_index].rgbtBlue;
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

void copy_image(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }
}

bool is_valid_index(int row, int col, int height, int width)
{
    return row >= 0 && row <= height - 1 && col >= 0 && col <= width - 1;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy the image.
    RGBTRIPLE copy[height][width];
    copy_image(height, width, image, copy);

    // Sobel operator kernels.
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            double red_Gx = 0;
            double green_Gx = 0;
            double blue_Gx = 0;
            double red_Gy = 0;
            double green_Gy = 0;
            double blue_Gy = 0;

            for (int k_row = -1; k_row < 2; k_row++)
            {
                for (int k_col = -1; k_col < 2; k_col++)
                {
                    int row_idx = row + k_row;
                    int col_idx = col + k_col;

                    if (is_valid_index(row_idx, col_idx, height, width))
                    {
                        /* Generate a Gx and Gy value for each of the
                        red, green, and blue channels for a pixel using the kernels. */
                        int k_row_idx = k_row + 1;
                        int k_col_idx = k_col + 1;

                        red_Gx += copy[row_idx][col_idx].rgbtRed * Gx[k_row_idx][k_col_idx];
                        green_Gx += copy[row_idx][col_idx].rgbtGreen * Gx[k_row_idx][k_col_idx];
                        blue_Gx += copy[row_idx][col_idx].rgbtBlue * Gx[k_row_idx][k_col_idx];
                        red_Gy += copy[row_idx][col_idx].rgbtRed * Gy[k_row_idx][k_col_idx];
                        green_Gy += copy[row_idx][col_idx].rgbtGreen * Gy[k_row_idx][k_col_idx];
                        blue_Gy += copy[row_idx][col_idx].rgbtBlue * Gy[k_row_idx][k_col_idx];
                    }
                }
            }

            /* Sobel filter algorithm combines Gx and Gy by
            calculating the square root of Gx^2 + Gy^2. */
            // Round the resulting value to the nearest intger capped at 255.
            int red = round_rgb(sqrt(red_Gx*red_Gx + red_Gy*red_Gy));
            int green = round_rgb(sqrt(green_Gx*green_Gx + green_Gy*green_Gy));
            int blue = round_rgb(sqrt(blue_Gx*blue_Gx + blue_Gy*blue_Gy));

            image[row][col].rgbtRed = red;
            image[row][col].rgbtGreen = green;
            image[row][col].rgbtBlue = blue;
        }
    }
}

int round_rgb(double rgb)
{
    int value = round(rgb);
    
    if (value > 255)
    {
        value = 255;
    }
    
    return value;
}