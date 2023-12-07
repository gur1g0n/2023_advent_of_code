#include "ParserHelper.h"
#include <fmt/core.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

struct map_entry {
    int64_t dest_start;
    int64_t src_start;
    int64_t length;
};

struct seed_range {
    int64_t start;
    int64_t end;
};

struct Map {
    std::vector<map_entry> conversion_maps;

    int64_t map_to(int64_t num) {
        for (auto m: conversion_maps) {
            if (num >= m.src_start && num < (m.src_start + m.length)) {
                return m.dest_start + num - m.src_start;
            }
        }
        return num;
    }

    std::vector<seed_range> map_to(std::vector<seed_range> ranges) {
        std::vector<seed_range> output;

        while (!ranges.empty()) {
            auto range = ranges.back();
            ranges.pop_back();
            bool mapped = false;
            for (auto map: conversion_maps) {
                int64_t x1 = range.start;
                int64_t x2 = range.end;
                int64_t y1 = map.src_start;
                int64_t y2 = map.src_start + map.length - 1;
                int64_t offset = map.dest_start - map.src_start;
                if (x1 <= y2 && y1 <= x2) {
                    mapped = true;
                    if (x1 < y1)
                        ranges.push_back({x1, y1 - 1});
                    output.push_back({std::max(x1, y1) + offset, std::min(x2, y2) + offset});
                    if (x2 > y2)
                        ranges.push_back({y2 + 1, x2});
                }
            }
            if (not mapped)
                output.push_back(range);
        }

        return output;
    }
};


int64_t second_solution(const std::string &s) {
    std::vector<int64_t> nums = ParserHelper::parseIntsFromString(s.substr(7, s.find('\n')));
    std::vector<std::vector<seed_range>> seeds;


    for (int i = 0; i < nums.size(); i += 2) {
        std::vector<seed_range> v{{nums[i], nums[i] + nums[i + 1] - 1}};
        seeds.push_back(v);
    }

    std::vector<Map> maps;
    maps.resize(7);

    auto maps_strings = ParserHelper::parseStrsFromString(s.substr(s.find("seed-to-soil")), "\n\n");

    for (std::size_t i = 0; i < maps_strings.size(); i++) {
        auto map = ParserHelper::parseStrsFromString(maps_strings[i].substr(maps_strings[i].find('\n') + 1), "\n");
        for (const auto &m: map) {
            auto map_num = ParserHelper::parseIntsFromString(m);
            maps.at(i).conversion_maps.push_back({map_num[0], map_num[1], map_num[2]});
        }
    }

    for (Map m: maps) {
        for (std::vector<seed_range> &seed: seeds) {
            seed = m.map_to(seed);
        }
    }

    return ranges::min(seeds | ranges::views::join | ranges::views::transform([](seed_range n) { return n.start; }));
}


int64_t first_solution(const std::string &s) {
    std::vector<int64_t> seeds;
    seeds = ParserHelper::parseIntsFromString(s.substr(7, s.find('\n')));

    std::vector<Map> maps;
    maps.resize(7);

    auto maps_strings = ParserHelper::parseStrsFromString(s.substr(s.find("seed-to-soil")), "\n\n");

    for (std::size_t i = 0; i < maps_strings.size(); i++) {
        auto map = ParserHelper::parseStrsFromString(maps_strings[i].substr(maps_strings[i].find('\n') + 1), "\n");
        for (const auto &m: map) {
            auto map_num = ParserHelper::parseIntsFromString(m);
            maps.at(i).conversion_maps.push_back({map_num[0], map_num[1], map_num[2]});
        }
    }


    for (Map m: maps) {
        for (int64_t &seed: seeds) {
            seed = m.map_to(seed);
        }
    }
    return ranges::min(seeds);
}

int main() {
    auto strings = ParserHelper::readStringFromFile("../Input/05.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
