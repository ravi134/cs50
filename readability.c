#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Declaring functions
double count_letters(string text);
double count_words(string text);
double count_sentences(string text);
double coleman_liau_index(double l, double w, double s);
int grade(double i);

int main(void)
{
    string text = get_string("Text: ");

    double l = count_letters(text);
    printf("Letters: %f\n", l);

    double w = count_words(text);
    printf("Words: %f\n", w);

    double s = count_sentences(text);
    printf("Sentences: %f\n", s);

    double i = coleman_liau_index(l, w, s);
    printf("Index: %f\n", i);

    grade(i);

}
// Counts the number of letters in a string provided by the user
double count_letters(string text)
{
    double l = 0;

    for (int index = 0, length = strlen(text); index < length; index++)
    {
        if (isalpha(text[index]) != 0)
        {
            l++;
        }
    }
    return l;
}

// Counts the number of words in a string provided by the user
double count_words(string text)
{
    double w = 1;

    for (int index = 0, length = strlen(text); index < length; index++)
    {
        if (isspace(text[index]) != 0)
        {
            w++;
        }
       if (ispunct(text[index]) != 0 && (isspace(text[index - 1]) != 0) && (isspace(text[index + 1]) != 0))
       {
           w--;
       }
    }
    return w;
}

// Counts the number of sentences in a string provided by the user
double count_sentences(string text)
{
    double s = 0;

    for (int index = 0, length = strlen(text); index <= length; index++)
    {
        if (text[index] == '.' || text[index] == '?' || text[index] == '!')
        {
            s++;
        }
    }
    return s;
}

// Calculates the grade level based on the Coleman-Liau Index
double coleman_liau_index(double l, double w, double s)
{
    double avglet = ((l * 100) / w);
    printf("%f\n", avglet);
    double avgsent = ((s * 100) / w);
    printf("%f\n", avgsent);
    double i = ((0.0588 * avglet) - (0.296 * avgsent)) - 15.8;
    return i;
}

// Determines the grade reading level of a given text
int grade(double i)
{
    int g = round(i);
    if (g <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (g >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", g);
    }
    return g;
}