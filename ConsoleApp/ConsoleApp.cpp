// ConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <string>
#include "SudokuSolver.h"


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

std::string typical {
"53-" "-7-" "---"
"6--" "195" "---"
"-98" "---" "-6-"

"8--" "-6-" "--3"
"4--" "8-3" "--1"
"7--" "-2-" "--6"

"-6-" "---" "28-"
"---" "419" "--5"
"---" "-8-" "-79" };


int main()
{
    SudokuSolver s(difficult);
    std::cout << s.to_string();
    bool impossible = s.solve();
    if (!impossible)
    {
        if (!s.complete())
        {
            std::cout << s.to_string();
            std::cout << "make guesses?\n";
        }
        else std::cout << s.to_string();
    }
    else 
        std::cout << "Can not solve this!";
}

