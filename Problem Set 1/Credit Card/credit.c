#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long longCard;

    do
    {
        longCard = get_long("Credit/Debit card number: ");
    }
    while(longCard < 0);

    //Card number from right starting fron 2nd number
    int intCard2, intCard4, intCard6, intCard8, intCard10, intCard12, intCard14, intCard16;

    //Card number from right starting fron 1st number
    int intCard1, intCard3, intCard5, intCard7, intCard9, intCard11, intCard13, intCard15;

    //To find the value of each card number's position (alternating in twos) form the right starting from 2nd number
    intCard2 = ((longCard % 100)/10*2);
    intCard4 = ((longCard % 10000)/1000*2);
    intCard6 = ((longCard % 1000000)/100000*2);
    intCard8 = ((longCard % 100000000)/10000000*2);
    intCard10 = ((longCard % 10000000000)/1000000000*2);
    intCard12 = ((longCard % 1000000000000)/100000000000*2);
    intCard14 = ((longCard % 100000000000000)/10000000000000*2);
    intCard16 = ((longCard % 10000000000000000)/1000000000000000*2);

    //Find the front number X, where in "000XY" X is the second number from the right and so on
    intCard2 = (intCard2 % 100/10) + (intCard2 % 10);
    intCard4 = (intCard4 % 100/10) + (intCard4 % 10);
    intCard6 = (intCard6 % 100/10) + (intCard6 % 10);
    intCard8 = (intCard8 % 100/10) + (intCard8 % 10);
    intCard10 = (intCard10 % 100/10) + (intCard10 % 10);
    intCard12 = (intCard12 % 100/10) + (intCard12 % 10);
    intCard14 = (intCard14 % 100/10) + (intCard14 % 10);
    intCard16 = (intCard16 % 100/10) + (intCard16 % 10);

    int intHalf1 = intCard2 + intCard4 + intCard6 + intCard8 + intCard10 + intCard12 + intCard14 + intCard16;

    //To find the value of each card number's position (alternating in twos) form the right starting from 1st number
    intCard1 = ((longCard % 10));
    intCard3 = ((longCard % 1000)/100);
    intCard5 = ((longCard % 100000)/10000);
    intCard7 = ((longCard % 10000000)/1000000);
    intCard9 = ((longCard % 1000000000)/100000000);
    intCard11 = ((longCard % 100000000000)/10000000000);
    intCard13 = ((longCard % 10000000000000)/1000000000000);
    intCard15 = ((longCard % 1000000000000000)/100000000000000);

    int intHalf2 = intCard1 + intCard3 + intCard5 + intCard7 + intCard9 + intCard11 + intCard13 + intCard15;
    int intTotal = intHalf1 + intHalf2;

    //Find the last digit of intTotal
    int intCardNumLength = 0;
    long longVisa = longCard;
    long longMaster = longCard;
    long longAmex = longCard;

    if ((intTotal % 10) != 0)
    {
        printf("%s\n", "INVALID");
        return 0;
    }

    else
    {
        //Identify VISA, MASTERCARD, AMERICAN EXPRESS
        while (longCard > 0 )
        {
            longCard = longCard / 10;
            intCardNumLength++;
        }

        //VISA
        while (longVisa >= 10)
        {
            longVisa /= 10;
        }
        if (longVisa == 4 && (intCardNumLength == 13 || intCardNumLength == 16))
        {
            printf("%s\n", "VISA");
            return 0;
        }

        //MASTERCARD
        while (longMaster >= 100000000000000)
        {
            longMaster /= 100000000000000;
        }
        if (intCardNumLength == 16 && (longMaster == 51 || longMaster == 52 || longMaster == 53 || longMaster == 54 || longMaster == 55))
        {
            printf("%s\n", "MASTERCARD");
            return 0;
        }

        //AMERICAN EXPRESS
        while (longAmex >= 10000000000000)
        {
            longAmex /= 10000000000000;
        }
        if (intCardNumLength == 15 && (longAmex == 34 || longAmex == 37))
        {
            printf("%s\n", "AMEX");
            return 0;
        }

        else
        {
            printf("%s\n", "INVALID");
            return 0;
        }
    }

}