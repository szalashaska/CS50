import sys
import csv


def main():

    # Ensure proper usege
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna data.csv seqence.txt")

    # List to store persons data
    person = []

    # Read person seqences into memory from file
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            person.append(row)

    # Read the header from persons file, in order to store patterns
    with open(sys.argv[1]) as file:
        reader = csv.reader(file)
        STR = next(reader)
    print({}.for)

    # change pattern values to integer
    for line in person:
        for i in range(1, len(STR)):
            line[STR[i]] = int(line[STR[i]])

    # Read seqence from file
    with open(sys.argv[2]) as file:
        reader = csv.reader(file)
        header = next(reader)

    # Store sequence as a string
    sequence = header[0]

    # Dictionary to store counted data
    person_of_intrest = {}

    # Find patterns, count them and assign to dictionary
    for i in range(len(STR)):
        if i == 0:
            person_of_intrest[STR[i]] = "P.O.I."
        else:
            person_of_intrest[STR[i]] = count_sequence(sequence, STR[i])

    # helping variables
    sercher = 0
    namer = ""

    # Compere two dictionaries, look for perfect match and print out their name
    for line in person:
        # reset the matching count
        sercher = 0
        # keep the name of person we check
        namer = line["name"]

        for i in range(1, len(STR)):
            if line[STR[i]] == person_of_intrest[STR[i]]:
                sercher += 1

        # if we found match at all patterns we print the winner
        if sercher == len(STR) - 1:
            print(namer)
            #sys.exit(0)
    print("nice try")
    for name,data in person.items():
        if data == person_of_intrest:
            print(name)


    # In case there was no match found
    print("No match")
    sys.exit(0)


# Helpful functions:


# returns value of consecutive repeated pattern in sequence
def count_sequence(sequence, pattern):
    # counting variables
    count = 0
    final_count = -1

    # to help with keeping track of consecutive repeat
    score = 100

    # lenght of input data
    pattern_lenght = len(pattern)
    sequence_lenght = len(sequence)

    # loop over seqence, changing output word by letter
    for i in range(sequence_lenght):
        score += 1
        # finding pattern - first of consecutive
        if sequence[i:pattern_lenght + i] == pattern and score != pattern_lenght:
            score = 0
            count = 1
        # finding pattern - keep track if consecutive repeat occurs
        if sequence[i:pattern_lenght + i] == pattern and score == pattern_lenght:
            count += 1
            score = 0
        # keep track of longest consecutive repeat, update the value

        final_count = max(count, final_count)
    # return value
    return final_count


if __name__ == "__main__":
    main()