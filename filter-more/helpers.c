#include "helpers.h"
#include <math.h>

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
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // coping the image
            copy[i][j] = image[i][j];
        }
    }


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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // declaring the 9 x 9 GY && GX as an array
    int gx_array[] = {-1 , 0, 1, -2, 0, 2, -1, 0, 1};
    int gy_array[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    // copying image an image to change in it the new values
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // coping the image
            copy[i][j] = image[i][j];
        }
    }

    // for looping over every pixel in the image
    for (int i = 0; i < height;  i++)
    {
        for (int j = 0; j < width;  j++)
        {
            int sum_red_gx = 0, sum_green_gx = 0, sum_blue_gx = 0;
            int sum_red_gy = 0, sum_green_gy = 0, sum_blue_gy = 0;
            int counter = 0;
            // for looping over the neighbour of the current pixel:

            // for looping over the neighbouer rows:
            // update_i = (i - 1) to look over the previous row of the cureent pixel
            // then increament  update_i to go to the current row (i - 1) + 1 = i
            // then increment it again to go through the next row of the cuurent row (i) + 1 = i + 1

            // for looping over the neighbouer coulmns :
            // update_j (j - 1) to look over the previous coulmn [pixel] of the current pixel
            // then increment it (j - 1)[update_j] + 1  = j (the current pixel)
            // then icrement it to j + 1 to go to the next coulmn {next pixel}

            // Note : the loop goes to the (update_i) first then go through (update_j) which go to the the -
            //  previous pixel then current then next -- then go to the current row then do the same in the (update_j) loop

            for (int update_i = i - 1; update_i < i + 2; update_i++)
            {
                for (int update_j = j - 1; update_j < j + 2; update_j++)
                {
                    // check if update_i (previous row or next row of the current row is greater than zero as if it is not --
                    // this means that row out of the scoope of the image)
                    // check if update_j is greater than zero [(previous / next) pixel is exsist]
                    // check if update_i is smaller than height [(next) row is exsist and do not exceeds the height of an image]
                    // check if update_j is smaller than the width of the image (next pixel does not exceeds the edges of an image)
                    if (update_i >= 0 &&  update_j >= 0 &&  update_i < height &&  update_j < width)
                    {
                        // making a variables for sum of the neighbours pixel for each current pixel in the image[i][j]
                        // and this for red && green && blue
                        sum_red_gx += image[update_i][ update_j].rgbtRed * gx_array[counter];
                        sum_green_gx += image[update_i][ update_j].rgbtGreen * gx_array[counter];
                        sum_blue_gx += image[update_i][ update_j].rgbtBlue * gx_array[counter];

                        sum_red_gy += image[update_i][ update_j].rgbtRed * gy_array[counter];
                        sum_green_gy += image[update_i][ update_j].rgbtGreen * gy_array[counter];
                        sum_blue_gy += image[update_i][ update_j].rgbtBlue * gy_array[counter];
                    }
                    // counter set to zero as for every neigbouer pixel muiltiplies by it's corrosponding gx & gy number
                    // even if a neighbour pixel does not exsist >> it's ok we will not make thing with it --
                    // as it's value will equal to zero
                    // and then we will also increment the counter thus when it will go to the next pixel --
                    // the next pixel can multiplies throught it's correct corrospnding pixel from gx && gy
                    counter++;
                }
            }
            // caluclating the formalla of the edge (gx2 + gy2) for the neigbour of the (pixel image[i][j])
            int final_red = round(sqrt(pow(sum_red_gx , 2) + pow(sum_red_gy , 2)));
            int final_green = round(sqrt(pow(sum_green_gx , 2) + pow(sum_green_gy , 2)));
            int final_blue = round(sqrt(pow(sum_blue_gx , 2) + pow(sum_blue_gy , 2)));

            // puting the result of (the new pixel) of the (pixel image[i][j]) in the copy of the original image
            // and insure that if the value of the new pixel over 255  it will be capped at 255
            // RESULT = (COND) ? (STATEMEN IF TRUE) : (STATEMENT IF FALSE)
            copy[i][j].rgbtRed = (final_red > 255) ? 255 : final_red;
            copy[i][j].rgbtGreen = (final_green > 255) ? 255 : final_green;
            copy[i][j].rgbtBlue = (final_blue > 255) ? 255 : final_blue;

        }
    }

    // copying pixel from the edge image(copied image) to the original image
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
