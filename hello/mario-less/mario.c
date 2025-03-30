#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int row, coulmn, space, height;
    do
    {
        height = get_int("enter a number:");
    }
    while (height < 1 || height > 8);

    // NO.OF ROWS
    for (row = 0; row < height; row++)
    {
        // Spaces  -- form relation ship between no. of spaces , row and coulmns
        //  space = height - row - 1
        for (space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }
        // NO. OF # per coulmn
        for (coulmn = 0; coulmn <= row; coulmn++)
        {
            printf("#");
        }

        printf("\n");
    }
}