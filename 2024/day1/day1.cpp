
#include <cmath>
#include <vector>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <utility>
#include <numeric>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <unordered_map>

// Each assignment of this output iterator assigns the value to one of the two
// underlying output iterators, but alternates between which iterator it assigns
// to after successive calls to operator=
template <typename LeftOutIt, typename RightOutIt>
class fork_inserter
{
public:
    using left = LeftOutIt;
    using right = RightOutIt;
private:
    LeftOutIt left_;
    RightOutIt right_;
    bool use_left_ = true;
public:
    explicit fork_inserter(LeftOutIt l, RightOutIt r):
        left_(std::move(l)),
        right_(std::move(r)) {}

    fork_inserter& operator*() { return *this; }

    fork_inserter& operator++()
    {
        if(use_left_) ++left_;
        else ++right_;
        use_left_ ^= true;
        return *this;
    }

    template <typename T>
    fork_inserter& operator=(const T& value)
    {
        if(use_left_) *left_ = value;
        else *right_ = value;
        return *this;
    }
};


// Zip together two underlying iterators, so that each dereference operation
// on this iterator produces a pair, containing elements of the underlying
// iterators
template <typename LeftIt, typename RightIt>
class zip_iterator
{
public:
    using value_type = 
        std::pair<
            typename std::iterator_traits<LeftIt>::value_type,
            typename std::iterator_traits<RightIt>::value_type>;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
private:
    LeftIt left_first_;
    RightIt right_first_;
public:
    explicit zip_iterator():
        left_first_(),
        right_first_() {}
    explicit zip_iterator(
        LeftIt left_first, 
        RightIt right_first):
            left_first_(left_first),
            right_first_(right_first) {}

    value_type operator*() { return std::make_pair(*left_first_, *right_first_); }
    zip_iterator& operator++() { ++left_first_; ++right_first_; return *this; }
    zip_iterator operator++(int)
    {
        zip_iterator ret = *this;
        ++*this;
        return ret;
    }

    friend bool operator==(zip_iterator lhs, zip_iterator rhs)
    {
        return (
            *lhs.left_first_ == *rhs.left_first_
            && *lhs.right_first_ == *rhs.right_first_
        );
    }

    friend bool operator!=(zip_iterator lhs, zip_iterator rhs)
    {
        return !(lhs == rhs);
    }

    zip_iterator& operator+=(difference_type n)
    {
        std::advance(left_first_, n);
        std::advance(right_first_, n);
        return *this;
    }

    friend zip_iterator operator+(zip_iterator lhs, difference_type n)
    {
        return lhs += n;
    }
};

template <typename L, typename R>
fork_inserter<L, R>
make_fork_inserter(L l, R r) { return fork_inserter<L, R>(l, r); }

using location_id = int;
using list_t = std::vector<location_id>;
using locations_t = std::pair<list_t, list_t>;

locations_t read_input(const std::string& filename)
{
    list_t left;
    list_t right;
    fork_inserter split_locations(std::back_inserter(left), std::back_inserter(right));
    std::ifstream locations(filename, std::ios_base::in);
    std::copy(
        std::istream_iterator<int>(locations),
        std::istream_iterator<int>(),
        split_locations
    );

    return std::make_pair(left, right);
}

template <typename LeftIt, typename RightIt>
location_id solve_part_one(
    LeftIt left_first,
    LeftIt left_last,
    RightIt right_first,
    RightIt right_last)
{
    std::sort(left_first, left_last);
    std::sort(right_first, right_last);

    return std::accumulate(
        zip_iterator<LeftIt, RightIt>(left_first, right_first),
        zip_iterator<LeftIt, RightIt>(left_last, right_last),
        0,
        [](location_id acc, const auto p) { 
            return (acc + std::abs(p.first - p.second));
        }
    );
}

template <typename LeftIt, typename RightIt>
location_id solve_part_two(
    LeftIt left_first,
    LeftIt left_last,
    RightIt right_first,
    RightIt right_last)
{
    
    using frequency_map = std::unordered_map<location_id, int>;
    frequency_map loc_freqs;
    while(right_first != right_last)
        loc_freqs[*right_first++]++;

    return std::accumulate(
        left_first,
        left_last,
        0,
        [&loc_freqs](const auto acc, const auto x) {
            return acc + (x*loc_freqs[x]);
        }
    );
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "usage: ./day1 input\n";
        return EXIT_FAILURE;
    }

    auto [left, right] = read_input(argv[1]);
    const auto diff = solve_part_one(
        std::begin(left), std::end(left),
        std::begin(right), std::end(right)
    );
    std::cout << "Part 1 - Sum of differences: " << diff << '\n';

    const auto similarity = solve_part_two(
        std::cbegin(left), std::cend(left),
        std::cbegin(right), std::cend(right)
    );
    std::cout << "Part 2 - Similarity score: " << similarity << '\n';
    
    return EXIT_SUCCESS;
}
