#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Prompt user for input
    string text = get_string("Text: ");

    // Calculating length of string(text)
    int n = strlen(text);

    // Calculating total number of letters
    int l = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            l += 1;
        }
    }

    // Calculating total number of words
    int s = 0;
    int w = 0;
    for (int j = 0; j < n; j++)
    {
        if (isblank(text[j]))
        {
            s += 1;
        }
    }
    w = s + 1;

    // Calculating total number of sentences
    int v = 0;
    for (int k = 0; k < n; k++)
    {
        if (text[k] == 33 || text[k] == 46 || text[k] == 63)
        {
            v += 1;
        }
    }

    // Calculation 'L' and 'S'
    float L = (l / (float) w) * 100;
    float S = (v / (float) w) * 100;

    // Calculating grade level using  Coleman-Liau index
    float index = (0.0588 * L - 0.296 * S - 15.8);
    int grade = round(index);

    // Printing output to user
    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (grade > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
