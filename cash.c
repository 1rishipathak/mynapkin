#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int amt;
    // Prompt user for the amount of change owed
    do
    {
        amt = get_int("Please enter amount of change owed: ");
    }
    while (amt < 0);
    // Calculate the amount of $0.25 to dispense
    int x = (amt / 25);
    // Calculate the amount of $0.10 to dispense
    int y = ((amt - 25 * x) / 10);
    // Calculate the amount of $0.5 to dispense
    int z = ((amt - 25 * x - 10 * y) / 5);
    // Calculate the amount of $0.1 to dispense
    int k = ((amt - 25 * x - 10 * y - 5 * z) / 1);

    // Calculate the output
    int o = (x + y + z + k);
    // Print output
    printf("%i\n", o);
}
