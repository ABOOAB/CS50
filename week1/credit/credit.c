#include <cs50.h>
#include <stdio.h>

int checksum(long number, int *cnt);
void check(long num, int cnt);

int main(void)
{
    int cnt = 0;

    //prompet for input
    long num = get_long("Number : ");

    //calculate checksum
    int val = checksum(num, &cnt);
    printf("%i\n" ,val);
    if (val % 10 == 0)
    {
        check(num, cnt);
    }
    else
    {
        printf("INVALID\n");
    }

}

void check(long num, int cnt)
{
    // sort the type of visa number and validity
    // AMX type
    if ((cnt == 15) && (num / 10000000000000 == 34 || num / 10000000000000 == 37))
    {
        printf("AMEX\n");
    }
    // MASTERCARD type
    else if ((cnt == 16) && (num / 100000000000000 == 51 || num / 100000000000000 == 52 || \
                             num / 100000000000000 == 53 || num / 100000000000000 == 54 || num / 100000000000000 == 55))
    {
        printf("MASTERCARD\n");
    }
    // VISA type
    else if ((cnt == 16) && (num / 1000000000000000 == 4))
    {
        printf("VISA\n");
    }
    else if ((cnt == 13) && (num / 1000000000000 == 4))
    {
        printf("VISA\n");
    }
    // not valid visa
    else
    {
        printf("INVALID\n");
    }


}

// this function for Luhan's algorithm

int checksum(long number, int *cnt)
{

    int digit;
    int sum = 0;
    int unprosum = 0;

    while (number)
    {
        digit = number % 10;
        number /= 10;
        *cnt = *cnt + 1 ;
        if (*cnt % 2 == 0)
        {

            digit = digit * 2;
            if (digit / 10 != 0)
            {
                digit = (digit % 10) + (digit / 10);


            }
            sum = sum + digit;

        }
        else
        {


            unprosum += digit ;
        }

    }
    int chsum = sum + unprosum ;

    return chsum;
}
