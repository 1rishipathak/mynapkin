import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py [database.csv] [sequence.txt]")
        sys.exit(0)

    # Read database file into a variable
    data = []
    with open(sys.argv[1], "r") as ifile:
        ireader = csv.DictReader(ifile)
        for row in ireader:
            data.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as ofile:
        seq = ofile.read()

    # Find longest match of each STR in DNA sequence
    lengths = []
    for str in ireader.fieldnames[1:]:
        lengths.append({str: longest_match(seq, str)})

    # Check database for matching profiles

    name = "No Match"
    req = len(lengths)

    for row in data:
        counts = 0
        for row1 in lengths:
            for smp, num in row.items():
                for rep, val in row1.items():
                    if (rep == smp):
                        if (int(num) == (val)):
                            counts += 1

        if counts == req:
            name = row["name"]

    print(name)


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

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
