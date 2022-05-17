# Simulate a sports tournament

import csv
import sys
import random


    # Ensure correct usage
if len(sys.argv) != 2:
    sys.exit("Usage: python tournament.py FILENAME")

teams = []
# TODO: Read teams into memory from file
with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    for row in reader:

            # print("{}".format(row['team']))
        row["rating"] = int(row["rating"])
        teams.append(row)


print("{} and {}".format(teams[1]["team"], teams[1]["rating"]))

table = []

table = teams


print("{} and {}".format(table[1]["team"], table[1]["rating"]))

print("{}".format(len(table)))
print("this is my new input")
print("{}".format(table[8]))
