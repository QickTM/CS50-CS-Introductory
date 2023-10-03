#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int intWordsize);
int check_word(string strGuess, int intWordsize, int intStatus[], string strChoice);
void print_word(string strGuess, int intWordsize, int intStatus[]);

int main(int argc, string argv[])
{
    //Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    int intWordsize = 0;

    //Ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    if (!isdigit(argv[1][0]))
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    intWordsize = atoi(argv[1]);
    if (intWordsize < 5 || intWordsize > 8 || strlen(argv[1]) != 1)
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    //Open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", intWordsize);
    FILE* wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    //Load word file into an array of size LISTSIZE
    char options[LISTSIZE][intWordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    //Pseudorandomly select a word for this game
    srand(time(NULL));
    string strChoice = options[rand() % LISTSIZE];

    //Allow one more guess than the length of the word
    int intGuesses = intWordsize + 1;
    bool blWon = false;

    //Print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", intGuesses, intWordsize);

    //Main game loop, one iteration for each guess
    for (int i = 0; i < intGuesses; i++)
    {
        //Obtain user's guess
        string strGuess = get_guess(intWordsize);

        //Array to hold guess status, initially set to zero
        int intStatus[intWordsize];

        //Set all elements of status array initially to 0, aka WRONG
        for (int j = 0; j < intWordsize; j++)
        {
            intStatus[j] = WRONG;
        }

        //Calculate score for the guess
        int intScore = check_word(strGuess, intWordsize, intStatus, strChoice);

        printf("Guess %i: ", i + 1);

        //Print the guess
        print_word(strGuess, intWordsize, intStatus);

        //If they guessed it exactly right, set terminate loop
        if (intScore == EXACT * intWordsize)
        {
            blWon = true;
            break;
        }
    }

    //Print the game's result
    if (blWon == true)
    {
        printf("You won!\n");
    }
    else
    {
        printf("You lose!\n The correct word was %s\n", strChoice);
    }

    //That's all folks!
    return 0;
}

string get_guess(int intWordsize)
{
    string strGuess = "";

    //Ensure users actually provide a guess that is the correct length
    //Assuming user is does not enter a upper case letter
    do
    {
        strGuess = get_string("Input a %i-letter word: ", intWordsize);
    } while (strlen(strGuess) != intWordsize);
    return strGuess;
}

int check_word(string strGuess, int intWordsize, int intStatus[], string strChoice)
{
    int intScore = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    // iterate over each letter of the guess
    for (int i = 0; i < intWordsize; i++)
    {
        // iterate over each letter of the choice
        for (int j = 0; j < intWordsize; j++)
        {
            // compare the current guess letter to the current choice letter
            if (strGuess[i] == strChoice[j])
            {
                // if they're the same position in the word, score EXACT points (green) and break so you don't compare that letter further
                if (i == j)
                {
                    intStatus[i] = EXACT;
                    break;
                }
                // if it's in the word, but not the right spot, score CLOSE point (yellow)
                else
                {
                    intStatus[i] += CLOSE;
                }
            }
        }
        // keep track of the total score by adding each individual letter's score from above
        intScore += intStatus[i];
    }
    return intScore;
}

void print_word(string strGuess, int intWordsize, int intStatus[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    for (int i = 0; i < intWordsize; i++)
    {
        if (intStatus[i] == EXACT)
        {
            printf(GREEN "%c" RESET, strGuess[i]);
        }
        else if (intStatus[i] == 1)
        {
            printf(YELLOW "%c" RESET, strGuess[i]);
        }
        else
        {
            printf(RED "%c" RESET, strGuess[i]);
        }
    }
    printf("\n");
    return;
}