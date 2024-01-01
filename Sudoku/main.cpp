//
//  main.cpp
//  Sudoku
//
//  Created by Veselin Roganovic on 24.12.23..
//

#include <iostream>
#include "SudokuGame.hpp"
#include "SudokuTest.hpp"

using namespace std;

int choice(vector<string> &files, bool save)
{
    while(true)
    {
        try 
        {
            cout << "Unesite redni broj fajla koji zelite da se koristi za " << (save ? "cuvanje" : "ucitavanje") << ":" << endl;
            
            for(int i = 0;i < files.size();i++)
            {
                cout << i + 1 << ". " << files[i] << endl;
            }
            
            int choice;
            cin >> choice;
            
            return (choice - 1);
        } 
        catch (...)
        {
            cout << "Nepostojeca opcija! Pokusajte ponovo..." << endl;
        }
    }
}

int main(int argc, const char * argv[]) {
    srand(unsigned(time(0)));
    
    SudokuTest test;
    test.test();
    
    cout << "DOBRO DOSLI U SUDOKU IZAZOV!\n=========================" << endl;
    
    while(true)
    {
        cout << "Ukoliko zelite da ucitate sudoku izazov unesite naziv datoteke gde se nalazi izazov, a ukoliko zelite da Vam program izgenerise izazov unesite broj 1: ";
        string input;
        cin >> input;
        
        if(input == "1")
        {
            cout << "Unesite naziv datoteke gde zelite da Vam se sacuva izazov";
            cin >> input;
            SudokuGame game(input);
            
            cout << "Ukoliko zelite da resite sudoku zagonetku unesite naziv datoteke gde se resenje nalazi, a ukoliko zelite da Vam je program resi unesite broj 1: ";
            cin >> input;
            if(input == "1")
            {
                cout << "Unesite naziv datoteke gde zelite da Vam se sacuva resenje izazova: ";
                cin >> input;
                game.solve(false, input);
            }
            else
            {
                game.solve(true, input);
            }
        }
        else
        {
            SudokuGame game(input, true);
            
            cout << "Ukoliko zelite da resite sudoku zagonetku unesite naziv datoteke gde se resenje nalazi, a ukoliko zelite da Vam je program resi unesite broj 1: ";
            cin >> input;
            if(input == "1")
            {
                cout << "Unesite naziv datoteke gde zelite da Vam se sacuva resenje izazova: ";
                cin >> input;
                game.solve(false, input);
            }
            else
            {
                game.solve(true, input);
            }
        }
        
        cout << "Ukoliko zelite da nastavite sa resavanjem sudoku izazova unesite DA, a ukoliko zelite prekinuti napisite NE: ";
        cin >> input;
        
        if(input == "NE")
        {
            break;
        }
    }
    
    return 0;
}
