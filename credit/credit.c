#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // prompt the user for input
    long card;
    do
    {
        card = get_long("Enter your card number:");
    }
    while (card < 0);

    // checksum
    // checksum(card);

    int sum1, sum2, sum3;
    int card1, card2, card3, card4, card5, card6, card7;
    int card8, card9, card10, card11, card12, card13, card14, card15, card16;
    // for cards that is multiplayed by 2
    card1 = ((card % 100) / 10) * 2;
    card2 = ((card % 10000) / 1000) * 2;
    card3 = ((card % 1000000) / 100000) * 2;
    card4 = ((card % 100000000) / 10000000) * 2;
    card5 = ((card % 10000000000) / 1000000000) * 2;
    card6 = ((card % 1000000000000) / 100000000000) * 2;
    card7 = ((card % 100000000000000) / 10000000000000) * 2;
    card8 = ((card % 10000000000000000) / 1000000000000000) * 2;
    //           for secound digit        for first digit (last digit)
    // card(n) = ((card(n) % 100) / 10) + ((card(n) % 10) / 1);
    card1 = ((card1 % 100) / 10) + ((card1 % 10) / 1);
    card2 = ((card2 % 100) / 10) + ((card2 % 10) / 1);
    card3 = ((card3 % 100) / 10) + ((card3 % 10) / 1);
    card4 = ((card4 % 100) / 10) + ((card4 % 10) / 1);
    card5 = ((card5 % 100) / 10) + ((card5 % 10) / 1);
    card6 = ((card6 % 100) / 10) + ((card6 % 10) / 1);
    card7 = ((card7 % 100) / 10) + ((card7 % 10) / 1);
    card8 = ((card8 % 100) / 10) + ((card8 % 10) / 1);

    sum1 = card1 + card2 + card3 + card4 + card5 + card6 + card7 + card8;

    // for the rest of cards that is not muliplayed byy 2
    card9 = ((card % 10) / 1);
    card10 = ((card % 1000) / 100);
    card11 = ((card % 100000) / 10000);
    card12 = ((card % 10000000) / 1000000);
    card13 = ((card % 1000000000) / 100000000);
    card14 = ((card % 100000000000) / 10000000000);
    card15 = ((card % 10000000000000) / 1000000000000);
    card16 = ((card % 1000000000000000) / 100000000000000);

    // there is no necessary to differentiate the cards as they doesn't multiplayed by 2

    sum2 = card9 + card10 + card11 + card12 + card13 + card14 + card15 + card16;
    sum3 = sum1 + sum2;

    if (((sum3 % 10) / 1) != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    long VISA = card;
    long MASTER = card;
    long AMEX = card;

    // get the length of the card
    int length = 0;
    while (card > 0)
    {
        card = card / 10;
        length++;
    }

    // Detrmine VISACARD
    // condition >= 10 as visa is 13 or 16 length
    while (VISA >= 10)
    {
        VISA /= 10;
    }
    if (VISA == 4 && (length == 13 || length == 16))
    {
        printf("VISA\n");
        return 0;
    }
    printf("hello");
    // Detrmine AMEX
    // the condition is smaller than 10 ^ 3 as AMEX == 15 length
    // And we need to compare the first two digits ..thus 15 -2 == 13
    while (AMEX >= 10000000000000)
    {
        AMEX /= 10000000000000;
    }

    if ((AMEX == 34 || AMEX == 37) && length == 15)
    {
        printf("AMEX\n");
        return 0;
    }

    // Detrmine MASTERCARD
    while (MASTER >= 100000000000000)
    {
        MASTER = MASTER / 100000000000000;
    }
    if ((MASTER == 51 || MASTER == 52 || MASTER == 53 || MASTER == 54 || MASTER == 55) && length == 16)
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

/* int checksum(long card)
{
   i
return sum3;
} */

/* int checklength(long card)
{
}
*/

/* int checkcard(long card , int length)
{
    return 0;
}
*/