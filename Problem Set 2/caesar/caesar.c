#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

//Use to change the letter of the alphabet down the stated value in caesar
int main(int argc, string argv[])
{
    //Check for command line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Key
    string strKey = argv[1];

    //See if input is an integer
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        // "isdight" is to check if there are only numbers
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //Get text from the user
    string strText = get_string("plaintext: ");

    //Convert the "Key" string to an integer
    int intKey = atoi(strKey);
    printf("ciphertext: ");

    //Get the ciphered text
    char cUpper, cLower;
    for (int i = 0; i < strlen(strText); i++)
    {
        //Formula to change the text depending one upper or lower case
        cUpper = (((strText[i] - 65) + intKey) % 26) + 65;
        cLower = (((strText[i] - 97) + intKey) % 26) + 97;

        if (isupper(strText[i]))
        {
            printf("%c", cUpper);
        }
        else if (islower(strText[i]))
        {
            printf("%c", cLower);
        }
        else
        {
            //Keep the character (i.e. punctuation) after cipher
            printf("%c", strText[i]);
        }
    }
    printf("\n");
}
