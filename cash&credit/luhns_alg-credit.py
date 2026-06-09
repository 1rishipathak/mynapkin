import sys

number = input("Enter your credit card number: ")

if len(number) < 13 or len(number) > 16:
    print("INVALID", end="\n")
    sys.exit(0)

# Implementing LUHN's algorithm
digits1 = []

for i in range(len(number) - 2, -1, -2):
    digit = int(number[i]) * 2
    if digit > 9:
        d1 = int(digit / 10)
        d2 = int(digit % 10)
        digits1.append(d1)
        digits1.append(d2)
    else:
        digits1.append(digit)

sum1 = sum(digits1)

digits2 = []

for i in range(len(number) - 1, -1, -2):
    digits2.append(int(number[i]))

sum2 = sum(digits2)

sumT = sum1 + sum2

if not (sumT % 10 == 0):
    print("INVALID", end="\n")
    sys.exit(0)

    # Card Validated #

# Determining BANK
# Calculating first two digits

n = int(int(number) / (10**(len(number) - 2)))

# Calculating first digit

m = int(int(number) / (10**(len(number) - 1)))

# Assigning BANK

if n in [34, 37]:
    bank = "AMEX"
elif n in range(55, 50, -1):
    bank = "MASTERCARD"
elif m == 4:
    bank = "VISA"
else:
    print("INVALID", end="\n")

# Printing Output
print(bank, end="\n")
