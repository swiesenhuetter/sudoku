#pragma once

#include <utility>
#include <set>
#include <string>

class SudokuSolver
{
    struct Cell
    {
        int first{};
		std::set<int> second{ 1,2,3,4,5,6,7,8,9 };
    };

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
