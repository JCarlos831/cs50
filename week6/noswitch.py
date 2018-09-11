# Logical Operators

from cs50 import get_char

# Prompt user for answer
answer = get_char("answer: ")

# Check answer
if answer == "Y" or answer == "y":
    print("yes")
elif answer == "N" or answer == "n":
    print("no")