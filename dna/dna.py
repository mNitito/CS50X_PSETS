import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("usgae python dna.py databases/small.csv sequences/1.txt")
        return 1

    # TODO: Read database file into a variable
    dna = []
    with open(sys.argv[1]) as file1:
        reader = csv.DictReader(file1)
        for row in reader:
            dna.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file2:
        data = file2.read()

    # TODO: Find longest match of each STR in DNA sequence
    longest_list = []
    for protien in reader.fieldnames[1:]:
        longest = longest_match(data, protien)
        longest_list.append(longest)

    # TODO: Check database for matching profiles
    if (sys.argv[1] == 'databases/small.csv'):
        longest1 = longest_list[0]
        longest2 = longest_list[1]
        longest3 = longest_list[2]
        for ROW in dna:
            name = ROW['name']
            protien1 = int(ROW['AGATC'])
            protien2 = int(ROW['AATG'])
            protien3 = int(ROW['TATC'])
            if (protien1 == longest1 and protien2 == longest2 and protien3 == longest3):
                print(name)
        if (protien1 != longest1 or protien2 != longest2 or protien3 != longest3):
            print("No match")

    elif (sys.argv[1] == 'databases/large.csv'):
        longest1 = longest_list[0]
        longest2 = longest_list[1]
        longest3 = longest_list[2]
        longest4 = longest_list[3]
        longest5 = longest_list[4]
        longest6 = longest_list[5]
        longest7 = longest_list[6]
        longest8 = longest_list[7]
        for ROW in dna:
            name = ROW['name']
            protien1 = int(ROW['AGATC'])
            protien2 = int(ROW['TTTTTTCT'])
            protien3 = int(ROW['AATG'])
            protien4 = int(ROW['TCTAG'])
            protien5 = int(ROW['GATA'])
            protien6 = int(ROW['TATC'])
            protien7 = int(ROW['GAAA'])
            protien8 = int(ROW['TCTG'])
            if (protien1 == longest1 and protien2 == longest2 and protien3 == longest3 and protien4 == longest4 and protien5 == longest5 and protien6 == longest6 and protien7 == longest7 and protien8 == longest8):
                print(name)
        if (protien1 != longest1 and protien2 != longest2 and protien3 != longest3 and protien4 != longest4 and protien5 != longest5 and protien6 != longest6 and protien7 != longest7 and protien8 != longest8):
            print("No match")


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


main()
