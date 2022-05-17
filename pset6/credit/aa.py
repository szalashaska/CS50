from cs50 import get_string
from cs50 import get_int

# Prompt user for number

while True:
    num = get_int("Number: ")
    # check for positive value
    if num > 0:
        break

# Determine single digits using string
digits = []
num = str(num)
numbers_of_digits = len(num)

print(num[2])