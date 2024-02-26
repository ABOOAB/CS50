#include <ctype.h>
#include <cs50.h>
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

    //player 1 win
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    //player 2 win
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }

    //no winner
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    //make sure it's uppercase string
    for (int i = 0, n = strlen(word); i < n ; i++)
    {
        word[i] = toupper(word[i]);
    }

    // get sum of points
    int asci, sum = 0 ;
    int i = 0;
    while (word [i] != '\0')
    {
        asci = (int) word[i] - 65 ;

        //ckeck that the string is just letters
        if (asci >= 0 && asci <= 65)
        {
            sum += POINTS[asci] ;
        }

        i++ ;

    }
    return sum;
}
