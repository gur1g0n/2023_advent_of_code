#include "ParserHelper.h"
#include <fmt/core.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>


bool is_symbol(char c) {
    return (not isdigit(c)) && (c != '.');
}

//https://www.geeksforgeeks.org/find-all-adjacent-elements-of-given-element-in-a-2d-array-or-matrix/
std::vector<std::tuple<int, int>> getAdjacent(std::vector<std::vector<std::tuple<int, int>>> &arr, int i, int j) {
    int n = arr.size();
    int m = arr[0].size();

    std::vector<std::tuple<int, int>> v;

    for (int dx = (i > 0 ? -1 : 0); dx <= (i < n -1 ? 1 : 0); ++dx) {
        for (int dy = (j > 0 ? -1 : 0); dy <= (j < m -1 ? 1 : 0); ++dy) {
            if (dx != 0 || dy != 0) {
                v.push_back(arr[i + dx][j + dy]);
            }
        }
    }

    // Returning the vector array
    return v;
}

u_int64_t second_solution(const std::vector<std::string> &grid) {

    std::size_t n_rows = grid.size();
    std::size_t n_columns = grid.at(0).size();

    std::vector<std::vector<std::tuple<int, int>>> numbers;
    numbers.resize(n_rows);
    for (auto &row: numbers) {
        row.resize(n_columns);
    }
    int id = 1;

    u_int64_t result = 0;
    for (std::size_t row = 0; row < n_rows; row++) {
        for (std::size_t col = 0; col < n_columns; col++) {
            if ( isdigit(grid.at(row).at(col))) {
                std::size_t length = 0;
                int num = std::stoi(grid.at(row).substr(col), &length);
                for(std::size_t i = 0;i<length;i++){
                    numbers.at(row).at(col + i) = {num, id};
                }
                id++;
                col += length;
            }
        }
    }

    for (std::size_t row = 0; row < n_rows; row++) {
        for (std::size_t col = 0; col < n_columns; col++) {
            if (grid.at(row).at(col) == '*') {
                std::vector<std::tuple<int, int>> adj = getAdjacent(numbers, row, col);
                auto unique_gears = adj
                                    |ranges::views::filter([](std::tuple<int,int>t){return get<1>(t)!=0;})
                                    |ranges::views::unique([](std::tuple<int, int> t, std::tuple<int, int> s) { return get<1>(t) == get<1>(s); });
                if(ranges::distance(unique_gears) == 2) {
                    result+= ranges::fold_left(
                                unique_gears
                                    | ranges::views::transform([](std::tuple<int, int> t) { return get<0>(t); })
                            , 1
                            , std::multiplies{});
                }
            }
        }
    }

    return result;
}


u_int64_t first_solution(const std::vector<std::string> &grid) {


    std::size_t n_rows = grid.size();
    std::size_t n_columns = grid.at(0).size();

    u_int64_t result = 0;
    for (std::size_t row = 0; row < n_rows; row++) {
        for (std::size_t col = 0; col < n_columns; col++) {
            if ( isdigit(grid.at(row).at(col))) {
                std::size_t length = 0;
                int num = std::stoi(grid.at(row).substr(col), &length);
                bool valid = false;
                for (std::size_t row_test{(row == 0) ? 0 : row - 1}; row_test <= std::min(row + 1, grid.size() - 1); ++row_test) {
                    for (std::size_t col_test{(col == 0) ? 0 : col - 1}; col_test <= std::min(col + length, grid[row].size() - 1); ++col_test) {
                        if (is_symbol(grid[row_test][col_test])) {
                            valid = true;
                        }
                    }
                }
                if (valid) {
                    result += num;
                }
                col += length;
            }
        }

    }
    return result;
}

int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/03.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
