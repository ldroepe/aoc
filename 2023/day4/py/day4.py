#!/usr/bin/python3

from collections import defaultdict

#puzzle_input = '../day4_test.in'
#puzzle_input = '../day4_partial.in'
puzzle_input = '../day4.in'

def count_winning_numbers(winning_numbers, hand):
    # int(True) = 1, int(False) = 0
    return sum((int(n in winning_numbers) for n in hand))

def count_hand(winning_numbers, hand):
    '''
    Checks whether any of the numbers in hand are present in winning_numbers
    Returns the total point value of the hand
    :param winning_numbers: a set of winning numbers
    :param hand: the numbers which are present on your scratchcard
    '''
    
    num_matches = count_winning_numbers(winning_numbers, hand)
    hand_total = int(2 ** (num_matches - 1)) # 0 matches --> 0
    return hand_total

def parse_input_card(card):
    '''
    Parse the given card (line of input) and return a set of winning numbers,
    and a list of numbers in your hand.
    :param card: line of input from the input file
    :returns (winning_numbers, hand):
    '''

    _, all_numbers = card.split(': ')
    winning_numbers, hand = all_numbers.split(' | ')
    winning_numbers = set(int(wn) for wn in winning_numbers.split() if wn != '')
    hand = [int(n) for n in hand.split(' ') if n != '']

    return (winning_numbers, hand)

def part_one(filename):
    '''
    Calculate the sum of points in a given pile of cards
    :param filename: input file
    '''
    with open(filename, 'r') as cards:
        calc_card_total = lambda c: count_hand(*parse_input_card(c.strip()))
        pile_total = sum((calc_card_total(c) for c in cards))
        print(f'{pile_total=}')

def part_two(filename):
    '''
    Calculate the number of scratchcards won from a given pile of cards
    If you have 4 winning numbers in Card 1, that means that you win a copy
    of the NEXT 4 cards (i.e. Cards 2, 3, 4, 5)
    :param filename: input file
    '''

    copies = defaultdict(int)

    with open(filename, 'r') as cards:
        for card_number, card in enumerate(cards, start=1):

            (winning_numbers, hand) = parse_input_card(card)
            num_winners = count_winning_numbers(winning_numbers, hand)
            for i in range(card_number + 1, card_number + num_winners + 1):
                copies[i] += (1 + copies[card_number])

    total_scratchcards = sum(copies.values()) + (card_number)
    print(f'{total_scratchcards=}')

def main(filename):
    part_one(filename)
    part_two(filename)

if __name__ == '__main__':
    main(puzzle_input)
