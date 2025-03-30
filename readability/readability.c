#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // promt the user for the text
    string text = get_string("Text: ");

    // calaculates the number of letters
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    // calaculates the number of words
    int words = 0;
    for (int j = 0; j < strlen(text); j++)
    {
        if ((text[j] == ' ' && text[j] != 0))
        {
            words++;
        }
    }
    words++;

    // caclculates the number of sentences
    int sentences = 0;
    for (int k = 0; k < strlen(text); k++)
    {
        if (text[k] == '.' || text[k] == '?' || text[k] == '!')
        {
            sentences++;
        }
    }
    // printf("%i \n",letters);
    // printf("%i \n",words);
    // printf("%i \n",sentences);

    // claculate number of letters per 100 words
    int L = (float) letters / (float) words * 100;

    // claculate number of sentences per 100 words
    int S = (float) sentences / (float) words * 100;

    // compute the readability level through Coleman-Liau index.
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // if condition about the dagree of the readability
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}