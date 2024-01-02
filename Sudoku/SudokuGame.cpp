//
//  SudokuGame.cpp
//  Sudoku
//
//  Created by Veselin Roganovic on 25.12.23..
//

#include "SudokuGame.hpp"

// Inicijalizacija staticke promenljive za broj odigranih partija na 0
int SudokuGame::gameNum = 0;

// Konstruktor za kreaciju partije sa nasumicnim generisanjem table, uzima jedan parametar, a to je string koji predstavlja put do fajla gde ce se sacuvati nasumicno generisana tabla. Broj partija se povecava za jedan i ispisujemo tablu.
SudokuGame::SudokuGame(const string filePath) : sudoku()
{
    this->gameNum++;
    this->sudoku.saveTable(filePath);
    this->sudoku.outputTable();
}

// Konstruktor za kreaciju partije sa ucitavanjem table, uzima dva parametetrax, a to su string koji predstavlja put do fajla odakle se ucitava tabla i informacija za cuvanje table. Broj partija se povecava za jedan i ispisujemo tablu.
SudokuGame::SudokuGame(const string filePath, const bool load) : sudoku(filePath)
{
    this->gameNum++;
    this->sudoku.outputTable();
}

// Metoda za ispis statistickih parametara partije, prima jedan parametar, a to je da li je sudoku tabla uspesno resena. Nema povratne vrednosti. Ispisuje broj partije, da li je tabla uspesno resena i statisticke informacije same table putem njene metode.
void SudokuGame::writeStats(const bool solved)
{
    cout << "Broj partije: " << this->gameNum << endl;
    cout << "Da li je resena zadata tabla: " << (solved ? "DA" : "NE") << endl;
    this->sudoku.writeStats();
}

// Metoda za resavanje sudoku table u igri, kao parametre prima bool vrednost - da li korisnik resava datu tablu i string - put do fajla sa korisnickim resenjem ili put gde treba smestiti resenje programa. Nema povratnih vrednosti. Funkcionise tako sto ucitava korisnicko resenje ili resava program i zatim to resenje proverava i poziva funkciju za ispis statistikcih informacija programa.
void SudokuGame::solve(const bool user, const string filePath)
{
    // Pomocne prmoenljive za to da li je tabla uspesno resena
    bool solved = true;
    bool wrongTable = false;
    
    if(user)
    {
        // Ako resava korisnik, kreiramo novi objekat sudoku table i u njega ucitavamo korisnicko resenje i ispisujemo ga
        Sudoku9 sudokuSolution(filePath);
        sudokuSolution.outputTable();
        
        // Prolazimo kroz sve elemente sudoku resenja i uporedjujemo da li je ono validno za zadatu tablu u igri. Ako neko polje nije popunjeno ili je neko polje promenjeno, resenje nije validno.
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
        
        // Ako resenje nije popunjeno po pravilima igre ili nije potpuno popunjeno, opet resenje nije valindo
        if(solved && (!sudokuSolution.isOkay() || sudokuSolution.getGoodNums() != 81))
        {
            solved = false;
        }
        
        // Ukoliko je korisnik resavao zadatu tablu (makar i neuspesno), postavljamo mu vrednosti za dobra i losa popunjena polja
        if(!wrongTable)
        {
            this->sudoku.isOkay();
        }
    }
    else
    {
        // Ako resava program, tabla se resava preko poznate funkcije, ispisuje, proverava se validnost resenja i cuva se tabla u fajlu
        this->sudoku.solveTable();
        this->sudoku.outputTable();
        if(!this->sudoku.isOkay() || this->sudoku.getGoodNums() != 81)
        {
            solved = false;
        }
        this->sudoku.saveTable(filePath);
    }
    
    // Na kraju, ispisujemo statisticke podatke za ovu partiju
    this->writeStats(solved);
}
