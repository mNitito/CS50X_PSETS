#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open card");
        return 2;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];
    int counter = 0;
    char filename[100];
    // declare a file pointer and handel it
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card))
    {
        // if you found a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Create JPEGs from the data
            if (counter == 0)
            {
                // create a jpeg file
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");

                // check if file opens
                if (img == NULL)
                {
                    fclose(card);
                    printf("Could not open %s.\n", filename);
                    return 1;
                }
                fwrite(buffer, 1, 512, img);
                counter++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fclose(card);
                    printf("Could not open %s.\n", filename);
                    return 2;
                }
                fwrite(buffer, 1, 512, img);
                counter++;
            }
        }
        else if (counter != 0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    fclose(card);
    fclose(img);
}
