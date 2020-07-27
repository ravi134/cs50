from cs50 import SQL
from sys import argv, exit

db = SQL("sqlite:///students.db")
house = argv[1]

if len(argv) != 2:
    print("Please specify the file")
    exit(1)

rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", house)

for row in rows:
    first = row["first"]
    middle = row["middle"]
    last = row["last"]
    birth = row["birth"]
    print(f"{first} {middle + ' ' if middle else ''} {last} born {birth}")