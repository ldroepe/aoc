#! /usr/bin/python3

import enum

__aoc_year__ = 2022
__aoc_day__ = 2
__author = 'Luke Roepe'

filename = '../day2.in'
value_mapping = {'A': 1, 'X': 1, 'B': 2, 'Y': 2, 'C': 3, 'Z': 3}
result_multiplier = 3

class Solution(enum.Enum):
    PART_ONE = 1
    PART_TWO = 2
solve_part_number = Solution.PART_TWO

'''
Part One

A = X = Rock = 1
B = Y = Paper = 2
C = Z = Scissors = 3

Win
Paper (2) > Rock (1) --> 2-1 = 1
Scissors (3) > Paper (2) --> 3-2 = 1
Rock (1) > Scissors (3) --> 1-3 = -2

Lose
Rock (1) < Paper (2) --> 1-2 = -1
Paper (2) < Scissors (3) --> 2-3 = -1
Scissors (3) < Rock (1) --> 3-1 = 2

Loss = 0
Draw = 3
Win = 6
'''
def calculate_game_multiplier(elf, mine):
    d = mine-elf
    if abs(d) == 2:
        return d / -2
    return d

def part_one_sol(elf, mine):

    total = 0

    elf_val = value_mapping[elf]
    mine_val = value_mapping[mine]

    total += mine_val

    k = calculate_game_multiplier(elf_val, mine_val)
    total += (result_multiplier + (result_multiplier * k))

    return total

'''
Part Two
A = Rock, X = Lose
B = Paper, Y = Draw
C = Scissors, Z = Win

Win
Rock (0) --> Paper (1)
Paper (1) --> Scissors (2)
Scissors (2) --> Rock (0)
==> Modulus addiiton

Lose
Rock (0) --> Scissors (2)
Paper (1) --> Rock (0)
Scissors (2) --> Paper (1)
==> Modulus subtraction

Lose (0) --> +2 = 0
Draw (1) --> +0 = 3
Win  (2) --> +1 = 6
'''
def part_two_sol(elf, game):
    
    total = 0
    elf_val = value_mapping[elf] - 1
    game_val = value_mapping[game] - 1

    total += result_multiplier * game_val

    d = (game_val + 2) % result_multiplier
    mine_val = ((elf_val + d) % result_multiplier) + 1
    total += mine_val

    return total

def solution_fn(part):
    if part == Solution.PART_ONE:
        return part_one_sol
    elif part == Solution.PART_TWO:
        return part_two_sol
calculate_strategy = solution_fn(solve_part_number)

if __name__ == '__main__':
    
    with open(filename, 'r') as inFile:
        total = 0
        for match in inFile:
            total += calculate_strategy(*match.split())
        print(f'Strategy total: {total}')
