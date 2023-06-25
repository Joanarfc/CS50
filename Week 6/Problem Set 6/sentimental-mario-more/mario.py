height = 0

# Prompt the user about the height of the pyramids
while height < 1 or height > 8:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Invalid input. Please enter a valid height (integer).")

# Loop to print out the pyramids
for i in range(1, height + 1):
    # Print out left pyramid
    for j in range(1, height - i + 1):
        print(" ", end="")
    for j in range(1, i+1):
        print("#", end="")

    # Print out middle between pyramids, which is only 1 space
    print("  ", end="")

    # Print out right pyramid
    for j in range(1, i + 1):
        print("#", end="")
    print()