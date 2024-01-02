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
    bool wrongTable = false;
    
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
                        this->sudoku.setTableNumberValue(i, j, solVal);
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
                        wrongTable = true;
                    }
                }
            }
        }
        
        if(solved && (!sudokuSolution.isOkay() || sudokuSolution.getGoodNums() != 81))
        {
            solved = false;
        }
        
        if(!wrongTable)
        {
            this->sudoku.isOkay();
        }
    }
    else
    {
        this->sudoku.solveTable();
        if(!this->sudoku.isOkay() || this->sudoku.getGoodNums() != 81)
        {
            solved = false;
        }
        this->sudoku.saveTable(filePath);
    }
    
    this->writeStats(solved);
}
