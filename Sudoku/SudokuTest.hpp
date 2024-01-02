//
//  SudokuTest.hpp
//  Sudoku
//
//  Created by Veselin Roganovic on 25.12.23..
//
//  SudokuTest je klasa koji se koristi za testiranje funkcionalnosti klase Sudoku9
//  Atributi klase su parametri koji govore da li i koliko puta treba izvrsiti odredjeni test
//  Ovi atributi podesavaju se konstruktorom
//  Metode ove klase su pojedinacni testovi koji vracaju da li je test uspesan ili ne, kao i metoda test koja sluzi da izvrsi sve specificirane testove i ispise njihove rezultate

#ifndef SudokuTest_hpp
#define SudokuTest_hpp

#include <stdio.h>

class SudokuTest
{
    bool creationTest;
    bool loadingTest;
    bool okayTest;
    int saveTest;
    int solTest;
    
public:
    SudokuTest();
    SudokuTest(bool creationTest, bool loadingTest, bool okayTest, int saveTest, int solTest);
    
    bool tableCreationTest();
    
    bool tableLoadingTest();
    
    bool tableSaveTest();
    
    bool isOkayTest();
    
    bool solveTest();
    
    void test();
};

#endif /* SudokuTest_hpp */
