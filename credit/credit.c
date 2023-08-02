#include <cs50.h>
#include <stdio.h>

bool valid_card(long card_num);
bool valid_length(long card_num);
int length(long num);
bool checksum(long n);
string card_network(long card_num);

int main(void)
{
    // Get the card number from user input.
    long card_num = get_long("Number: ");

    /* Validate the card number and prints whether it is a valid
    American Express, MasterCard, Visa, or an invalid card number. */
    if (valid_card(card_num))
    {
        string card = card_network(card_num);
        printf("%s\n", card);
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

bool valid_card(long card_num)
{
    return valid_length(card_num) && checksum(card_num);
}

bool valid_length(long card_num)
{
    int len = length(card_num);
    /* American Express uses 15-digit numbers,
    MasterCard uses 16-digit numbers,
    and Visa uses 13- and 16-digit numbers. */

    return len == 15 || len == 16 || len == 13;
}

int length(long num)
{
    int length = 0;
    while (num > 0)
    {
        num /= 10;
        length++;
    }

    return length;
}

bool checksum(long num)
{
    int sum = 0;
    // Luhn's Algorithm.
    while (num > 0)
    {
        int digit1 = num % 10;
        sum += digit1;
        num /= 10;

        int digit2 = num % 10 * 2;
        if (digit2 >= 10)
        {
            sum += digit2 / 10 + digit2 % 10;
        }
        else
        {
            sum += digit2;
        }
        num /= 10;
    }

    return sum % 10 == 0;
}

string card_network(long card_num)
{
    string card;

    // Get the starting two digit number of the card number.
    while (card_num >= 100)
    {
        card_num /= 10;
    }

    /* American Express numbers start with 34 or 37.
    MasterCard numbers start with 51, 52, 53, 54, or 55.
    Visa numbers start with 4. */
    if (card_num == 34 || card_num == 37)
    {
        card = "AMEX";
    }
    else if (card_num >= 51 && card_num <= 55)
    {
        card = "MASTERCARD";
    }
    else if (card_num / 10 == 4)
    {
        card = "VISA";
    }
    else
    {
        card = "INVALID";
    }

    return card;
}