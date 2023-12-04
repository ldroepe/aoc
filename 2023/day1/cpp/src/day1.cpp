#include <string>
#include <fstream>
#include <sstream>
#include <numeric>
#include <iostream>
#include <iterator>
#include <algorithm>

constexpr bool is_digit(unsigned char c) { return c >= '0' && c <= '9'; }

static const std::string test_input = R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)";

int get_calibration_score(const std::string& line)
{
    // Precondition: line contains at least one digit
    std::ostringstream combined_digits;
    std::copy_if(std::cbegin(line), std::cend(line),
                 std::ostream_iterator<unsigned char>(combined_digits),
                 is_digit);
    const std::string all_combined_digits = combined_digits.str();
    combined_digits.str("");

    combined_digits << all_combined_digits.front();
    combined_digits << all_combined_digits.back();

    return std::stoi(combined_digits.str());
}

int main()
{
    
    using text_iterator = std::istream_iterator<std::string>;
    //std::istringstream inFile(test_input);
    std::ifstream inFile("../day1.in");

    const int result = std::transform_reduce(
        text_iterator(inFile),
        text_iterator(),
        0,
        std::plus<>(),
        [&](const std::string& line) { return get_calibration_score(line); }
    );
        
    std::cout << "result: " << result << '\n';
}
