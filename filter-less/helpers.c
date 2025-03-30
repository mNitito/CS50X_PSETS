#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int new;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // compute the average of red and green and blue
            new = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // update the value of the new pixel
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = new;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Update pixel with sepia values
            // RESULT = (COND) ? (STATEMEN IF TRUE) : (STATEMENT IF FALSE)
            image[i][j].rgbtRed = (sepiaRed > 255) ? (sepiaRed = 255) : sepiaRed ;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? (sepiaGreen = 255) : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? (sepiaBlue == 255) : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int row = 0; row < height; row++)
    {
        for (int coulmn = 0; coulmn < width / 2; coulmn++)
        {
            // Swap pixels
            temp.rgbtRed = image[row][coulmn].rgbtRed;
            temp.rgbtGreen = image[row][coulmn].rgbtGreen;
            temp.rgbtBlue = image[row][coulmn].rgbtBlue;

            image[row][coulmn].rgbtRed = image[row][width - 1 - coulmn].rgbtRed;
            image[row][coulmn].rgbtGreen = image[row][width - 1 - coulmn].rgbtGreen;
            image[row][coulmn].rgbtBlue = image[row][width - 1 - coulmn].rgbtBlue;

            image[row][width - 1 - coulmn].rgbtRed = temp.rgbtRed;
            image[row][width - 1 - coulmn].rgbtGreen = temp.rgbtGreen;
            image[row][width - 1 - coulmn].rgbtBlue = temp.rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Create a copy of image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // coping the image
            copy[i][j] = image[i][j];
        }
    }

    // updated_i = i-1 as we start from the pixel row before the current pixel row
    // updated_j = j-1 as we start from the pixel coulmn before the current pixel coulmn
    // update_i >= 0 to make sure the the row - 1 (previoues row of the current pixel is valied)
    // update_j >= 0 to make sure that the coulmn - 1 (previoues coulmn of the current pixel is valied)
    // update_i < height to make sure (when looping and row + 1 becoume equal to image[update_i][update_j]) not overlapping the edge
    // of the image update_j < width same as update_i < height to make sure the next pixel in the next coulmn is not overlapping the
    // edge of the image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_red = 0, sum_green = 0, sum_blue = 0, total_pixels = 0;
            // looping through the valid neighbores
            for (int update_i = i - 1; update_i < i + 2; update_i++)
            {
                for (int update_j = j - 1; update_j < j + 2; update_j++)
                {
                    if (update_i >= 0 && update_j >= 0 && update_i < height && update_j < width)
                    {
                        sum_red += image[update_i][update_j].rgbtRed;
                        sum_green += image[update_i][update_j].rgbtGreen;
                        sum_blue += image[update_i][update_j].rgbtBlue;
                        total_pixels++;
                    }
                }
            }
            copy[i][j].rgbtRed = round(sum_red / total_pixels);
            copy[i][j].rgbtGreen = round(sum_green / total_pixels);
            copy[i][j].rgbtBlue = round(sum_blue / total_pixels);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // restore to the original image
            image[i][j] = copy[i][j];
        }
    }
    return;
}
