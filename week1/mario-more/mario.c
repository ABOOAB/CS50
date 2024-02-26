#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt height from the user
    int h;
    do
    {
        h = get_int("Height : ");
    }
    while (h < 1 || h > 8);

    // print grid
    for (int i = 0; i < h; i++)
    {
        // printing first grid
        for (int j = 0; j < h - i - 1; j++)
        {
            printf(" ");
        }

        for (int j = h - i - 1; j < h; j++)
        {
            printf("#");
        }
        printf("  ");
        // printing second grid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
