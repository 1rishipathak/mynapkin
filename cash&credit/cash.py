try:
    num = float(input("Change owed: $"))
except ValueError:
    num = float(input("Change owed: $"))

while num < 0:
    try:
        num = float(input("Change owed: $"))
    except ValueError:
        num = float(input("Change owed: $"))


change = 100 * num

# Calculate number of quarters
qtr = int(change / 25)

# Calculate number of dimes
dme = int((change - (qtr*25)) / 10)

# Calculate number of nickels
nic = int((change - (qtr*25) - (dme*10)) / 5)

# Calculate number of pennies
pny = int((change - (qtr*25) - (dme*10) - (nic*5)) / 1)

# Output the total number of coins
coins = qtr + dme + nic + pny

print(coins)
