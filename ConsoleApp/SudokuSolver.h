#pragma once

#include <utility>
#include <set>
#include <array>
#include <string>

class SudokuSolver
{
    struct Cell
    {
        int solution{};
        std::set<int> candidates{ 1,2,3,4,5,6,7,8,9 };
    };

public:
    SudokuSolver(const std::string& unsolved);

    std::string to_string();

    std::set<int> in_square(unsigned int ln, unsigned int col);

    std::set<int> other_destination(unsigned int ln, unsigned int col);

    std::set<int> ruled_out(unsigned int ln, unsigned int col);

    bool solve();

    bool complete();

private:
    void read(const std::string& initial);

    
    using Line = std::array<Cell, 9>;
    std::array<Line, 9> s_;

};
