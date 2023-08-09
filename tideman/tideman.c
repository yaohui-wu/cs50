#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates.
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j.
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j.
bool locked[MAX][MAX];

// Each pair has a winner, loser.
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates.
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes.
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void merge_sort(pair candidate_pairs[], int left, int right);
void merge(pair candidate_pairs[], int left, int mid, int right);
int victory(pair pair);
void lock_pairs(void);
bool has_cycle(int start, int end);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage.
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");

        return 1;
    }

    // Populate array of candidates.
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %d\n", MAX);

        return 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes.
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference.
        int ranks[candidate_count];

        // Query for each rank.
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %d: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");

                return 1;
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

// Update ranks given a new vote.
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;

            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks.
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other.
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
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
}

// Sort pairs in decreasing order by strength of victory.
void sort_pairs(void)
{
    merge_sort(pairs, 0, pair_count - 1);
}

void merge_sort(pair candidate_pairs[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Sort left and right halves.
        merge_sort(candidate_pairs, left, mid);
        merge_sort(candidate_pairs, mid + 1, right);

        // Merge the sorted left and right halves.
        merge(candidate_pairs, left, mid, right);
    }
}

void merge(pair candidate_pairs[], int left, int mid, int right)
{
    int left_pairs_length = mid - left + 1;
    pair left_pairs[left_pairs_length];

    for (int i = 0; i < left_pairs_length; i++)
    {
        left_pairs[i] = candidate_pairs[left + i];
    }

    int right_pairs_length = right - mid;
    pair right_pairs[right_pairs_length];

    for (int i = 0; i < right_pairs_length; i++)
    {
        right_pairs[i] = candidate_pairs[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < left_pairs_length && j < right_pairs_length)
    {
        if (victory(left_pairs[i]) > victory(right_pairs[j]))
        {
            candidate_pairs[k] = left_pairs[i];
            i++;
        }
        else
        {
            candidate_pairs[k] = right_pairs[j];
            j++;
        }
        k++;
    }

    while (i < left_pairs_length)
    {
        candidate_pairs[k] = left_pairs[i];
        i++;
        k++;
    }

    while (j < right_pairs_length)
    {
        candidate_pairs[k] = right_pairs[j];
        j++;
        k++;
    }
}

int victory(pair pair)
{
    int victory = preferences[pair.winner][pair.loser];

    return victory;
}

// Lock pairs into the candidate graph in order, without creating cycles.
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!has_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool has_cycle(int start, int end)
{
    if (locked[end][start])
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i] && has_cycle(start, i))
        {
            return true;
        }
    }

    return false;
}

// Print the winner of the election.
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                false_count++;
                
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);

                    return;
                }
            }
        }
    }
}