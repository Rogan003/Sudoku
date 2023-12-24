//
//  SudokuGame.hpp
//  Sudoku
//
//  Created by Veselin Roganovic on 25.12.23..
//

#ifndef SudokuGame_hpp
#define SudokuGame_hpp

#include <stdio.h>
#include "Sudoku9.hpp"

class SudokuGame
{
    Sudoku9 sudoku;
    
public:
    static int gameNum;
    
    SudokuGame(const string filePath);
    
    SudokuGame(const string filePath, const bool load);
    
    void writeStats(const bool solved);
    
    void solve(const bool user, const string filePath);
};

#endif /* SudokuGame_hpp */
