#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int s, e, count = 0;
    // TODO: Prompt for start size
    do
    {
        s = get_int("Start size :");
    }
    while (s < 9);

    // TODO: Prompt for end size
    do
    {
        e = get_int("End size :");
    }
    while (e < s);


//     // TODO: Calculate number of years until we reach threshold
    while (s < e)
    {
        s = s + (s / 3) - (s / 4);

        count ++;

    }
    // TODO: Print number of years
    printf("Years: %i", count);
    printf("\n");
}
