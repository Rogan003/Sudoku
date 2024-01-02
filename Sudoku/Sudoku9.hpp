//
//  Sudoku9.hpp
//  Sudoku
//
//  Created by Veselin Roganovic on 24.12.23..
//  Sudoku9 je klasa koja predstavlja sudoku tablu sa matricom polja, brojacem dobro postavljenih polja i brojacem lose postavljenih polja. U samoj matrici prazna polja predstavljena su sa 0, a brojevi od 1-9 predstavljaju validne vrednosti polja sudoku table.
//  Metode ove klase su metode za ucitavanje i cuvanje table iz/u datoteke, generisanje nove table, proveru validnosti table (isOkay), resavanje date table, kao i pomocna metoda za rekurzivno resavanje table, ispis statistickih informacija za tablu, geteri za brojac dobrih polja i brojac losih polja i geter i seter za odredjeno polje table

#ifndef Sudoku9_hpp
#define Sudoku9_hpp

#include <stdio.h>
#include <iostream>
#include <set>

using namespace std;

class Sudoku9 
{
    int table[9][9];
    int goodNums;
    int badNums;
    bool solveTableRec(int i, int j, set<int> (&rows)[9], set<int> (&cols)[9], set<int> (&boxes)[9]);
    
public:
    Sudoku9();
    
    Sudoku9(const string filePath);
    
    void loadTable(const string filePath);
    
    void saveTable(const string filePath);
    
    bool isOkay();
    
    bool solveTable();
    
    void createTable();
    
    void writeStats();
    
    int getTableNumberValue(const int i, const int j);
    
    int getGoodNums();
    
    int getBadNums();
    
    void setTableNumberValue(const int i, const int j, const int val);
};

#endif /* Sudoku9_hpp */
