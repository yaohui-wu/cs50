import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit('Usage: python dna.py data.csv sequence.txt')

    # Read database file into a variable
    data_filename = sys.argv[1]

    with open(data_filename) as data_file:
        data = csv.DictReader(data_file)
        dna_database = list(data)
    
    # Read DNA sequence file into a variable
    sequence_filename = sys.argv[2]

    with open(sequence_filename) as sequence_file:
        sequence = sequence_file.read()

    # Find longest match of each STR in DNA sequence
    matches = {}

    for i in dna_database[0]:
        matches[i] = longest_match(sequence, i)

    # Check database for matching profiles
    matches_count = 1

    for i in range(len(dna_database)):
        for j in matches:
            if str(matches[j]) == dna_database[i][j]:
                matches_count += 1
        
        if matches_count == len(matches):
            print(dna_database[i]['name'])
            sys.exit()
        else:
            matches_count = 1

    print('No match')


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == '__main__':
    main()