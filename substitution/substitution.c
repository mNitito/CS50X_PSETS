#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // get key
    if (argc != 2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

    // validate key by
    //  check the key length
    if (strlen(argv[1]) != 26)
    {
        printf("You should enter a 26 charcter");
        return 1;
    }
    // check for non alphabetic characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("the string must contains characters only");
            return 1;
        }
    }

    // converting alphabetical to upper to unified the string characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        argv[1][i] = toupper(argv[1][i]);
    }

    // check for repeated charaters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        /// we will gonna make insted loop for points on a charcter and --
        /// checks it with all the rest of the string charcters
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (argv[1][j] == argv[1][i])
            {
                printf("charcters not allow to be repeated \n");
                return 1;
            }
        }
    }
    // prompt the user for plaintext
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    // creating argv[1] array
    // edit : there is no array as there is not a constant subsitution input

    // Assigning the value of the alphabetical to it's ciphertext
    for (int k = 0; k < strlen(plaintext); k++)
    {
        if (isupper(plaintext[k]))
        {
            printf("%c", argv[1][plaintext[k] - 'A']);
        }
        else if (islower(plaintext[k]))
        {
            printf("%c", tolower(argv[1][plaintext[k] - 'a']));
        }
        else
        {
            printf("%c", plaintext[k]);
        }
    }
    printf("\n");
}