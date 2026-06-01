#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
int search(void);
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Checking for existance of a tie
    if (search() == 0)
    {
        candidate tie1[candidate_count];
        int count = 0;
        // Finding the winning count
        int highest = candidates[0].votes;
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes > highest)
            {
                highest = candidates[i].votes;
            }
            else
            {
                continue;
            }
        }
        // Calculating if there any ties with the winning count
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == highest)
            {
                count += 1;
                tie1[count] = candidates[i];
            }
        }
        for (int m = 1; m <= count; m++)
        {
            printf("%s", tie1[m].name);
            printf("\n");
        }
        return;
    }
    else
    {
        // No ties exist, using selection sort
        candidate order[candidate_count];
        for (int i = 0; i < candidate_count; i++)
        {
            order[i] = candidates[i];
        }

        for (int i = 0; i < candidate_count; i++)
        {
            candidate smallest;
            smallest = order[i];
            int index = i;
            for (int j = i + 1; j < candidate_count; j++)
            {
                if (order[j].votes < smallest.votes)
                {
                    smallest = order[j];
                    index = j;
                }
                else
                {
                    continue;
                }
            }
            candidate temp = order[i];
            order[i] = smallest;
            order[index] = temp;
        }
        printf("%s\n", order[candidate_count - 1].name);

        return;
    }
}

// tie detection
int search(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (candidates[i].votes == candidates[j].votes)
            {
                if (candidates[i].votes == 0 && candidates[j].votes == 0)
                {
                    continue;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
