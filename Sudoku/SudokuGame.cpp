//
//  SudokuGame.cpp
//  Sudoku
//
//  Created by Veselin Roganovic on 25.12.23..
//

#include "SudokuGame.hpp"

int SudokuGame::gameNum = 0;

SudokuGame::SudokuGame(const string filePath) : sudoku()
{
    this->gameNum++;
    this->sudoku.saveTable(filePath);
}

SudokuGame::SudokuGame(const string filePath, const bool load) : sudoku(filePath)
{
    this->gameNum++;
}

void SudokuGame::writeStats(const bool solved)
{
    cout << "Broj partije: " << this->gameNum << endl;
    cout << "Da li je resena zadata tabla: " << (solved ? "DA" : "NE") << endl;
    this->sudoku.writeStats();
}

void SudokuGame::solve(const bool user, const string filePath)
{
    bool solved = true;
    
    if(user)
    {
        Sudoku9 sudokuSolution(filePath);
        
        for(int i = 0;i < 9;i++)
        {
            for(int j = 0;j < 9;j++)
            {
                int val = this->sudoku.getTableNumberValue(i, j);
                int solVal = sudokuSolution.getTableNumberValue(i, j);
                if(val == 0)
                {
                    if(solVal != 0)
                    {
                        this->sudoku.setTableNumberValue(i, j, val);
                    }
                    else
                    {
                        solved = false;
                    }
                }
                else
                {
                    if(val != solVal)
                    {
                        solved = false;
                    }
                }
            }
        }
        
        if(solved && (!sudokuSolution.isOkay() || sudokuSolution.getGoodNums() != 81))
        {
            solved = false;
        }
    }
    else
    {
        this->sudoku.solveTable();
        this->sudoku.saveTable(filePath);
    }
    
    this->writeStats(solved);
}
