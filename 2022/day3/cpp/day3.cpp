#include <array>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <unordered_set>

static const std::string test_input = R"(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)";

static const std::string input_file = "../day3.in";

/*
 * What to subtract from each of the characters to get their priorities
 * a = 1, b = 2, c = 3, ... , A = 27, B = 28, C = 29, ...
 * 'a' - 'b' = 1, 'A' - '&' = 27.
 * Intended usage is: priority_adjustment[char < 'a']
 * Assuming valid input (which should not be done in practice), we'll
 * either have uppercase or lowercase letters, meaning that anything under 'a'
 * is uppercase, and should be adjusted by '&'
 * This scheme means that we can avoid a branch in our addition loop
 */
constexpr std::array<unsigned char, 2> priority_adjustment = {'`', '&'};

template <typename Container>
class unordered_inserter
{
private:
    Container& c;
public:
    
    // modeled after std::back_insert_iterator
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    explicit unordered_inserter(Container& c) : c(c) {}
    unordered_inserter& operator++() { return *this; }
    unordered_inserter& operator*() { return *this; }
    unordered_inserter& operator=(typename Container::value_type v) { c.insert(std::move(v)); return *this; }
};

template <typename Container>
unordered_inserter<Container> make_unordered_inserter(Container& c)
{
    return unordered_inserter<Container>(c);
}

auto find_duplicate(const std::string& line)
{
    std::unordered_set<unsigned char> first_compartment;
    const auto d = std::distance(std::cbegin(line), std::cend(line)) / 2;
    const auto m = std::cbegin(line) + d;
    
    std::copy(std::cbegin(line), m, make_unordered_inserter(first_compartment));
    
    const auto in_first_compartment = [&](const auto c) { 
        return first_compartment.find(c) != std::end(first_compartment); 
    };

    return std::find_if(m, std::cend(line), in_first_compartment);
}

int calculate_priority(std::istream& in)
{
    int total = 0;
    std::string line;
    while(std::getline(in, line))
    {
        const auto dit = find_duplicate(line);
        const unsigned char dupe = *dit;
        //std::cout << "dupe: " << dupe;
        const unsigned char add = dupe - priority_adjustment[dupe < 'a'];
        //std::cout << " adding: " << +add << '\n';
        
        total += add;
    }
    
    return total;
}

int main()
{
    //std::ifstream in{test_input};
    std::ifstream in{input_file};
    const int total_priority = calculate_priority(in);
    std::cout << "Total priority: " << total_priority << '\n';
}
