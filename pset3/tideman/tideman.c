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
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool check_loop(int win, int los, int numb);

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
    for (int i = 0; i < candidate_count; i++)
    {
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (k > i)
            {
                preferences[ranks[i]][ranks[k]]++; //update the ranks
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (k > i)
            {
                if (preferences[i][k] > preferences[k][i]) //update the pairs over preference
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = k;
                    pair_count++;
                }
                if (preferences[i][k] < preferences[k][i]) //update the pairs over the preferences
                {
                    pairs[pair_count].winner = k;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int pairs_power[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        pairs_power[i] = preferences[pairs[i].winner][pairs[i].loser]; // update power of victory for pair
    }

    bool k = 0;
    // substitution variables to store value while sorting
    int subs_power1 = 0;
    int subs_power2 = 0;

    int subs_winner1 = 0;
    int subs_winner2 = 0;

    int subs_loser1 = 0;
    int subs_loser2 = 0;

    do
    {
        k = true;
        for (int j = 0, n = pair_count - 1; j < n; j++)
        {
            if (pairs_power[j] < pairs_power[j + 1]) //check if pairs are decreasing
            {
                //if pairs are in wrong order, substitute them
                subs_power1 = pairs_power[j];
                subs_power2 = pairs_power[j + 1];

                subs_winner1 = pairs[j].winner;
                subs_winner2 = pairs[j + 1].winner;

                subs_loser1 = pairs[j].loser;
                subs_loser2 = pairs[j + 1].loser;

                pairs_power[j] = subs_power2;
                pairs_power[j + 1] = subs_power1;

                pairs[j].winner = subs_winner2;
                pairs[j + 1].winner = subs_winner1;

                pairs[j].loser = subs_loser2;
                pairs[j + 1].loser = subs_loser1;

                k = false;
            }
        }

    }
    while (k == false);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_loop(pairs[i].winner, pairs[i].loser, i)) // check for loops
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int false_count = 0;
    int winner = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (false_count == candidate_count)
        {
            printf("%s\n", candidates[winner]); //only winner of election have no loses
            return;
        }
        false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false) // check if candidate was defeated
            {
                false_count++;
                winner = i;
            }
        }
    }
    return;
}


bool check_loop(int win, int los, int numb)
{
    if (numb - 1 < 0)
    {
        return false;
    }
    int subs = win;
    for (int i = numb - 1; i >= 0; i--)
    {
        if (pairs[i].winner == los && pairs[i].loser == subs) //look for previous destintion
        {
            return true;
        }
        else if (pairs[i].loser == subs)
        {
            subs = pairs[i].winner; // update "previous destination"
        }
    }
    return false;
}