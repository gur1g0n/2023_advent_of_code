#include "ParserHelper.h"
#include <fmt/core.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

int64_t get_prev_element(std::vector<int64_t> v){
    if(ranges::all_of(v,[](auto i){return i==0;})){
        return v.front();
    }
    v = ranges::views::zip(v, ranges::views::drop(v, 1)) | ranges::views::transform([](auto a){return a.second-a.first;}) | ranges::to_vector;

    return v.front() - get_prev_element(v);
}

u_int64_t second_solution(const std::vector<std::string> &strings) {
    std::vector<int64_t> nums;
    for(const auto& s:strings) {
        auto v = ParserHelper::parseIntsFromString(s);
        v.insert(v.begin(), v.front() - get_prev_element(v));
        nums.push_back(v.front());
    }

    return ranges::fold_left(nums,0,std::plus{});
}


int64_t get_next_element(std::vector<int64_t> v){
    if(ranges::all_of(v,[](auto i){return i==0;})){
        return v.front();
    }
    v = ranges::views::zip(v, ranges::views::drop(v, 1)) | ranges::views::transform([](auto a){return a.second-a.first;}) | ranges::to_vector;

    return v.back() + get_next_element(v);
}

u_int64_t first_solution(const std::vector<std::string>& strings) {
    std::vector<int64_t> nums;
    for(const auto& s:strings) {
        auto v = ParserHelper::parseIntsFromString(s);
        v.push_back(v.back() + get_next_element(v));
        nums.push_back(v.back());
    }

    return ranges::fold_left(nums,0,std::plus{});
}

int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/09.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
