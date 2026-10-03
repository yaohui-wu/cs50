#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string substitution_cipher(string s, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");

        return 1;
    }

    string key = argv[1];

    int key_length = strlen(key);
    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");

        return 1;
    }

    for (int i = 0; i < key_length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");

            return 1;
        }

        for (int j = i + 1; j < key_length; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");

                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");
    string ciphertext = substitution_cipher(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

string substitution_cipher(string s, string key)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (isupper(s[i]))
        {
            int index = s[i] - 'A';
            s[i] = toupper(key[index]);
        }
        else if (islower(s[i]))
        {
            int index = s[i] - 'a';
            s[i] = tolower(key[index]);
        }
    }

    return s;
}