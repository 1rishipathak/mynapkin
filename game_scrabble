#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
 //Get input from the user
   string p1 = get_string("Player 1: ");
   string p2 = get_string("Player 2: ");

    // Calculate input length
    int n1 = strlen(p1);
    int n2 = strlen(p2);

 //Creative arrays with data of scribble rules
   int letters[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
   int lettersc[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
   int values[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

    // Assign values/points to letters
    // P1
    for (int i = 0; i < n1; i++)
    {
        if (p1[i] < 65 || p1[i] > 122)
        {
            p1[i] = 0;
        }
        else if (p1[i] >= 91 && p1[i] <= 96)
        {
            p1[i] = 0;
        }
        for (int j = 0; j < 26; j++)
        {
            if (p1[i] == letters[j] || p1[i] == lettersc[j])
            {
                p1[i] = values[j];
                break;
            }
            else
            {
                continue;
            }
        }
    }

    // P2
    for (int k = 0; k < n2; k++)
    {
        if (p2[k] < 65 || p2[k] > 122)
        {
            p2[k] = 0;
        }
        else if (p2[k] >= 91 && p2[k] <= 96)
        {
            p2[k] = 0;
        }

        for (int l = 0; l < 26; l++)
        {
            if (p2[k] == letters[l] || p2[k] == lettersc[l])
            {
                p2[k] = values[l];
                break;
            }
            else
            {
                continue;
            }
        }
    }

    // Calculate points of each
    // P1
    int x1 = 0;
    for (int j1 = 0; j1 < n1; j1++)
    {
        x1 = x1 + p1[j1];
    }

    // P2
    int x2 = 0;
    for (int k1 = 0; k1 < n2; k1++)
    {
        x2 = x2 + p2[k1];
    }

    // Declaring winner
    if (x1 > x2)
    {
        printf("Player 1 wins!");
        return 0;
    }
    if (x1 == x2)
    {
        printf("Tie!\n");
        return 0;
    }
    else if (x1 < x2)
    {
        printf("Player 2 wins!");
        return 0;
    }
}
