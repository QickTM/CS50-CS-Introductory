#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Check for command line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //Check that the input contains only letters
    string strKey = argv[1];
    for (int i = 0; i < strlen(strKey); i++)
    {
        // "isalpha" is to check if there is only alphabets
        if (!isalpha(strKey[i]))
        {
            printf("Usage: ./substituion key\n");
            return 1;
        }
    }

    //Check if the key string only contains 26 letters
    if (strlen(strKey) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    //Check that there are no duplicate letters in the key
    // "i" stands for current letter being checked
    // "j" stands for the letter after
    for (int i = 0; i < strlen(strKey); i++)
    {
        for (int j = i + 1; j < strlen(strKey); j++)
        {
            //Check for duplicate upper case letters
            if (toupper(strKey[i] == toupper(strKey[j])))
            {
                printf("Usage: ./substituion key\n");
                return 1;
            }

            ////Check for duplicate lower case letters
            else if (tolower(strKey[i] == tolower(strKey[j])))
            {
                printf("Usage: ./substituion key\n");
                return 1;
            }
        }
    }

    //Ask the user for text
    string strText = get_string("plaintext: ");

    //Make all letters in the strKey upper case
    for (int i = 0; i < strlen(strKey); i++)
    {
        if (islower(strKey[i]))
        {
            strKey[i] = strKey[i] - 32;
        }
    }

    //Output the ciphered text
    printf("ciphertext: ");
    for (int i = 0; i < strlen(strText); i++)
    {
        if (isupper(strText[i]))
        {
            int intOfLetter = strText[i] - 65;
            printf("%c", strKey[intOfLetter]);
        }
        else if (islower(strText[i]))
        {
            int intOfLetter = strText[i] - 97;

            //Convert it back to lower case
            printf("%c", strKey[intOfLetter] + 32);
        }
        else
        {
            printf("%c", strText[i]);
        }
    }
    printf("\n");
}