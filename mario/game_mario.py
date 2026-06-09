height = input("Height: ")

while not (height.isnumeric()):
    height = input("Height: ")

height = int(height)

while height < 1 or height > 8:
    height = int(input("Height: "))

for i in range(height):
    print(" " * ((height - 1) - i), end="")
    print("#" * (i + 1), end="  ")
    print("#" * (i + 1))
