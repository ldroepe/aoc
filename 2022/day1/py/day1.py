#! /usr/bin/python3

import heapq

__aoc_year__ = 2022
__aoc_day__ = 1
__author__ = 'Luke Roepe'

# part 1 implementation
def find_most_calories(inFile):
    
    current = 0
    most_calories = 0

    for line in inFile:
        if line == '\n':
            most_calories = max(most_calories, current)
            current = 0
        else:
            current += int(line.rstrip())

    return most_calories

# part 2 implementation
def collect_all_calorie_counts(inFile):
    
    calorie_counts = []
    current = 0

    for line in inFile:
        if line == '\n':
            calorie_counts.append(current)
            current = 0
        else:
            current += int(line.rstrip())

    calorie_counts.append(current)
    return calorie_counts

if __name__ == '__main__':

    filename = '../day1.in'
    n = 3

    with open(filename, 'r') as inFile:
        #most_calories = find_most_calories(inFile)
        #print(f'Most Calories: {most_calories}')
        calorie_counts = collect_all_calorie_counts(inFile)
        max_n_calories = heapq.nlargest(n, calorie_counts)
        print(f'Max {n} calories: {sum(max_n_calories)}')
