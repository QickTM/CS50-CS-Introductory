#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Declare the number of bits we are working with
const int BITS_IN_BYTE = 8;

//Passing and int variable into func
void print_bulb(int intBit);

int main(void)
{
    // TODO
    string strMessage = get_string("Enter message: ");

    //Go through each character in the message loop
    for (int i = 0; i < strlen(strMessage); i++)
    {
        int intBinary[] = {0, 0, 0, 0, 0, 0, 0, 0};

        //Convert the chracter into its ASCII value
        int intDecimal = strMessage[i];

        int j = 0;
        while (intDecimal > 0)
        {
            //Formual to get the binary value from the ASCII code
            //However its output is from left to right, but binary is read right to left
            intBinary[j] = intDecimal % 2;
            intDecimal = intDecimal / 2;

            j++;
        }

        //Reverse the bit then prtint them
        //"k--" to go from the right to the left since furthest bit is 7, 6, 5,...., 1, 0
        for (int k = BITS_IN_BYTE - 1; k >= 0; k--)
        {
            print_bulb(intBinary[k]);
        }
        printf("\n");
    }
}

void print_bulb(int intBit)
{
    if (intBit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (intBit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
