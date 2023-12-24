//
//  SudokuTest.hpp
//  Sudoku
//
//  Created by Veselin Roganovic on 25.12.23..
//
//  SudokuTest je klasa koji se koristi za testiranje funkcionalnosti klase Sudoku9
//  Testiranje se vrsi pozivom konstruktora klase koji onda poziva sve testove i ispisuje njihovu ispravnost

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
