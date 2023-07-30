#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size.
    int start_size;
    const int MIN_START_SIZE = 9;
    do
    {
        start_size = get_int("Start size: ");
    } while (start_size < MIN_START_SIZE);
    
    // Prompt for end size.
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    } while (end_size < start_size);
    
    // Calculate number of years until we reach threshold.
    int years = 0;
    while (start_size < end_size)
    {
        start_size += start_size / 3 - start_size / 4;
        years++;
    }
    
    // Print number of years.
    printf("Years: %d\n", years);

    return 0;
}