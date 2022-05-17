from cs50 import get_string
from cs50 import get_int
import sys

# Prompt user for number

while True:
    num = get_int("Number: ")
    # check for positive value
    if num > 0:
        break
# Determine single digits useing modulo %, but why do that if we can use strings!
'''
interseting show of math thinking:
digits = []
numbers_of_digits = len(str(num))
for i in range(numbers_of_digits):

    ten = 10 ** (i + 1)
    if i == 0:
        digits.append((num % ten) / (10 ** i))
    else:
        digits.append((num % ten - digits[i - 1]) / (10 ** i))
    print(int(digits[i]))
'''
# Since we are using strings, we can proceed with other operations
num = str(num)
numbers_of_digits = len(num)

# Why bother doing all the checking, if the number is invalid? We consider only 13, 15 and 16 digits
if numbers_of_digits < 13 or numbers_of_digits == 14 or numbers_of_digits > 16:
    print("INVALID")
    sys.exit(1)

# Indexes for calculation
second_to_last_digit_index = len(num) - 2
last_digit_index = len(num) - 1

# Multiply by 2 and asign every other digit to list "other..."
other_digits = []
for i in range(second_to_last_digit_index, -1, -2):
    other_digits.append(int(num[i]) * 2)

# Add digits from list "other...", includ "12 = 1 + 2" cases
sum_of_other_digits = 0
for k in range(len(other_digits)):
    if other_digits[k] >= 10:
        other_digits[k] = other_digits[k] % 10 + 1
    sum_of_other_digits += other_digits[k]

# Add up digits that were skipped previously
sum_of_rest = 0
for j in range(last_digit_index, -1, -2):
    sum_of_rest += int(num[j])

# Add up previously calculated sums and check if card is valid
control_sum = sum_of_other_digits + sum_of_rest
check_control_sum = control_sum % 10
if check_control_sum != 0:
    print("INVALID")
    sys.exit(2)

# Time has come. Card is now valid, lets assign company

# Mastercard
if numbers_of_digits == 16 and num[0] == "5" and int(num[1]) > 0 and int(num[1]) <= 5:
    print("MASTERCARD")
    sys.exit(0)

# American Express
if numbers_of_digits == 15 and num[0] == "3" or num[1] == 4 or num[1] == 7:
    print("AMEX")
    sys.exit(0)

# VISA
if numbers_of_digits == 13 or numbers_of_digits == 16 and num[0] == "4":
    print("VISA")
    sys.exit(0)

# for all the cases that are not included
else:
    print("INVALID")
    sys.exit(0)