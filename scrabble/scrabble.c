#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins! \n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins! \n");
    }
    else
    {
        printf("Tie! \n");
    }
}

int compute_score(string word)
{

    // assigning the score of each alphabtical
    // update: no need to assign this values and it also didn't workkk

    // TODO: Compute and return score for string
    // initliaze score to zero to add the suumation of the cracters

    int score = 0;
    // for loop to over the chracters of the srting and compute the suumation of the string charcters
    for (int i = 0; i < strlen(word); i++)
    {
        if (islower(word[i]))
        {
            score = score + POINTS[word[i] - 'a'];
        }
        else if (isupper(word[i]))
        {
            score = score + POINTS[word[i] - 'A'];
        }
        else if (word[i] < 65 || word[i] > 122)
        {
            score = score + 0;
        }
    }
    return score;
}
