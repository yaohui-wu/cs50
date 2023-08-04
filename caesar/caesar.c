#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
string caesar_cipher(string s, int key);
char rotate(char c, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }

    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext:  ");
    string ciphertext = caesar_cipher(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

bool only_digits(string s)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}

string caesar_cipher(string s, int key)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        s[i] = rotate(s[i], key);
    }

    return s;
}

char rotate(char c, int key)
{
    if (isupper(c))
    {
        c = (c - 'A' + key) % 26 + 'A';
    }
    else if (islower(c))
    {
        c = (c - 'a' + key) % 26 + 'a';
    }

    return c;
}