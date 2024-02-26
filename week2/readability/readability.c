#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

int calc_grade(int le, int wo, int se);
void grade(int index);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //prompt string from the user
    string text = get_string("Text: ");

    //calculate number of letters
    int le = count_letters(text);


    //calculate number of words
    int wo = count_words(text);


    //calculate number of sentences
    int se = count_sentences(text);

    //calculate the grade
    int index = calc_grade(le, wo, se);

    //print the grade
    grade(index);

}

// calculate the grade

int calc_grade(int le, int wo, int se)
{
    float L = le / (float)wo * 100;
    float S = se / (float)wo * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8 ;
    return round(index) ;
}

int count_letters(string text)
{
    int letnum = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letnum ++ ;
        }
        i ++;
    }
    return letnum;

}

// count words function
int count_words(string text)
{
    int wornum = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (text[i] == ' ')
        {
            wornum ++ ;
        }
        i ++ ;
    }
    return wornum + 1;
}

// count sentences function
int count_sentences(string text)
{
    int sennum = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sennum ++ ;
        }
        i ++;
    }
    return sennum;

}

// print grade function

void grade(int index)
{
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 16 && index >= 1)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Before Grade 1\n");
    }
}