#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Ensure proper CLI usage
    // Incorrect number of CLIs
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Incorrect format of CLIs
    int n = strlen(argv[1]);
    for (int i = 0; i < n; i++)
    {
        if (argv[1][i] < 48 || argv[1][i] > 57)
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
        else
        {
            continue;
        }
    }

    // Defining key
    int key = atoi(argv[1]);

    // Prompt for input
    string text = get_string("Plaintext:  ");
    int m = strlen(text);

    // Creating copy of original text
    char input[m];
    for (int z = 0; z < m; z++)
    {
        input[z] = text[z];
    }

    // Ciphering plaintext
    // Indexing from ASCII to 0 onwards

    for (int j = 0; j < m; j++)
        if (!(isalpha(text[j])))
        {
            continue;
        }
        else if (isupper(text[j]))
        {
            text[j] = text[j] - 'A';
        }
        else if (islower(text[j]))
        {
            text[j] = text[j] - 'a';
        }

    // Applying cipher formula
    char output[m];
    for (int l = 0; l < m; l++)
        if (text[l] < 0 || text[l] > 25)
        {
            continue;
        }
        else
        {
            output[l] = (text[l] + key) % 26;
        }

    // Converting from Index to ASCII
    for (int h = 0; h < m; h++)
        if (!(isalpha(input[h])))
        {
            continue;
        }
        else if (isupper(input[h]))
        {
            output[h] = output[h] + 'A';
        }
        else if (islower(input[h]))
        {
            output[h] = output[h] + 'a';
        }

    // Printing Ciphertext
    printf("Ciphertext: ");
    for (int o = 0; o < m; o++)
        if (isalpha(input[o]))
        {
            printf("%c", output[o]);
        }
        else
        {
            printf("%c", input[o]);
        }
    printf("\n");
}
