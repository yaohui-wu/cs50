#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: ");
    int length = strlen(message);

    for (int i = 0; i < length; i++)
    {
        char c = message[i]; // A character of the message.
        int ascii = c; // ASCII code of the character.
        
        // Binary number of the ASCII code.
        int bits[BITS_IN_BYTE] = {0};
        int current_index = BITS_IN_BYTE - 1;
        while (ascii > 0)
        {
            if (ascii % 2 == 1)
            {
                bits[current_index] = 1;
            }
            ascii /= 2;
            current_index--;
        }
        
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(bits[j]);
        }

        printf("\n");
    }

    return 0;
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji.
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji.
        printf("\U0001F7E1");
    }
}