#include "ParserHelper.h"
#include <fmt/core.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>


u_int64_t findNum(std::string s, bool reverse) {
    const static std::unordered_map<std::string, int> numbers = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}};
    const static std::unordered_map<std::string, int> numbers_reverse = {{"eno", 1}, {"owt", 2}, {"eerht", 3}, {"ruof", 4}, {"evif", 5}, {"xis", 6}, {"neves", 7}, {"thgie", 8}, {"enin", 9}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}};
    std::unordered_map<std::string, int> map;
    size_t start_pos;
    size_t min = std::string::npos;
    u_int64_t minNum;

    if (reverse) {
        std::reverse(s.begin(), s.end());
        map = numbers_reverse;
    } else {
        map = numbers;
    }

    for (const auto &[num_s, num_i]: map) {
        start_pos = s.find(num_s);
        if (start_pos < min) {
            min = start_pos;
            minNum = map.at(num_s);
        }
    }
    return minNum;
}

u_int64_t second_solution(const std::vector<std::string> &strings) {
    u_int64_t result = 0;
    for (const std::string &s: strings) {
        result += findNum(s, false) * 10 + findNum(s, true);
    }
    return result;
}


u_int64_t first_solution(std::vector<std::string> strings) {
    return ranges::fold_left(strings | ranges::views::transform([](std::string &s) { return ((*ranges::find_if(s, isdigit)) - '0') * 10 +
                                                                                            (*ranges::find_if(s | ranges::views::reverse, isdigit)) - '0'; }), 0, std::plus{});
}

int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/01.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
