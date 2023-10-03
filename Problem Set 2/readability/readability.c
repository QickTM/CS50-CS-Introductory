#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //Get text from user
    string strText = get_string("Text: ");
    printf("%s\n", strText);

    //Count number of letter in the given text
    int intLetters = 0;
    for (int i = 0; i < strlen(strText); i++)
    {
        //Check the text for both lower and uppcase range of letters
        if((strText[i] >= 'a' && strText[i] <= 'z') || (strText[i] >= 'A' && strText[i] <= 'Z'))
        {
            intLetters++;
        }
    }

    //Count number of letter in the given text
    int intWords = 1;
    for (int i = 0; i < strlen(strText); i++)
    {
        //Check for spaces in between the words of the sbumited text
        if(strText[i] == ' ')
        {
            intWords++;
        }
    }

    //Count number of setences in the text where each sentence ends with a "." or "?" or "!"
    int intSentences = 0;
    for (int i = 0; i < strlen(strText); i++)
    {
        //Check for the "." or "?" or "!" in the text
        if((strText[i] == '.' || strText[i] == '?' || strText[i] == '!'))
        {
            intSentences++;
        }
    }

    //Using Coleman-Liau index formula to determine the grade of readability
    float fltCal = (0.0588 * intLetters / intWords * 100) - (0.296 * intSentences / intWords * 100) - 15.8;
    int intIndex = round(fltCal);

    if (intIndex < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (intIndex >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %i\n", intIndex);
    }
}