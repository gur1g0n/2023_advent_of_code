#include "ParserHelper.h"
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

struct race {
    int64_t time;
    int64_t record;
};

u_int64_t second_solution(std::vector<std::string> strings) {
    u_int64_t result = 0;
    std::vector<race> races;

    strings.at(0).erase(remove_if(strings.at(0).begin(), strings.at(0).end(), isspace), strings.at(0).end());
    strings.at(1).erase(remove_if(strings.at(1).begin(), strings.at(1).end(), isspace), strings.at(1).end());

    auto time = std::stol(strings.at(0).substr(5));
    auto record = std::stol(strings.at(1).substr(9));


    for (u_int64_t i = 1; i < time; i++) {
        auto distance = (time - i) * i;
        if (distance > record) {
            result++;
        }
    }

    return result;
}


u_int64_t first_solution(std::vector<std::string> strings) {
    u_int64_t result = 1;
    std::vector<race> races;

    auto a = ParserHelper::parseIntsFromString(strings.at(0).substr(6));
    auto b = ParserHelper::parseIntsFromString(strings.at(1).substr(10));

    for (int i = 0; i < a.size(); i++) {
        races.push_back({a.at(i), b.at(i)});
    }


    for (race r: races) {
        u_int64_t count = 0;

        for (int i = 1; i < r.time; i++) {
            auto distance = (r.time - i) * i;
            if (distance > r.record)
                count++;
        }
        result *= count;
    }

    return result;
}

int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/06.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
