# Integer Arithmetic

from cs50 import get_int

# prompt user for x
x = get_int("x: ")

# prompt user for y
y = get_int("y: ")

# perform arithmetic
print(f"{x} plus {y} is {x + y}")
print(f"{x} minus {y} is {x - y}")
print(f"{x} times {y} is {x * y}")
print(f"{x} truly divided by {y} is {x / y}")
print(f"{x} floor-divided by {y} is {x // y}")
print(f"remainder of {x} divided by {y} is {x % y}")