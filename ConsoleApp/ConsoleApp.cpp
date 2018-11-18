// ConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
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

int main()
{
    SudokuSolver s;
    s.read(typical);
    std::cout << s.to_string();
    s.solve();
    std::cout << s.to_string();
}

