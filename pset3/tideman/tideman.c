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
bool check_cycle(int row, int col);
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
    // TODO
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
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int row = ranks[i];

        for (int j = candidate_count - 1; j > 0 ; j--)
        {
            int column = ranks[j];

            if (row != column)
                preferences[row][column]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences [j][i] > preferences[i][j])
            {
                pairs[pair_count].loser = i;
                pairs[pair_count].winner = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //TODO
    bool valid = false;
    int swap = 0;
    do
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            swap = 0;
            int p_rows = pairs[i].winner;
            int p_cols = pairs[i].loser;
            int p_rows1 = pairs[i + 1].winner;
            int p_cols1 = pairs[i + 1].loser;

            if (preferences[p_rows][p_cols] < preferences[p_rows1][p_cols1])
            {
                pair tmp = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = tmp;
                swap ++;
            }
        }
        if (swap == 0)
            valid = true;
    }
    while (valid == false);
    return;
}

//Check if a cycle is created
bool check_cycle(int row, int col)
{
    if (locked[col][row])
            return false;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (locked[col][i])
        {
            if (!check_cycle(row, i))
                return false;
        }
    }
    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //Sets all winners as true
    for (int i = 0; i < pair_count; i++)
    {
        int row = pairs[i].winner;
        int col = pairs[i].loser;

        locked[row][col] = true;
        locked[row][col] = check_cycle(row, col);
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int place = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
                place++;
        }
        if (place == candidate_count)
            printf("%s\n", candidates[i]);
    }
}