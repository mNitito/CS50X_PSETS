#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // array for store the binary value
    int binary[BITS_IN_BYTE];

    // propmt the user for input
    string message = get_string("Enter a message:");
    int len = strlen(message);

    // for loop to loop over every charcters
    for (int i = 0; i < len; i++)
    {

        // loop for loop over the decimal of the charcter
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {

            if ((message[i] % 2) == 0)
            {
                binary[j] = 0;
            }
            else
            {
                binary[j] = 1;
            }
            message[i] /= 2;
        }

        // for loop to print the reverse binary of the array binary
        for (int k = BITS_IN_BYTE - 1; k >= 0; k--)
        {
            print_bulb(binary[k]);
        }
        printf("\n");
    }
    // printf("%i \n", strlen(message));
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
