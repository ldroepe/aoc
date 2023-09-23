#include <cmath>
#include <fstream>
#include <iostream>

static const std::string input = "../day2.in";
constexpr unsigned char elf_adjustment = '@'; // shift {A, B, C} -> {1, 2, 3}
constexpr unsigned char mine_adjustment = 'W'; // shift {X, Y, Z} -> {1, 2, 3}
constexpr unsigned char game_adjustment = 'X'; // shift {X, Y, Z} -> {0, 1, 2}
constexpr unsigned char result_multiplier = 3;

/* 
 * Part 1
 * A = X = Rock = 1
 * B = Y = Paper = 2
 * C = Z = Scissors = 3
 *
 * Win
 * Paper (2) > Rock (1) --> 2-1 = 1
 * Scissors (3) > Paper (2) --> 3-2 = 1
 * Rock (1) > Scissors (3) --> 1-3 = -2
 *
 * Lose
 * Rock (1) < Paper (2) --> 1-2 = -1
 * Paper (2) < Scissors (3) --> 2-3 = -1
 * Scissors (3) < Rock (1) --> 3-1 = 2
 *
 * Loss = 0
 * Draw = 3
 * Win = 6
 */

#ifdef PART_ONE_SOLUTION
int calculate_game_multiplier(unsigned char elf, unsigned char mine)
{
    const int d = mine - elf;
    if(std::abs(d) == 2)
        return d / -2; // -2 --> 1, 2 --> -1
    return d;
}

int calculate_sum(unsigned char elf, unsigned char mine)
{
    int total = 0;
    const unsigned char elf_val = (elf - elf_adjustment);
    const unsigned char mine_val = (mine - mine_adjustment);

    //std::cout << "e: " << +elf_val << ", m: " << +mine_val << ", ";

    total += mine_val;

    const int k = calculate_game_multiplier(elf_val, mine_val);
    const int game_bonus = (result_multiplier + (result_multiplier * k));
    //std::cout << "gb: " << +game_bonus << '\n';

    total += game_bonus;

    return total;
}

#else

 /*
 * Part 2
 * A = Rock, X = Lose
 * B = Paper, Y = Draw
 * C = Scissors, Z = Win
 *
 * Win
 * Rock (0) --> Paper (1)
 * Paper (1) --> Scissors (2)
 * Scissors (2) --> Rock (0)
 * ==> Modulus addiiton
 *
 * Lose
 * Rock (0) --> Scissors (2)
 * Paper (1) --> Rock (0)
 * Scissors (2) --> Paper (1)
 * ==> Modulus subtraction
 *
 * Lose (0) --> +2 = 0
 * Draw (1) --> +0 = 3
 * Win  (2) --> +1 = 6
 */
int calculate_sum(unsigned char elf, unsigned char outcome)
{
    int total = 0;

    const unsigned char elf_val = elf - elf_adjustment - 1; // shift to {0, 1, 2}
    const unsigned char game_val = outcome - game_adjustment;
    total += result_multiplier * game_val;

    const unsigned char d = (game_val + 2) % result_multiplier;
    const int mine_val = ((elf_val + d) % result_multiplier) + 1;
    total += mine_val;
    
    return total;
}

#endif

int calculate_strategy_total(const std::string& filename)
{
    int strategy_total = 0;
    std::ifstream inFile(filename);
    unsigned char elf;
    while(inFile >> elf)
    {
        unsigned char other;
        inFile >> other;
        strategy_total += calculate_sum(elf, other);
    }

    return strategy_total;
}

int main()
{
    const int strategy_total = calculate_strategy_total(input);
    std::cout << "Strategy total: " <<  strategy_total << '\n';
    return 0;
}
