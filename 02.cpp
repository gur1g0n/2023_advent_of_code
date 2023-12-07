#include "ParserHelper.h"
#include <fmt/core.h>
#include <range/v3/algorithm.hpp>
#include <string>


//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

//https://stackoverflow.com/questions/30073839/c-extract-number-from-the-middle-of-a-string
std::string first_numberstring(std::string const &str) {
    char const *digits = "0123456789";
    std::size_t const n = str.find_first_of(digits);
    if (n != std::string::npos) {
        std::size_t const m = str.find_first_not_of(digits, n);
        return str.substr(n, m != std::string::npos ? m - n : m);
    }
    return {};
}


u_int64_t second_solution(const std::vector<std::string> &strings) {
    u_int64_t result = 0;
    std::vector<std::tuple<int, int, int>> squares(strings.size(), {0, 0, 0});

    for (unsigned int i = 0; i < strings.size(); i++) {
        auto line = split(strings[i], ":");
        auto sets = split(line.at(1), ";");
        for (const std::string &pick: sets) {
            auto colors = split(pick, ",");
            for (const std::string &col: colors) {
                int num = std::stoi(first_numberstring(col));
                if (col.find("red") != std::string::npos && get<0>(squares[i]) < num)
                    get<0>(squares[i]) = num;
                if (col.find("green") != std::string::npos && get<1>(squares[i]) < num)
                    get<1>(squares[i]) = num;
                if (col.find("blue") != std::string::npos && get<2>(squares[i]) < num)
                    get<2>(squares[i]) = num;
            }
        }
    }
    for (auto x: squares) {
        result += get<0>(x) * get<1>(x) * get<2>(x);
    }

    return result;
}

u_int64_t first_solution(std::vector<std::string> strings) {

    u_int64_t result = 0;
    std::vector<bool> valid(strings.size(), true);

    for (unsigned int i = 0; i < strings.size(); i++) {
        auto line = split(strings[i], ":");
        auto sets = split(line.at(1), ";");
        for (const std::string &pick: sets) {
            auto colors = split(pick, ",");
            for (const std::string &col: colors) {
                int num = std::stoi(first_numberstring(col));
                if (col.find("red") != std::string::npos && num > 12)
                    valid[i] = false;
                if (col.find("green") != std::string::npos && num > 13)
                    valid[i] = false;
                if (col.find("blue") != std::string::npos && num > 14)
                    valid[i] = false;
            }
        }
        if (valid[i]) {
            result += i + 1;
        }
    }
    return result;
}

int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/02.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
