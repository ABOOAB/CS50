#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

bool only_digits(string argc);
char rotate(char c, int key);
int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc == 2)
    {
        bool bol = only_digits(argv[1]);
        if (!bol)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // convert to integer
    int key = atoi(argv[1]);

    //prompt string from the user
    string text = get_string("plaintext:  ");
    //call rotating function and print ciphertext
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        printf("%c", rotate(text[i], key));
    }
    printf("\n");
    return 0;
}

//function to check if the argument is just integer
bool only_digits(string argv)
{
    bool bol;
    for (int i = 0, n = strlen(argv); i < n; i++)
    {
        bol = isdigit(argv[i]);
    }
    return bol;
}

//rotating function
char rotate(char c, int key)
{

    if (isalpha(c))
    {


        if (isupper(c))
        {
            c = c - 65;
            c = (c + key) % 26 ;
            c = c + 65;
        }
        else
        {
            c = c - 97;
            c = (c + key) % 26 ;
            c = c + 97;
        }
    }

    return c ;
}