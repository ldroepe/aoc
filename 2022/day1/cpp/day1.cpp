#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>

static const std::string input = "../day1.in";

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

int count_calories(std::istream& in)
{
    int total = 0;
    for(std::string line; std::getline(in, line) && line != "";)
        total += std::stoi(line); // wildly dangerous for unverified data
    
    return total;
}

template <typename OutIt>
OutIt collect_all_calorie_counts(std::istream& in, OutIt out)
{

    while(in)
        *out++ = count_calories(in);
    
    return out;
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

    constexpr int n = 3;
    std::vector<int> calorie_counts;
    collect_all_calorie_counts(inFile, std::back_inserter(calorie_counts));

    // Complexity is (first-last)log(middle-first), and for small n, this means
    // we basically have linear time
    std::partial_sort(std::begin(calorie_counts), 
                      std::begin(calorie_counts) + n + 1, 
                      std::end(calorie_counts),
                      std::greater<>());

    const int max_n_calories = 
        std::accumulate(std::cbegin(calorie_counts),
                        std::cbegin(calorie_counts) + n,
                        0);

    std::cout << "Max " << n << " calorie count: " << max_n_calories << '\n';

#endif

    return 0;
}
