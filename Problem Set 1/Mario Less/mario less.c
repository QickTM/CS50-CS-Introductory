#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //TODO: Get height value
    int intHeight;
    do{
        intHeight = get_int("Enter wanted height: ");
    }
    while(intHeight < 1 || intHeight > 8);

    //TODO: Create blocks in a pyramid
    for (int intRows = 0; intRows < intHeight; intRows++)
    {
        //Add blanks before the "#"
        for(int intBlanks = 0; intBlanks < intHeight - intRows - 1; intBlanks++)
        {
            printf(" ");
        }
        //Add "#" as blocks
        for (int intColumns = 0; intColumns <= intRows; intColumns++)
        {
            printf("#");
        }
        printf("\n");
    }

}