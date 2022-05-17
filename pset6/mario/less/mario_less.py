from cs50 import get_int

# prompt user for pyramid hight
height = -1
while height < 1 or height > 8:
    height = get_int("Height: ")

# print pyramid

for i in range(height):
    # print spaces
    for j in range(1, height - i):
        print(" ", end="")
    # print hashes
    for k in range(i + 1):
        print("#", end="")
    # go to the next row
    print()
