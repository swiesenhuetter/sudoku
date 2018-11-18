#pragma once

#include <utility>
#include <set>
#include <string>

class SudokuSolver
{
    using Cell = std::pair<int, std::set<int>>;

public:
    SudokuSolver();

    std::string to_string();

    void read(std::string initial);

    std::set<int> in_square(unsigned int ln, unsigned int col);

    std::set<int> other_destination(unsigned int ln, unsigned int col);

    std::set<int> ruled_out(unsigned int ln, unsigned int col);

    bool solve();

private:
    Cell s_[9][9];
};


