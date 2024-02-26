#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt hight from user

    int h;
    do
    {
        h = get_int(" Height : ");
    }
    while (h < 1 || h > 8);

    // print grid

    for (int i = 0; i < h; i++)
    {
        // loop for printing spaces

        for (int j = 0; j < h - i - 1; j++)
        {
            printf(" ");
        }
        // loop for printing hases
        for (int j = h - i; j <= h; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
