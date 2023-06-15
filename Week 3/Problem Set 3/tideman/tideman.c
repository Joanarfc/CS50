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
bool check_cycle(int winner, int loser);
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
        if (strcmp(name, candidates[i]) == 0)
        {
            // Update the ranks[] with the rank and position of the candidate, i:
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Update the preferences
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // Maximum number of pairs that could possibly exist
    int max_pairs = candidate_count * (candidate_count - 1) / 2;

    for (int i = 0; i < candidate_count - 1 && pair_count < max_pairs; i++)
    {
        for (int j = 0; j < candidate_count && pair_count < max_pairs; j++)
        {
            // Pair already exists?
            bool pair_exists = false;
            for (int k = 0; k < pair_count; k++)
            {
                if (pairs[k].winner == i && pairs[k].loser == j)
                {
                    pair_exists = true;
                    break;
                }
            }

            // If it doesn't exist, add pair
            if (!pair_exists && preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (!pair_exists && preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser];
            int strength2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            // if the next pair has more strength than the current pair, swap them
            if (strength1 < strength2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;

            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    bool locked_candidates[MAX] = {false};

    for (int i = 0; i < pair_count; i++)
    {
        pair current_pair = pairs[i];
        int winner = current_pair.winner;
        int loser = current_pair.loser;

        if (!check_cycle(winner, loser))
        {
            locked[winner][loser] = true;
            locked_candidates[loser] = true;
        }
    }
}

bool check_cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true && check_cycle(winner, i))
        {
            return true;
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    bool is_winner[MAX] = {true};

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                is_winner[i] = false;
                break;
            }
            else if (j == candidate_count - 1)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (is_winner[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
}