from cs50 import get_float

coin = 0

# Receive input from user, making sure input is a positive integer, if not, prompt again
while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

cents = change * 100.0

# Check to see if we can use quarters
while cents >= 25:
    cents = cents - 25
    coin = coin + 1

# If we can't use quarters, use dimes
while cents >= 10:
    cents = cents - 10
    coin = coin + 1

# If we can't use dimes, use nickels
while cents >= 5:
    cents = cents - 5
    coin = coin + 1

# If we can't use nickels, use pennies
while cents >= 1:
    cents = cents - 1
    coin = coin + 1

print(coin)