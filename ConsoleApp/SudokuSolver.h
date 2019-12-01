#pragma once

#include <utility>
#include <set>
#include <string>

class SudokuSolver
{
    using Cell = std::pair<int, std::set<int>>;

public:
    SudokuSolver(const std::string& unsolved);

    std::string to_string();

    std::set<int> in_square(unsigned int ln, unsigned int col);

    std::set<int> other_destination(unsigned int ln, unsigned int col);

    std::set<int> ruled_out(unsigned int ln, unsigned int col);

    bool solve();

private:
    void read(const std::string& initial);

    Cell s_[9][9];
};
