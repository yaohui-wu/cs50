from cs50 import get_int


def main():
    height = get_height()
    print_pyramid(height)


def get_height():
    height = get_int('Height: ')

    while height < 1 or height > 8:
        height = get_int('Height: ')
    
    return height


def print_pyramid(height):
    spaces = height - 1

    for i in range(1, height + 1):
        print(' ' * spaces, end='')
        print('#' * i, end='')
        spaces -= 1
        print('  ', end='')
        print('#' * i)


if __name__ == '__main__':
    main()