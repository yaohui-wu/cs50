import re


def main():
    card_num = input('Number: ')
    card = get_card(card_num)
    print(card)


def get_card(card_num):
    """Check the card number and return whether it is a valid
    American Express, MasterCard, Visa, or an invalid card number."""
    valid_format = False
    # American Express uses 15-digit numbers,
    # MasterCard uses 16-digit numbers,
    # and Visa uses 13- and 16-digit numbers.
    # American Express numbers start with 34 or 37.
    # MasterCard numbers start with 51, 52, 53, 54, or 55.
    # Visa numbers start with 4.
    brands = {
        'AMEX': r'^3[47]\d{13}$',
        'MASTERCARD': r'^5[1-5]\d{14}$',
        'VISA': r'^4(\d{12}|\d{15})$'
    }

    for brand in brands:
        if re.match(brands[brand], card_num):
            card = brand
            valid_format = True
    
    if not valid_format:
        return 'INVALID'

    # Luhn's Algorithm.
    checksum = 0
    card_num = int(card_num)

    while card_num > 0:
        odd_digit = card_num % 10
        checksum += odd_digit
        card_num //= 10

        even_digit = card_num % 10 * 2

        if even_digit >= 10:
            checksum += even_digit // 10 + even_digit % 10
        else:
            checksum += even_digit
        
        card_num //= 10
    
    if checksum % 10 == 0:
        return card
    else:
        return 'INVALID'


if __name__ == '__main__':
    main()