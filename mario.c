#include <cs50.h>
#include <stdio.h>

void print_row(int bricks, int height);
int main(void)
{
    // Prompting user for height of the pyramid
    int height;
    do
    {
        height = get_int("What is the height of the pyramid?: \n");
    }
    while (height < 1 || height >= 9);

    // Printing the pyramid
    for (int i = 0; i < height; i++)
    {
        print_row(i, height);
    }
}

// Prototyping function to print a row with as many bricks as given
void print_row(int bricks, int height)
{

    {
        int x = (height - bricks - 1);
        int y = bricks + 1;

        // Printing 1st set of spaces
        {
            for (int a = 0; a < x; a++)
            {
                printf(" ");
            }
        }
        // Printing 1st set of hashes
        {
            for (int b = 0; b < y; b++)
            {
                printf("#");
            }
        }
        // Printing 2nd set of spaces (of constant number)
        {
            printf("  ");
        }
        // Printing 2nd set of hashesh
        {

            for (int c = 0; c < y; c++)
            {
                printf("#");
            }
        }

        printf("\n");
    }
}
