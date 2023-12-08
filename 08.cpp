#include "ParserHelper.h"
#include <fmt/core.h>
#include <iostream>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <typeinfo>
#include <utility>


auto splitString(std::string_view sv, std::string_view sep) {
    auto parts = ranges::views::split(sv, sep);
    auto partsVec = ranges::to<std::vector<std::string>>(parts);
    return partsVec;
}
int64_t get_distance(std::string cur,std::unordered_map<std::string, std::pair<std::string, std::string>> graph,std::string dirs){
    std::int64_t i = 0;
    std::size_t len = dirs.length();

    while (true) {

        bool left = dirs[i % len] == 'L';
        if (left) {
            cur = graph[cur].first;
        } else {
            cur = graph[cur].second;
        }
        i++;

        if (cur.back()=='Z')
            return i;

    }
}
u_int64_t second_solution(std::vector<std::string> strings) {

    std::string dirs = strings[0];
    std::unordered_map<std::string, std::pair<std::string, std::string>> graph;
    std::vector<std::string> nodes;

    for (std::size_t i = 2; i < strings.size(); i++) {
        strings[i].erase(std::remove_if(strings[i].begin(), strings[i].end(), [](char c) {
                             return std::isspace(c) || c == '(' || c == ')';
                         }),
                         strings[i].end());
        auto node = splitString(strings[i], "=");
        auto lr = splitString(node[1], ",");
        graph[node[0]] = {lr[0], lr[1]};
        if(node[0].back() == 'A')
            nodes.push_back(node[0]);
    }

    std::vector<int64_t> distances;
    distances.reserve(nodes.size());
    for(const auto& n:nodes) {
        distances.push_back(get_distance(n, graph, dirs));
    }

    int64_t res = 1;
    for (auto n : distances) {
        res = std::lcm(res, n);
    }
    return res;
}





u_int64_t first_solution(std::vector<std::string> strings) {

    std::string dirs = strings[0];
    std::size_t len = dirs.length();


    std::unordered_map<std::string, std::pair<std::string, std::string>> graph;


    for (std::size_t i = 2; i < strings.size(); i++) {
        strings[i].erase(std::remove_if(strings[i].begin(), strings[i].end(), [](char c) {
                             return std::isspace(c) || c == '(' || c == ')';
                         }),
                         strings[i].end());
        auto node = splitString(strings[i], "=");
        auto lr = splitString(node[1], ",");
        graph[node[0]] = {lr[0], lr[1]};
    }

    std::size_t i = 0;

    std::string cur = "AAA";

    while (true) {

        bool left = dirs[i % len] == 'L';
        if (left) {
            cur = graph[cur].first;
        } else {
            cur = graph[cur].second;
        }
        i++;
        if (cur == "ZZZ")
            return i;

    }

}

int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/08.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
