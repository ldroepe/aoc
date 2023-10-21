#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>

static const std::string input = "../day1.in";

template <typename It>
void printc(const std::string& pref, It first, It last)
{

    std::cout << pref << ": ";
    while(first != last)
    {
        std::cout << *first << ' ';
        ++first;
    }

    std::cout << '\n';
}

template <typename Container>
void printc(const std::string& pref, const Container& c) { printc(pref, std::cbegin(c), std::cend(c)); }

#ifdef PART_ONE_SOLUTION
int count_calories(std::istream& in)
{
    int total = 0;
    for(std::string line; std::getline(in, line) && line != "";)
    {
        // wildly dangerous in untrusted environments -- very brittle
        total += std::stoi(line);
    }
    
    return total;
}

int find_most_calories()
{
    int max = 0;

    std::ifstream inFile(input);
    while(inFile)
    {
        const int calorie_count = count_calories(inFile);
        max = std::max(max, calorie_count);
    }

    return max;
}

#else

constexpr int n = 3;

template <typename Container, typename Comp = std::less<typename Container::value_type> >
class heap_back_inserter
{
private:
    Container& c;
    Comp comp;

    using reference = heap_back_inserter<Container, Comp>&;

public:
    explicit heap_back_inserter(Container& container, Comp compare=Comp()):
        c(container), comp(compare) {}
    reference operator++() { return *this; }
    reference operator*() { return *this; }
    reference operator=(typename Container::value_type v) {
        c.push_back(std::move(v));
        std::push_heap(std::begin(c), std::end(c), comp);
        return *this;
    }

};

template <typename Container, typename Comp = std::less<typename Container::value_type> >
heap_back_inserter<Container, Comp> make_heap_inserter(Container& c, Comp comp = Comp())
{
    return heap_back_inserter<Container, Comp>(c, comp);
}

int count_calories(std::istream& in)
{
    int total = 0;
    for(std::string line; std::getline(in, line) && line != "";)
        total += std::stoi(line); // wildly dangerous for unverified data
    
    return total;
}

/* n = input size (number of lines in day1.in
 * m = number of largest calories to count
 *
 * std::make_heap = O(m) ==> O(1)
 * std::push_heap = O(log(m)) ==> O(1)
 * std::pop_heap = O(log(m)) ==> O(1)
 * std::pop_back = O(1)
 *
 * Therefore, using a min heap has allowed this procedure to run in O(n) time,
 * while using constant storage
 */
std::vector<int> collect_all_calorie_counts(std::istream& in)
{
    using calorie_t = int;
    const auto comp = std::greater<calorie_t>();
    
    std::vector<calorie_t> calories;
    calories.reserve(n+1); // only storing 4 elements at most
    auto heap_inserter = make_heap_inserter(calories, comp);

    for(int i = 0; i < n; ++i)
        *heap_inserter = count_calories(in); // requires in has at least n lines

    while(in)
    {
        const calorie_t c = count_calories(in);
        *heap_inserter = c;
        std::pop_heap(std::begin(calories), std::end(calories), comp);
        calories.pop_back();
    }

    return calories;
}

#endif

int main()
{
    std::ifstream inFile(input);
    if(!inFile)
        std::cerr << "Could not open: " << input << '\n';
    
#ifdef PART_ONE_SOLUTION

    const int most_calories = find_most_calories();
    std::cout << "Most Calories: " << most_calories << '\n';

#else

    const std::vector<int> calorie_counts = collect_all_calorie_counts(inFile);

    /*
    // Complexity is (first-last)log(middle-first), and for small n, this means
    // we basically have linear time
    std::partial_sort(std::begin(calorie_counts), 
                      std::begin(calorie_counts) + n + 1, 
                      std::end(calorie_counts),
                      std::greater<>());
    */

    const int max_n_calories = 
        std::accumulate(std::cbegin(calorie_counts),
                        std::cbegin(calorie_counts) + n,
                        0);

    std::cout << "Max " << n << " calorie count: " << max_n_calories << '\n';

#endif

    return 0;
}
