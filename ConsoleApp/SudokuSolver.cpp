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
        os << s_[line][col].solution << " ";
    }
    os << "\n";
    return os.str();
}

void SudokuSolver::read(const std::string& initial)
{
    for (unsigned int c = 0; c < 81; ++c)
    {
        auto line = c / 9;
        auto col = c % 9;

        if (initial[c] != '-')
        {
            s_[line][col].solution = initial[c] - 48;
            s_[line][col].candidates.clear();
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
            if (s_[qln][qcol].solution)
            {
                result.insert(s_[qln][qcol].solution);
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
                auto& cell_candidates = s_[qln][qcol].candidates;
                result.insert(cell_candidates.begin(), cell_candidates.end());
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
        int hor = s_[ln][c].solution;
        if (hor)
        {
            result.insert(hor);
        }
        int ver = s_[c][col].solution;
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


bool SudokuSolver::complete()
{
    for (unsigned int c = 0; c < 81; ++c)
    {
        auto line = c / 9;
        auto col = c % 9;

        if (s_[line][col].solution == 0)
            return false;
    }
    return true;
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

            if (s_[line][col].solution == 0)
            {
                std::set<int> remaining;
                auto eliminate = ruled_out(line, col);
                auto& candidates = s_[line][col].candidates;
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
                    s_[line][col].solution = *remaining.begin();
                    s_[line][col].candidates.clear();
                }
                else
                {
                    if (remaining.size() < s_[line][col].candidates.size())
                        todo = true;
                    s_[line][col].candidates = remaining;

                    auto alternatives = other_destination(line, col);
                    for (int candidate : remaining)
                    {
                        auto found = std::find(alternatives.begin(), alternatives.end(), candidate);
                        if (found == alternatives.end())
                        {
                            s_[line][col].solution = candidate;
                            s_[line][col].candidates.clear();
                            break;
                        }
                    }
                }
            }
        }
    } while (todo);
    return impossible;
}
