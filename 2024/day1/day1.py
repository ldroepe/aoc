#!/usr/bin/env python3

import sys
from collections import defaultdict

def read_input(filename):
    left = []
    right = []

    with open(filename) as inFile:
        for line in inFile:
            l, r = line.split()
            left.append(int(l))
            right.append(int(r))

    return (left, right)

def solve_part_one(left, right):

    left.sort()
    right.sort()

    distances = (abs(l-r) for l, r in zip(left, right))
    n = sum(distances)
    print(f'Part 1 - Adjacent Differences: {n}')

def build_frequency_table(l):
    
    f = defaultdict(int)
    for x in l:
        f[x]+=1
    return f

def solve_part_two(left, right):

    freqs = build_frequency_table(right)
    similarities = (x*freqs[x] for x in left)
    n = sum(similarities)
    print(f'Part 2 - Similarity Scores: {n}')

def main(filename):
    left, right = read_input(filename)
    solve_part_one(left, right)
    solve_part_two(left, right)

if __name__ == '__main__':
    main(sys.argv[1])
