#include "ParserHelper.h"
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <range/v3/action.hpp>

auto splitString(std::string_view sv, std::string_view sep) {
    auto parts = std::views::split(sv, sep);
    auto partsVec = ranges::to<std::vector<std::string>>(parts);
    return partsVec;
}

std::vector<int> stringToIntVector(const std::string& input) {
    std::istringstream iss(input);
    return {std::istream_iterator<int>(iss), std::istream_iterator<int>()};
}

u_int64_t second_solution(const std::vector<std::string>& strings) {

    std::vector<int> copies;
    copies.resize(strings.size(),1);

    for(int i = 0; i<strings.size();i++){
        auto nums = splitString(strings[i].substr(9),"|");
        auto winning = stringToIntVector(nums[0]);
        auto actual = stringToIntVector(nums[1]);

        int count = 0;
        for(auto w :winning){
            for(auto a: actual){
                if(a==w){
                    count++;
                }
            }
        }

        for(int j = 1; j<=count;j++){
            copies[i+j] += copies[i];
        }
    }
    return ranges::fold_left(copies,0,std::plus{});
}




u_int64_t first_solution(const std::vector<std::string>& strings) {

    u_int64_t result = 0;

    std::vector<int> copies;

    copies.resize(strings.size(),1);


    for(const std::string& s:strings){
        auto nums = splitString(s.substr(9),"|");
        auto winning = stringToIntVector(nums[0]);
        auto actual = stringToIntVector(nums[1]);

        int count = 0;
        for(auto w :winning){
            for(auto a: actual){
                if(a==w){
                    count++;
                }
            }
        }

        result += count == 0 ? 0:static_cast<int>(pow(2,count-1));
    }

    return result;
}

int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/04.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
