// ConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>

char difficult[] =
"---" "---" "---"
"---" "--3" "-85"
"--1" "-2-" "---"

"---" "5-7" "---"
"--4" "---" "1--"
"-9-" "---" "---"

"5--" "---" "-73"
"--2" "-1-" "---"
"---" "-4-" "--9";

char typical[] =
"53-" "-7-" "---"
"6--" "195" "---"
"-98" "---" "-6-"

"8--" "-6-" "--3"
"4--" "8-3" "--1"
"7--" "-2-" "--6"

"-6-" "---" "28-"
"---" "419" "--5"
"---" "-8-" "-79";




const std::set<int> allnum = { 1,2,3,4,5,6,7,8,9 };

class SudokuSolver
{
    using Cell = std::pair<int, std::set<int>>;

public:
    SudokuSolver() {
        for (auto& line : s_)
            for (auto& cell : line)
                cell.second = allnum;
    }

    void print()
    {
        for (unsigned int c = 0; c < 81; ++c)
        {
            auto line = c / 9;
            auto col = c % 9;
            if (col == 0) std::cout << "\n";
            std::cout << s_[line][col].first << " ";
        }
        std::cout << "\n";
    }

    void read()
    {
        std::string init(difficult);
        for (unsigned int c = 0; c < 81; ++c)
        {
            auto line = c / 9;
            auto col = c % 9;

            if (init[c] != '-')
            {
                s_[line][col].first = init[c] - 48;
                s_[line][col].second.clear();
            }
            else
                s_[line][col].first = 0;
        }
    }

    std::set<int> in_square(unsigned int ln, unsigned int col)
    {
        std::set<int> result;
        int sqleft = (col / 3) * 3;
        int sqtop = (ln / 3) * 3;
        for (int qln = sqtop; qln < sqtop + 3; ++qln)
        {
            for (int qcol = sqleft; qcol < sqleft + 3; ++qcol)
            {
                if (s_[qln][qcol].first)
                {
                    result.insert(s_[qln][qcol].first);
                }
            }
        }
        return result;
    }

    std::set<int> other_destination(unsigned int ln, unsigned int col)
    {
        std::set<int> result;
        int sqleft = (col / 3) * 3;
        int sqtop = (ln / 3) * 3;
        for (int qln = sqtop; qln < sqtop + 3; ++qln)
        {
            for (int qcol = sqleft; qcol < sqleft + 3; ++qcol)
            {
                if (qln != ln || qcol != col)
                {
                    result.insert(s_[qln][qcol].second.begin(), s_[qln][qcol].second.end());
                }
            }
        }
        return result;
    }

    std::set<int> ruled_out(unsigned int ln, unsigned int col)
    {
        std::set<int> result;
        for (unsigned int c = 0; c < 9; ++c)
        {
            int hor = s_[ln][c].first;
            if (hor)
            {
                result.insert(hor);
            }
            int ver = s_[c][col].first;
            if (ver)
            {
                result.insert(ver);
            }
        }

        auto placed = in_square(ln, col);
        for (int already : placed)
        {
            result.insert(already);
        }
        return result;
    }



    void solve()
    {

        bool todo {};
        do 
        {
            todo = false;
            for (unsigned int c = 0; c < 81; ++c)
            {
                auto line = c / 9;
                auto col = c % 9;

                if (s_[line][col].first == 0)
                {
                    

                    std::set<int> remaining;
                    auto eliminate = ruled_out(line, col);
                    auto& candidates = s_[line][col].second;
                    std::set_difference(candidates.begin(),
                        candidates.end(),
                        eliminate.begin(),
                        eliminate.end(),
                        std::inserter(remaining, remaining.end()));
                    if (remaining.empty())
                    {
                        std::cout << "\n Impossible \n";
                        todo = false;
                        break;
                    }
                    else if (remaining.size() == 1)
                    {
                        s_[line][col].first = *remaining.begin();
                        s_[line][col].second.clear();
                    }
                    else
                    {
                        if (remaining.size() < s_[line][col].second.size())
                            todo = true;
                        s_[line][col].second = remaining;

                        auto alternatives = other_destination(line, col);
                        for (int candidate : remaining)
                        {
                            auto found = std::find(alternatives.begin(), alternatives.end(), candidate);
                            if (found == alternatives.end())
                            {
                                s_[line][col].first = candidate;
                                s_[line][col].second.clear();
                                break;
                            }
                        }
                    }
                }
            }
        } while (todo);
    }

private:
    Cell s_[9][9];
};

int main()
{
    SudokuSolver s;
    s.read();
    s.print();
    s.solve();
    s.print();
}

