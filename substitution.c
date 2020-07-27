#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Get key
    if (argc !=  2)
    {
        printf("Usage: ./substitution Key\n");
        return 1;
    }

    // Validate key
    if (strlen(argv[1]) != 26)
    {
        printf("Your key must contain 26 characters\n");
        return 1;
    }

    string userString = argv[1];
    char duplicateKey[26];

    bool repeat[26];
    for (int i = 0; i < 26; i++)
        repeat[i] = false;

    for (int i = 0; i < 26; i++)
    {
        if (isalpha(userString[i]))
        {
            if (isupper(userString[i]))
            {
                if (repeat[userString[i] - 'A'] == true)
                {
                    printf("Your key may not contain duplicate characters. %c repeats", userString[i]);
                    return 1;
                }
                else
                {
                    repeat[userString[i] - 'A'] = true;
                    duplicateKey[i] = userString[i] - 'A';
                }
            }
            else
            {
                if (repeat[userString[i] - 'a'] == true)
                {
                    printf("Your key may not contain duplicate characters. %c repeats", userString[i]);
                    return 1;
                }
                else
                {
                    repeat[userString[i] - 'a'] = true;
                    duplicateKey[i] = userString[i] - 'a';
                }
            }
        }
        else
        {
            printf("Your key must contain only alphabets, %c at spot %i is not an alphabet\n", userString[i], i);
            return 1;
        }
    }

    // Get plaintext
    string plainText = get_string("plaintext: ");
    string cipherText = plainText;

    // Encipher
    for(int i = 0; i < strlen(plainText); i++)
    {
        if (isalpha(plainText[i]))
        {
            if (isupper(plainText[i]))
                cipherText[i] = (duplicateKey[plainText[i] - 'A'] + 'A');
            else
                cipherText[i] = (duplicateKey[plainText[i] - 'a'] + 'a');
        }
        else
            cipherText[i] = plainText[i];
    }

    // Print ciphertext
    printf("ciphertext: %s\n", cipherText);

    return 0;
}