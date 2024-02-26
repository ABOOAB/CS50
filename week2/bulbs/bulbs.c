#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;
void conv(int num);

void print_bulb(int bit);

int main(void)
{
    // convert string to decimal number
    // array of number not character
    string mes = get_string("Message: ");
    int len = strlen(mes);
    int num[len];
    for (int i = 0; i < len ; i++)
    {
        num[i] = mes[i];

        conv(num[i]);
        printf("\n");
    }
}

// convert and print function
void conv(int num)
{
    // define a new arry to carry bits
    int bits[BITS_IN_BYTE] = {0}  ;

    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        //convert to binary from decimal
        if (num % 2 == 0)
        {
            num /= 2;
            bits[i] = 0 ;
        }
        else
        {
            num = (num - 1) / 2 ;
            bits[i] = 1 ;
        }
    }
    // printing bits
    for (int i = 0; i < BITS_IN_BYTE ; i++)
    {
        // calling printing function
        print_bulb(bits[BITS_IN_BYTE - i - 1]);

    }
}

//this is the function to print these special shapes
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
