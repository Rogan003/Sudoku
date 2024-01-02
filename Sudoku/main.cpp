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
    vector<string> files;
    string startingPath = "/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/";
    
    for (int i = 1; i < argc; ++i)
    {
        files.push_back(argv[i]);
    }
    
    srand(unsigned(time(0)));
    
    //SudokuTest test;
    //test.test();
    
    cout << "DOBRO DOSLI U SUDOKU IZAZOV!\n=========================" << endl;
    
    while(true)
    {
        cout << "Ukoliko zelite da ucitate sudoku izazov unesite 1, a ukoliko zelite da Vam program izgenerise izazov unesite broj 2: ";
        string input;
        cin >> input;
        
        int option = choice(files, input == "2");
        
        if(input == "2")
        {
            SudokuGame game(startingPath + files[option]);
            
            while(true)
            {
                cout << "Ukoliko zelite da resite sudoku zagonetku unesite 1, a ukoliko zelite da Vam je program resi unesite broj 2: ";
                cin >> input;
                
                option = choice(files, (input == "2"));
                
                if(input == "2")
                {
                    game.solve(false, startingPath + files[option]);
                }
                else if(input == "1")
                {
                    game.solve(true, startingPath + files[option]);
                }
                else
                {
                    cout << "Nevazeca opcija! Pokusajte ponovo..." << endl;
                    continue;
                }
                
                break;
            }
        }
        else if(input == "1")
        {
            SudokuGame game(startingPath + files[option], true);
            
            while(true)
            {
                cout << "Ukoliko zelite da resite sudoku zagonetku unesite 1, a ukoliko zelite da Vam je program resi unesite broj 2: ";
                cin >> input;
                
                option = choice(files, (input == "2"));
                
                if(input == "2")
                {
                    game.solve(false, startingPath + files[option]);
                }
                else if(input == "1")
                {
                    game.solve(true, startingPath + files[option]);
                }
                else
                {
                    cout << "Nevazeca opcija! Pokusajte ponovo..." << endl;
                    continue;
                }
                
                break;
            }
        }
        else
        {
            cout << "Nepostojeca opcija! Pokusajte ponovo..." << endl;
            continue;
        }
        
        cout << "Ukoliko zelite da nastavite sa resavanjem sudoku izazova unesite DA, a ukoliko zelite prekinuti napisite NE: ";
        cin >> input;
        
        if(input == "NE")
        {
            break;
        }
        
        cout << "=========================" << endl;
    }
    
    return 0;
}
