#include "pch.h"
#include "SudokuSolver.h"
#include <algorithm>
#include <sstream>
#include <iterator>



SudokuSolver::SudokuSolver(const std::string& unsolved)
{
    read(unsolved);
}

std::string SudokuSolver::to_string()
{
    std::ostringstream os;
    for (unsigned int c = 0; c < 81; ++c)
    {
        auto line = c / 9;
        auto col = c % 9;
        if (col == 0) os << "\n";
        os << s_[line][col].first << " ";
    }
    os << "\n";
    return os.str();
}

void SudokuSolver::read(const std::string& initial)
{
    static const std::set<int> allnum = { 1,2,3,4,5,6,7,8,9 };

    for (unsigned int c = 0; c < 81; ++c)
    {
        auto line = c / 9;
        auto col = c % 9;

        if (initial[c] != '-')
        {
            s_[line][col].first = initial[c] - 48;
            s_[line][col].second.clear();
        }
        else
        {
            s_[line][col].first = 0;
            s_[line][col].second = allnum;
        }
    }
}

std::set<int> SudokuSolver::in_square(unsigned int ln, unsigned int col)
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

std::set<int> SudokuSolver::other_destination(unsigned int ln, unsigned int col)
{
    std::set<int> result;
    auto sqleft = (col / 3) * 3;
    auto sqtop = (ln / 3) * 3;
    for (auto qln = sqtop; qln < sqtop + 3; ++qln)
    {
        for (auto qcol = sqleft; qcol < sqleft + 3; ++qcol)
        {
            if (qln != ln || qcol != col)
            {
                result.insert(s_[qln][qcol].second.begin(), s_[qln][qcol].second.end());
            }
        }
    }
    return result;
}

std::set<int> SudokuSolver::ruled_out(unsigned int ln, unsigned int col)
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

bool SudokuSolver::solve()
{
    bool impossible{};
    bool todo{};
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
                    impossible = true;
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
    return impossible;
}
