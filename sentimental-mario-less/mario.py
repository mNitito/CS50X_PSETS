from cs50 import get_int
while True:
    height = get_int("Enter the height:")
    if height < 1 or height > 8:
        print("Enter a height between 1 and 8:")
    else:
        break

for row in range(height):
    for space in range(height - row - 1):
        print(" ", end='')
    for hash in range(row + 1):
        print("#", end='')
    print()
