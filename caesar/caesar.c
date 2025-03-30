#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check for the input condition
    if (argc != 2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key \n");
            return 1;
        }
    }

    // prompt the user for plaintext
    string plaintext = get_string("plaintext: ");

    // convert plaintext to ciphertext

    // convert argv[1] to int
    int key = (atoi(argv[1]));

    // print ciphertext: on the terminal
    printf("ciphertext: ");
    for (int j = 0; j < strlen(plaintext); j++)
    {
        if (islower(plaintext[j]))
        {
            printf("%c", (plaintext[j] + key - 97) % 26 + 97);
        }
        else if (isupper(plaintext[j]))
        {

            printf("%c", (plaintext[j] + key - 65) % 26 + 65);
        }
        else
        {
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");
}
// yxocll