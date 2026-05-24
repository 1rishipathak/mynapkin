#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Ensure proper CLI usage
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Validate the key
    string key = argv[1];
    int n = strlen(key);

    // Checking the length of the key
    if (n != 26)
    {
        printf("Key must be 26 characters long.\n");
        return 1;
    }

    // Checking for non-alphabetic characters
    for (int i = 0; i < n; i++)
    {
        if(!(isalpha(argv[1][i])))
        {
            printf("Key must contain alphabetic characters.\n");
            return 1;
        }
    }

    // Checking for repeated characters
    for (int i = 0; i < n; i++)
    {
        for ( int j = i + 1; j < n; j++)
            if( key[i] == key[j] || key[i] == key[j] - 32 || key[i] == key[j] + 32)
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
    }

    // ***----- KEY HAS BEEN VALIDATED -----** //

    // Prompt user for input
    string text = get_string("plaintext:  ");
    int m = strlen(text);

    // Making a copy of original input
    char input[m];
    for (int i = 0; i < m; i++)
    {
        input[i] = text[i];
    }

    // Declaration of arrays of letters
    char lettersc[26];
    char letters[26];

    for( int i = 0; i < 26; i++)
    {
        lettersc[i] = i + 'A';
    }
    for( int i = 0; i < 26; i++)
    {
        letters[i] = i + 'a';
    }

    // Mapping plaintext to the key
    for (int i = 0; i < m; i++)
        if(!(isalpha(text[i])))
            {continue;}
        else
        {
        for ( int j = 0; j < 26; j++)
            if( text[i] == letters[j] || text[i] == lettersc[j])
                {
                    text[i] = key[j];
                    break;
                }
        }

    // Printing the ciphertext
    printf("ciphertext: ");
    for ( int i = 0; i < m; i++)
        if(!(isalpha(input[i])))
        {
            printf("%c", input[i]);
        }
        else if(isupper(input[i]))
        {
            if(isupper(text[i]))
            {
                printf("%c",text[i]);
            }
            else if(islower(text[i]))
            {
                printf("%c",toupper(text[i]));
            }
        }
        else if(islower(input[i]))
        {
            if(islower(text[i]))
            {
                printf("%c",text[i]);
            }
            else if(isupper(text[i]))
            {
                printf("%c",tolower(text[i]));
            }
        }
    printf("\n");
    return 0;
}
