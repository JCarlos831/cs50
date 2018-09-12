from cs50 import get_int

top = 1
steps = 0

# Prompt user for a positive number up to and including 23
while True:
    height = get_int("Enter height (positive number between 0 and 23): ")
    if height >= 0 and height < 24:
        break

# Build the pyramid
row = height
spaces = row - top

# Number of rows aka height
for i in range(height):

    # Print spaces
    for j in range(spaces):
        print(" ", end="")

    # Create number for steps
    steps = row - spaces

    # Decrement spaces
    spaces = spaces - 1

    # Print steps for the left side of the pyramid
    for k in range(steps):
        print("#", end="")

    # Print Gap
    print("  ", end="")

    # Print steps for the right side
    for m in range(steps):
        print("#", end="")
    print()