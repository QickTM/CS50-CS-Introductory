#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

//Declare function
int compute_score(string word);

int main(void)
{
    //Get input words from both players
    string strWord1 = get_string("Player 1: ");
    string strWord2 = get_string("Player 2: ");

    //Score both words
    int intPlyScore1 = compute_score(strWord1);
    int intPlyScore2 = compute_score(strWord2);

    //Print the winner
    if (intPlyScore1 > intPlyScore2)
    {
        printf("%s\n", "Player 1 wins!");
    }
    else if (intPlyScore2 > intPlyScore1)
    {
        printf("%s\n", "Player 2 wins!");
    }
    else
    {
        printf("%s\n", "Tie!");
    }
}

int compute_score(string strWord)
{
    //Compute and return score for string
    int intScore = 0;
    int intLength = strlen(strWord);

    for (int i = 0; i < intLength; i++)
    {
        //The isupper() and islower() checks for lower or upper case letters
        if (isupper(strWord[i]))
        {
            //Find letter, if upper case look for score in table
            intScore += POINTS[strWord[i] - 'A'];
        }
        else if (islower(strWord[i]))
        {
            //Find letter, if lower case look for score in table
            intScore += POINTS[strWord[i] - 'a'];
        }
    }
    return intScore;
}
