#include "ParserHelper.h"
#include <fmt/core.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>


bool is_symbol(char c) {
    return (not isdigit(c)) && (c != '.');
}

bool valid_index(int row, int col, int rows, int cols) {
    return not(row < 0 || col < 0 || row >= rows || col >= cols);
}

bool is_part(const std::vector<std::vector<char>> &grid, std::size_t num_begin, std::size_t num_end, std::size_t row) {
    bool is_part = false;
    std::size_t n_rows = grid.size();
    std::size_t n_columns = grid.at(0).size();

    for (std::size_t col = num_begin; col < num_end; col++) {
        if (valid_index(row - 1, col - 1, n_rows, n_columns))
            if (is_symbol(grid.at(row - 1).at(col - 1)))
                is_part = true;
        if (valid_index(row - 1, col, n_rows, n_columns))
            if (is_symbol(grid.at(row - 1).at(col)))
                is_part = true;
        if (valid_index(row - 1, col + 1, n_rows, n_columns))
            if (is_symbol(grid.at(row - 1).at(col + 1)))
                is_part = true;
        if (valid_index(row, col - 1, n_rows, n_columns))
            if (is_symbol(grid.at(row).at(col - 1)))
                is_part = true;
        if (valid_index(row, col + 1, n_rows, n_columns))
            if (is_symbol(grid.at(row).at(col + 1)))
                is_part = true;
        if (valid_index(row + 1, col - 1, n_rows, n_columns))
            if (is_symbol(grid.at(row + 1).at(col - 1)))
                is_part = true;
        if (valid_index(row + 1, col, n_rows, n_columns))
            if (is_symbol(grid.at(row + 1).at(col)))
                is_part = true;
        if (valid_index(row + 1, col + 1, n_rows, n_columns))
            if (is_symbol(grid.at(row + 1).at(col + 1)))
                is_part = true;
    }
    return is_part;
}

//https://www.geeksforgeeks.org/find-all-adjacent-elements-of-given-element-in-a-2d-array-or-matrix/
std::vector<std::tuple<int, int>> getAdjacent(std::vector<std::vector<std::tuple<int, int>>> &arr, int i, int j) {
    // Size of given 2d array
    int n = arr.size();
    int m = arr[0].size();

    // Initialising a vector array where
    // adjacent elements will be stored
    std::vector<std::tuple<int, int>> v;

    // Checking for adjacent elements
    // and adding them to array

    // Deviation of row that gets adjusted
    // according to the provided position
    for (int dx = (i > 0 ? -1 : 0); dx <= (i < n ? 1 : 0); ++dx) {
        // Deviation of the column that
        // gets adjusted according to
        // the provided position
        for (int dy = (j > 0 ? -1 : 0); dy <= (j < m ? 1 : 0); ++dy) {
            if (dx != 0 || dy != 0) {
                v.push_back(arr[i + dx][j + dy]);
            }
        }
    }

    // Returning the vector array
    return v;
}

u_int64_t second_solution(const std::vector<std::vector<char>> &grid) {
    std::size_t n_rows = grid.size();
    std::size_t n_columns = grid.at(0).size();

    std::vector<std::vector<std::tuple<int, int>>> numbers;
    numbers.resize(n_rows);
    for (auto &row: numbers) {
        row.resize(n_columns);
    }

    std::size_t num_begin = 0;
    std::size_t num_end = 0;
    bool same_num = false;
    int power = 1;
    int num = 0;
    int result = 0;
    int id = 0;

    for (std::size_t row = 0; row < n_rows; row++) {
        for (std::size_t col = 0; col < n_columns; col++) {
            if (auto c = grid.at(row).at(col); isdigit(c)) {
                if (not same_num)
                    num_begin = col;
                num += power * (c - '0');
                power *= 10;
                same_num = true;
            } else {
                if (same_num) {
                    num_end = col;
                    for (std::size_t col_temp = num_begin; col_temp < num_end; col_temp++) {
                        numbers.at(row).at(col_temp) = {num, id};
                    }
                    id++;
                }
                power = 1;
                same_num = false;
                num = 0;
            }
        }
        if (same_num) {
            num_end = n_columns;
            for (std::size_t col_temp = num_begin; col_temp < num_end; col_temp++) {
                numbers.at(row).at(col_temp) = {num, id};
            }
            id++;
        }
        power = 1;
        same_num = false;
        num = 0;
    }

    for (std::size_t row = 0; row < n_rows; row++) {
        for (std::size_t col = 0; col < n_columns; col++) {
            if (grid.at(row).at(col) == '*') {
                std::vector<std::tuple<int, int>> adj = getAdjacent(numbers, row, col);
                auto unique_gears = adj
                                    |ranges::views::unique([](std::tuple<int, int> t, std::tuple<int, int> s) { return get<1>(t) == get<1>(s); })
                                    |ranges::views::filter([](std::tuple<int,int>t){return get<1>(t)!=0;});
                if (ranges::distance(unique_gears) == 2) {
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


u_int64_t first_solution(const std::vector<std::vector<char>> &grid) {

    std::size_t n_rows = grid.size();
    std::size_t n_columns = grid.at(0).size();

    std::size_t num_begin = 0;
    std::size_t num_end = 0;
    bool same_num = false;
    int power = 1;
    int num = 0;
    int result = 0;

    for (std::size_t row = 0; row < n_rows; row++) {
        for (std::size_t col = 0; col < n_columns; col++) {
            if (auto c = grid.at(row).at(col); isdigit(c)) {
                if (not same_num)
                    num_begin = col;
                num += power * (c - '0');
                power *= 10;
                same_num = true;
            } else {
                if (same_num) {
                    num_end = col;
                    if (is_part(grid, num_begin, num_end, row)) {
                        result += num;
                    }
                }
                power = 1;
                same_num = false;
                num = 0;
            }
        }
        if (same_num) {
            num_end = n_columns;
            if (is_part(grid, num_begin, num_end, row)) {
                result += num;
            }
        }
        power = 1;
        same_num = false;
        num = 0;
    }
    return result;
}

int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/03.txt");
    std::vector<std::vector<char>> grid;
    grid.reserve(strings.size());
    for (std::string s: strings) {
        grid.emplace_back(s.rbegin(), s.rend());
    }

    fmt::print("Solution 1: {}\n", first_solution(grid));
    fmt::print("Solution 2: {}\n", second_solution(grid));

    return 0;
}
