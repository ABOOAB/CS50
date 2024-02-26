#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

bool check(string argv);

void encrypt(string text, string key);
int main(int argc, string argv[])
{

    //check validity of comand line

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        printf("not good argv\n");
        return 1;
    }
    //check the existing of the key
    else if ((!check(argv[1])) || (strlen(argv[1]) != 26))
    {
        printf("%lu\n", strlen(argv[1]));
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        string text = get_string("plaintext: ");
        printf("ciphertext: ");
        // function to encrypt text
        encrypt(text, argv[1]);
        printf("\n");

    }





    //encrypt plaintext

    //print the ciphertext

}

bool check(string argv)
{
    bool flag = true;
    int n = strlen(argv);
    // check if there is no repetition
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n ; j++) // remmeber that checking is not so good at all
        {
            if (toupper(argv[i]) == toupper(argv[j]))
            {
                flag = false;
                break;
            }

        }
        if (!flag)
        {
            break
        };
        // check if all string are characters
    }
    for (int i = 0; i < n ; i++)
    {
        if (!isalpha(argv[i]))
        {
            flag = false;
            break;
        }
    }
    return flag;
}

// function to encrypt the text
void encrypt(string text, string key)
{
    for (int i = 0, n = strlen(text) ; i < n ; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                text[i] = key[(int)text[i] - 65];
            }
            else
            {
                text[i] = key[(int)text[i] - 97];
            }
        }
        printf("%c", text[i]);
    }
}