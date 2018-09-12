from cs50 import get_string
import sys

#Get Key

# Check to see if user entered key and only two arguments
if len(sys.argv) == 2:
    # Assign second argument to key
    key = int(sys.argv[1])
else:
    # Return error message
    print("Error: Must enter a non negative integer after python caesar.py")
    sys.exit(1)

# Get plain text from user
plaintext = get_string("plaintext: ")

# Ciphered text will appear after "ciphertext:"
print("ciphertext: ", end="")

plainTextLength = len(plaintext)

# Loop through plaintext adding key to each character
for i in range (plainTextLength):
    if plaintext[i].isalpha():
        # If Alpha, check to see if character is uppercase
        if plaintext[i].isupper():
            # Convert uppercase character from ASCII to Alphabetical Index
            alphaIndexUpper = ord(plaintext[i]) + key - 65;
            #Convert from Alpha to Cipher
            cipheredUpper = alphaIndexUpper % 26 + 65;
            # Print character
            print(chr(cipheredUpper), end="")
        #If Alpha and not uppercase, character is lowercase
        else:
            # Convert lowercase character from ASCII to Alphabetical Index
            alphaIndexLower = ord(plaintext[i]) + key - 97;
            # convert from Alpha to Cipher
            cipheredLower = alphaIndexLower % 26 + 97;
            #Print character
            print(chr(cipheredLower), end="")
    # If not an Alpha character, no need to convert
    else:
        # Print character
        print(plaintext[i], end="")
print()
