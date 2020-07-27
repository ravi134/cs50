from cs50 import get_int

height = 0
h = 1
while True:
        height = get_int("Height: ")
        if 0 < height < 9:
            break

for i in range(height):
    s = height - h
    print(" "*s + "#"*h + "  " + "#"*h)
    h += 1