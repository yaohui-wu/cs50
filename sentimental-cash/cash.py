from cs50 import get_float


def main():
    change = get_change()
    pennies = calculate_pennies(change)
    quarters = calculate_quarters(pennies)
    pennies -= quarters * 25
    dimes = calculate_dimes(pennies)
    pennies -= dimes * 10
    nickels = calculate_nickels(pennies)
    pennies -= nickels * 5
    coins = int(quarters + dimes + nickels + pennies)
    print(coins)


def get_change():
    change = get_float('Change owed: ')

    while change < 0:
        change = get_float('Change owed: ')
    
    return change


def calculate_pennies(change):
    pennies = change * 100

    return pennies


def calculate_quarters(cents):
    quarters = cents // 25

    return quarters


def calculate_dimes(cents):
    dimes = cents // 10

    return dimes


def calculate_nickels(cents):
    nickels = cents // 5

    return nickels


if __name__ == '__main__':
    main()