from cs50 import SQL
from sys import argv, exit
import csv

db = SQL("sqlite:///students.db")

def splitName(full_name):
    names = full_name.split()
    return names if len(names) >= 3 else [names[0], None, names[1]]

if len(argv) != 2:
    print("Please specify the file")
    exit(1)

file = argv[1]

with open(file) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        names = splitName(row["name"])
        db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", names[0], names[1], names[2], row["house"], row["birth"])