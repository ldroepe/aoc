
import functools

COLORS = ('red', 'green', 'blue')

class Bag:
    def __init__(self, **kwargs):
        # default values
        for color in COLORS:
            setattr(self, color, 0)

        for key, val in kwargs.items():
            setattr(self, key, val)
    def __str__(self):
        return '{}({!r})'.format(self.__class__.__name__, ' '.join('{}={}'.format(k, v) for k, v in self.__dict__.items()))
    def __repr__(self):
        return self.__str__()

    def power(self):
        return functools.reduce(lambda a, x: a*x, vars(self).values())

def read_hands(game):
    
    bag = Bag()

    for hands in game.split('; '):
        for showing in hands.split(', '):
            number, color = showing.split(' ')
            prev_max = getattr(bag, color)
            setattr(bag, color, max(int(number), prev_max))

    return bag

def read_game(line):
    _, game = line.strip().split(': ')
    return read_hands(game)

def find_possible_games(max_condition, bags):

    condition_values = vars(max_condition).values()
    for i, bag in enumerate(bags):
        game_values = vars(bag).values()
        if all(gv <= cv for gv, cv in zip(game_values, condition_values)):
            yield i+1

def main(elf_input):
    
    max_condition = Bag(red=12, green=13, blue=14)
    bags = [read_game(line) for line in open(elf_input)]

    # Part 1 Solution
    possible_game_indices = (i for i in find_possible_games(max_condition, bags))
    game_id_total = sum(possible_game_indices)
    print(f'Game ID total: {game_id_total}')

    # Part 2 Solution
    power_sum = sum((b.power() for b in bags))
    print(power_sum)

if __name__ == '__main__':
    main('../day2.in')
    #main('./day2_test.in')
