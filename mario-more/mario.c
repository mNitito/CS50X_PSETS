#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, row, space, coulmn;
    do
    {
        height = get_int("Entar The height of pyramid:");
    }
    while (height < 1 || height > 8);

    // loop for rows
    for (row = 0; row < height; row++)
    {
        // nested loop for spaces before #
        for (space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }

        // nested loop for # per coulmn
        for (coulmn = 0; coulmn <= row; coulmn++)
        {
            printf("#");
        }

        // print spaces between the two pyramids
        printf("  ");

        // print # for the secound pramid
        for (coulmn = 0; coulmn <= row; coulmn++)
        {
            printf("#");
        }

        // printf("\n"); for enter a new line for each row || making a  new row
        printf("\n");
    }
}