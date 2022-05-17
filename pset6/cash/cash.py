from cs50 import get_float

change = -1

# Prompt user for input
while change <= 0:
    change = get_float("Change owed: ")

# Use largest coins possible and count coins

coins = 0
cents = round(change * 100)

# start counting
while cents > 0:
    # count 25 cent coins
    if cents >= 25:
        cents = cents - 25
    # coint 10 cent coins
    elif cents < 25 and cents >= 10:
        cents = cents - 10
    # count 5 cent coins
    elif cents < 10 and cents >= 5:
        cents = cents - 5
    # count 1 cent coins
    elif cents < 5 and cents >= 1:
        cents = cents - 1
    # keep count
    coins += 1
# Print the number of coins
print(coins)
