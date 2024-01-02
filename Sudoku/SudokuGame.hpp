//
//  SudokuGame.hpp
//  Sudoku
//
//  Created by Veselin Roganovic on 25.12.23..
//  Klasa SudokuGame predstavlja funkcionalnosti koje igra sudoku izazov zahteva. Kao atribute ima sudoku tablu za trenutnu igru i staticki atribut gameNum koji predstavlja trenutni redni broj igre. Od metoda ima konstruktor za varijantu igre sa pocetnim ucitavanjem table, konstruktor sa varijantom igre sa pocetnim nasumicnim generisanjem table, metodu za ispis statistickih informacija igre i metodu za resavanje sudoku table u igri.

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
