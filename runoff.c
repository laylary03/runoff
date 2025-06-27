#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Max number of candidates
#define MAX 9

#define MAX_VOTERS 11
#define MAX_CANDIDATES 9

// Global variables
candidate candidates[MAX];
int preferences[MAX_VOTERS][MAX_CANDIDATES];
int candidate_count;
int voter_count;

// Functions
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    if (argc >= 1)
    {
        candidate_count = argc - 1;
        if (candidate_count > MAX)
        {
            printf("Maximum number of candidates is %i\n", MAX);
            return 2;
        }
        else
        {
            // Sorts given names in candidates struct
            for (int i = 0; i < (candidate_count); i++)
            {
                candidates[i].name = argv[i + 1];
                candidates[i].votes = 0;
                candidates[i].eliminated = false;
            }

            // Loop that will execute 'vote' function every time user inputs a name
            int voters = get_int("Number of voters: ");
            voter_count = voters;
            string unsorted_vote[voter_count];
            for (int i = 0; i < voter_count; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    unsorted_vote[i] = get_string("Rank %i: ", j + 1);
                    if (!vote(i, j, unsorted_vote[i]))
                    {
                        printf("Invalid vote.\n");
                        return 3;
                    }
                }
                printf("\n");
            }
            // 'tabulate' function gives votes to candidates who haven't been eliminated
            tabulate();
            int minimum = find_min();
            if (is_tie(minimum) == true)
            {
                // Ensures all candidates are not tied
                do
                {
                    eliminate(minimum);
                    tabulate();
                    print_winner();
                }
                while (is_tie(minimum) == true && print_winner() == false);
            }
        }
    }
    else
    {
        // Ensures that candidates are inputed
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }
}

// Look for candidate 'name' and updated preferences array if found
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // case sensitive!!
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Updates votes
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                // if not eliminated, give 1 vote to candidate (Rank 1)
                candidates[preferences[i][j]].votes++;
                j = 3;
            }
        }
    }
    return;
}

// Whoever has more than half the votes wins, return true
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Returns minimum amount of votes of anyone still in the election
int find_min(void)
{
    int loser;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            loser = i;
            for (int j = 1; j < candidate_count - 1; j++)
            {
                if (candidates[loser].votes > candidates[j].votes)
                {
                    if (candidates[j].eliminated == false)
                    {
                        loser = j;
                    }
                }
            }
        }
    }
    return candidates[loser].votes;
}

// Accepts minimum # of votes min as input
// Returns true if election is tied between all remaining candidates
bool is_tie(int min)
{
    int ties[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
                ties[i] = 1;
            else
                ties[i] = 0;
        }
    }

    for (int j = 0; j < candidate_count; j++)
    {
        // Asks if any one of the remaining candidate IS NOT tied at the min vote
        if (ties[j] == 0)
        {
            return false;
        }
    }
    return true;
}

// Eliminate anyone still in the race with min number of votes
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
