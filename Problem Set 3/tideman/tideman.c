#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool creates_cycles (int intWinner, int intLoser);
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //Check if input name is the same as one of the candidates' names
    for (int i = 0; i < candidate_count; i++)
    {
        //Update the rank corredsponding to the name
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Loop through the candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        //Go the the less prefered candidate after the most prefered candidate
        for (int j = i + 1; j < candidate_count; j++)
        {
            //Change the ranks of the candidates
            int preferred_candidate = ranks[i];
            int less_preferred_candidate = ranks[j];

            //Increment the number of preferences over the less prefered ones
            preferences[preferred_candidate][less_preferred_candidate]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    //Add all pairs of candidates where one candidate is preferred to the pairs array.
    //A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            //Check if "i" candidate is preferred over "j" and vice versa
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //"pair_count - 1" as there is no need to compair the last pair
    for (int i = 0; i < pair_count - 1; i++)
    {
        //Check unsorted pairs in the array to check if the element is the largest unsorted element and placed at the end of the array
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            //Get the votes of the current pair
            int intVotes1 = preferences[pairs[j].winner][pairs[j].loser];
            int intVotes2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            if (intVotes1 < intVotes2)
            {
                //Make a temporary pair
                pair pTemp = pairs[j];

                //Swap position if the current pair and subsequent has a greated victory
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = pTemp;
            }
        }
    }
    return;
}

//Find out of the adding of 2 candidates creates a cycle
bool creates_cycles (int intWinner, int intLoser)
{
    if (intWinner == intLoser)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[intLoser][i])
        {
            if (creates_cycles(intWinner, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //
    for (int i = 0; i < pair_count; i++)
    {
        //Add the current pair to locked graph
        int intWinner = pairs[i].winner;
        int intLoser = pairs[i].loser;

        locked[intWinner][intLoser] = true;

        //If a cycle is created change the bool value of "locked" to FALSE
        if (creates_cycles(pairs[i].winner, pairs[i].loser))
        {
            locked[intWinner][intLoser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //
    for (int i = 0; i < candidate_count; i++)
    {
        bool blWinner = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                blWinner = false;
                break;
            }
        }

        if (blWinner)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}