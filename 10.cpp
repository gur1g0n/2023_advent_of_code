#include "ParserHelper.h"
#include <fmt/core.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>


struct tile {
    bool up;
    bool down;
    bool left;
    bool right;
};
void match_tile(const std::vector<std::string> &strings, std::vector<std::vector<tile>> &tiles, int x, int y, int x_prev, int y_prev) {

    if (strings[x][y] == '|') {
        tiles[x][y].up = true;
        tiles[x][y].down = true;

        if (strings[x_prev][y_prev] == '|') {
            tiles[x][y] = tiles[x_prev][y_prev];
        } else if (strings[x_prev][y_prev] == '7') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].left = false;
                tiles[x][y].right = true;
            } else {
                tiles[x][y].left = true;
                tiles[x][y].right = false;
            }
        } else if (strings[x_prev][y_prev] == 'F') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].left = true;
                tiles[x][y].right = false;
            } else {
                tiles[x][y].left = false;
                tiles[x][y].right = true;
            }
        }else if (strings[x_prev][y_prev] == 'L') {
            if (tiles[x_prev][y_prev].left) {
                tiles[x][y].left = true;
                tiles[x][y].right = false;
            } else {
                tiles[x][y].left = false;
                tiles[x][y].right = true;
            }
        }else if (strings[x_prev][y_prev] == 'J') {
            if (tiles[x_prev][y_prev].right) {
                tiles[x][y].left = false;
                tiles[x][y].right = true;
            } else {
                tiles[x][y].left = true;
                tiles[x][y].right = false;
            }
        }
    } else if (strings[x][y] == '-') {
        tiles[x][y].left = true;
        tiles[x][y].right = true;
        if (strings[x_prev][y_prev] == '-') {
            tiles[x][y] = tiles[x_prev][y_prev];
        } else if (strings[x_prev][y_prev] == 'F') {
            if (tiles[x_prev][y_prev].left) {
                tiles[x][y].up = true;
                tiles[x][y].down = false;
            } else {
                tiles[x][y].up = false;
                tiles[x][y].down = true;
            }
        } else if (strings[x_prev][y_prev] == 'L') {
            if (tiles[x_prev][y_prev].left) {
                tiles[x][y].up = false;
                tiles[x][y].down = true;
            } else {
                tiles[x][y].up = true;
                tiles[x][y].down = false;
            }
        }else if (strings[x_prev][y_prev] == 'J') {
            if (tiles[x_prev][y_prev].right) {
                tiles[x][y].up = false;
                tiles[x][y].down = true;
            } else {
                tiles[x][y].up = true;
                tiles[x][y].down = false;
            }
        } else if (strings[x_prev][y_prev] == '7') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].up = true;
                tiles[x][y].down = false;
            } else {
                tiles[x][y].up = false;
                tiles[x][y].down = true;
            }
        }
    } else if (strings[x][y] == 'L') {
        tiles[x][y].up = true;
        tiles[x][y].right = true;
        if (strings[x_prev][y_prev] == '|') {
            if (tiles[x_prev][y_prev].left) {
                tiles[x][y].left = true;
                tiles[x][y].down = true;
            } else {
                tiles[x][y].left = false;
                tiles[x][y].down = false;
            }
        } else if (strings[x_prev][y_prev] == '-') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].left = false;
                tiles[x][y].down = false;
            } else {
                tiles[x][y].left = true;
                tiles[x][y].down = true;
            }

        }else if (strings[x_prev][y_prev] == '7') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].left = false;
                tiles[x][y].down = false;
            } else {
                tiles[x][y].left = true;
                tiles[x][y].down = true;
            }

        } else if (strings[x_prev][y_prev] == 'F') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].left = true;
                tiles[x][y].down = true;
            } else {
                tiles[x][y].left = false;
                tiles[x][y].down = false;
            }
        } else if (strings[x_prev][y_prev] == 'J') {
            if (tiles[x_prev][y_prev].right) {
                tiles[x][y].left = true;
                tiles[x][y].down = true;
            } else {
                tiles[x][y].left = false;
                tiles[x][y].down = false;
            }
        }
    } else if (strings[x][y] == 'J') {
        tiles[x][y].up = true;
        tiles[x][y].left = true;
        if (strings[x_prev][y_prev] == '|') {
            if (tiles[x_prev][y_prev].right) {
                tiles[x][y].right = true;
                tiles[x][y].down = true;
            } else {
                tiles[x][y].right = false;
                tiles[x][y].down = false;
            }
        } else if (strings[x_prev][y_prev] == '-') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].right = false;
                tiles[x][y].down = false;
            } else {
                tiles[x][y].right = true;
                tiles[x][y].down = true;
            }

        }else if (strings[x_prev][y_prev] == '7') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].right = true;
                tiles[x][y].down = true;
            } else {
                tiles[x][y].right = false;
                tiles[x][y].down = false;
            }
        } else if (strings[x_prev][y_prev] == 'F') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].right = false;
                tiles[x][y].down = false;
            } else {
                tiles[x][y].right = true;
                tiles[x][y].down = true;
            }
        } else if (strings[x_prev][y_prev] == 'L') {
            if (tiles[x_prev][y_prev].down) {
                tiles[x][y].right = true;
                tiles[x][y].down = true;
            } else {
                tiles[x][y].right = false;
                tiles[x][y].down = false;
            }
        }
    } else if (strings[x][y] == 'F') {
        tiles[x][y].right = true;
        tiles[x][y].down = true;
        if (strings[x_prev][y_prev] == '-') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].up = true;
                tiles[x][y].left = true;
            } else {
                tiles[x][y].up = false;
                tiles[x][y].left = false;
            }
        }else if (strings[x_prev][y_prev] == '|') {
            if (tiles[x_prev][y_prev].left) {
                tiles[x][y].up = true;
                tiles[x][y].left = true;
            } else {
                tiles[x][y].up = false;
                tiles[x][y].left = false;
            }

        } else if (strings[x_prev][y_prev] == '7') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].up = true;
                tiles[x][y].left = true;
            } else {
                tiles[x][y].up = false;
                tiles[x][y].left = false;
            }
        } else if (strings[x_prev][y_prev] == 'J') {
            if (tiles[x_prev][y_prev].right) {
                tiles[x][y].up = false;
                tiles[x][y].left = false;
            } else {
                tiles[x][y].up = true;
                tiles[x][y].left = true;
            }
        } else if (strings[x_prev][y_prev] == 'L') {
            if (tiles[x_prev][y_prev].left) {
                tiles[x][y].up = true;
                tiles[x][y].left = true;
            } else {
                tiles[x][y].up = false;
                tiles[x][y].left = false;
            }
        }
    } else if (strings[x][y] == '7') {
        tiles[x][y].left = true;
        tiles[x][y].down = true;
        if (strings[x_prev][y_prev] == '-') {
            if (tiles[x_prev][y_prev].up) {
                tiles[x][y].up = true;
                tiles[x][y].right= true;
            } else {
                tiles[x][y].up = false;
                tiles[x][y].right = false;
            }
        }else if (strings[x_prev][y_prev] == '|') {
            if (tiles[x_prev][y_prev].left) {
                tiles[x][y].up = false;
                tiles[x][y].right = false;
            } else {
                tiles[x][y].up = true;
                tiles[x][y].right = true;
            }

        }  else if (strings[x_prev][y_prev] == 'L') {
            if (tiles[x_prev][y_prev].left) {
                tiles[x][y].up = false;
                tiles[x][y].right = false;
            } else {
                tiles[x][y].up = true;
                tiles[x][y].right = true;
            }
        } else if (strings[x_prev][y_prev] == 'J') {
            if (tiles[x_prev][y_prev].right) {
                tiles[x][y].up = true;
                tiles[x][y].right = true;
            } else {
                tiles[x][y].up = false;
                tiles[x][y].right = false;
            }
        } else if (strings[x_prev][y_prev] == 'F') {
            if (tiles[x_prev][y_prev].left) {
                tiles[x][y].up = true;
                tiles[x][y].right = true;
            } else {
                tiles[x][y].up = false;
                tiles[x][y].right = false;
            }
        }
    }

}

std::pair<int, int> get_next_coords(const std::vector<std::string> &strings, int x, int y, int x_prev, int y_prev) {
    if (strings[x][y] == '|') {
        if (x > x_prev)
            return {++x, y};
        else
            return {--x, y};
    } else if (strings[x][y] == '-') {
        if (y > y_prev)
            return {x, ++y};
        else
            return {x, --y};
    } else if (strings[x][y] == 'L') {
        if (x > x_prev)
            return {x, ++y};
        else
            return {--x, y};
    } else if (strings[x][y] == 'J') {
        if (x > x_prev)
            return {x, --y};
        else
            return {--x, y};
    } else if (strings[x][y] == '7') {
        if (x < x_prev)
            return {x, --y};
        else
            return {++x, y};
    } else if (strings[x][y] == 'F') {
        if (x < x_prev)
            return {x, ++y};
        else
            return {++x, y};
    }
    throw std::runtime_error("something went wrong");
}
u_int64_t first_solution(const std::vector<std::string> &strings) {
    u_int64_t result = 1;
    std::vector<std::string> out = strings;

    for (auto &s: out) {
        for (auto &c: s) {
            c = '.';
        }
    }

    int x = 0;
    int y = 0;
    int x_prev = 0;
    int y_prev = 0;

    for (int i = 0; i < strings.size(); i++) {
        for (int j = 0; j < strings[0].length(); j++) {
            if (strings[i][j] == 'S') {
                x = i;
                y = j;
                x_prev = i;
                y_prev = j;
            }
        }
    }
    if (strings[x + 1][y] == '|' || strings[x + 1][y] == 'J' || strings[x + 1][y] == 'L') {
        x++;
    } else if (strings[x - 1][y] == '|' || strings[x - 1][y] == 'F' || strings[x - 1][y] == '7') {
        x--;
    } else if (strings[x][y + 1] == '-' || strings[x][y + 1] == '7' || strings[x][y + 1] == 'J') {
        y++;
    } else if (strings[x][y - 1] == '-' || strings[x][y - 1] == 'F' || strings[x][y - 1] == 'L') {
        y--;
    }


    do {

        if (x > x_prev) {
            out[x][y] = '|';
        } else if (x < x_prev) {
            out[x][y] = '|';
        } else if (y > y_prev) {
            out[x][y] = '-';
        } else if (y < y_prev) {
            out[x][y] = '-';
        }
        auto [a, b] = get_next_coords(strings, x, y, x_prev, y_prev);
        x_prev = x;
        y_prev = y;
        x = a;
        y = b;
        result++;
    } while (strings[x][y] != 'S');

    for (auto &a: out) {
        fmt::println("{}", a);
    }
    return result / 2;
}

u_int64_t second_solution(std::vector<std::string> &strings) {
    u_int64_t result = 0;
    std::vector<std::string> out = strings;
    std::vector<std::vector<tile>> tiles;
    tiles.resize(strings.size());
    for (auto &t: tiles) {
        t.resize(strings[0].length());
    }

    for (auto &s: out) {
        for (auto &c: s) {
            c = '.';
        }
    }

    int x = 0;
    int y = 0;
    int x_prev = 0;
    int y_prev = 0;

    for (int i = 0; i < strings.size(); i++) {
        for (int j = 0; j < strings[0].length(); j++) {
            if (strings[i][j] == 'S') {
                x = i;
                y = j;
                x_prev = i;
                y_prev = j;
            }
        }
    }
    out[x][y] = strings[x][y];
    if (strings[x + 1][y] == '|' || strings[x + 1][y] == 'J' || strings[x + 1][y] == 'L') {
        x++;
    } else if (strings[x - 1][y] == '|' || strings[x - 1][y] == 'F' || strings[x - 1][y] == '7') {
        x--;
    } else if (strings[x][y + 1] == '-' || strings[x][y + 1] == '7' || strings[x][y + 1] == 'J') {
        y++;
    } else if (strings[x][y - 1] == '-' || strings[x][y - 1] == 'F' || strings[x][y - 1] == 'L') {
        y--;
    }


    do {
        out[x][y] = strings[x][y];
        auto [a, b] = get_next_coords(strings, x, y, x_prev, y_prev);
        x_prev = x;
        y_prev = y;
        x = a;
        y = b;
    } while (strings[x][y] != 'S');

    strings[x][y] = 'L';
    out[x][y] = 'O';
    x_prev = 4;
    y_prev = out[4].find('F');
    //out[x_prev][y_prev] = 'O';
    x = x_prev;
    y = y_prev + 1;
    tiles[x_prev][y_prev].up = false;
    tiles[x_prev][y_prev].right = true;
    tiles[x_prev][y_prev].left = false;
    tiles[x_prev][y_prev].down = true;
    do {
        out[x][y] = 'O';
        match_tile(strings, tiles, x, y, x_prev, y_prev);
        auto [a, b] = get_next_coords(strings, x, y, x_prev, y_prev);
        x_prev = x;
        y_prev = y;
        x = a;
        y = b;

    } while (not(x == 4 && y == out[4].find('F')));
    out[x][y] = 'O';
    //tiles[x][y].left = false;
    for(int i=0;i<out.size();i++){
        for(int j=0;j<out[0].size();j++){
            int c = j;
            if(out[i][c]=='O')
                continue;
            while (c<out[0].size()&&out[i][c]!='O'){
                c++;
            }
            if(tiles[i][c].left){
                out[i][j] = 'I';
                result++;
            }
        }
    }

    for (auto &a: out) {
        fmt::println("{}", a);
    }
    return result;
}


int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/10.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
