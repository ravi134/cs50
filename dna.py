from csv import reader, DictReader
from sys import argv

if len(argv) < 3:
    print("Usage Error: specify sequence and database please")
    exit()

# Get sequence from file
with open(argv[2]) as dnaFile:
    dnaReader = reader(dnaFile)
    for row in dnaReader:
        dnalist = row

dna = dnalist[0]
sequences = {}

# Put sequence into list
with open(argv[1]) as pplFile:
    ppl = reader(pplFile)
    for row in ppl:
        dnaSequences = row
        dnaSequences.pop(0)
        break

# Copy list to dict
for i in dnaSequences:
    sequences[i] = 1

# Count STR's
for key in sequences:
    l = len(key)
    tMax = 0
    tmp = 0
    for i in range(len(dna)):
        while tmp > 0:
            tmp -= 1
            continue
        if dna[i: i + l] == key:
            while dna[i - l: i] == dna[i: i + l]:
                tmp += 1
                i += l
            if tmp > tMax:
                tMax = tmp

    # longest seq
    sequences[key] += tMax

# Check for match
with open(argv[1], newline='') as peoplefile:
    people = DictReader(peoplefile)
    for person in people:
        match = 0
        for dna in sequences:
            if sequences[dna] == int(person[dna]):
                match += 1
        if match == len(sequences):
            print(person['name'])
            exit()
    print("No match")