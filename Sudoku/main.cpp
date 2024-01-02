//
//  main.cpp
//  Sudoku
//
//  Created by Veselin Roganovic on 24.12.23..
//  Main fajl projekta - odavde, konkretnije iz main funkcije u ovom fajlu, pocinje izvrsavanje programa

#include <iostream>
#include "SudokuGame.hpp"
#include "SudokuTest.hpp"

using namespace std;

// Pomocna funkcija za izbor fajla od svih prosledjenih kroz argumente komandne linije. Kao parametre prima referencu na vektor sa nazivima fajlova i bool vrednost koja oznacava da li zelimo da taj u taj fajl cuvamo ili iz njega ucitavamo. Kao povratnu vrednost vraca indeks naziva fajla u vektoru svih naziva fajlova.
int choice(vector<string> &files, bool save)
{
    // Korisniku se ispisuju svi nazivi fajlova i daje mu se da izabere jedan. Bira sve dok ne unese validnu postojecu opciju.
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
            
            if(choice >= 1 && choice <= files.size()) return (choice - 1);
            else cout << "Nepostojeca opcija! Pokusajte ponovo..." << endl;
        }
        catch (...)
        {
            cout << "Nepostojeca opcija! Pokusajte ponovo..." << endl;
        }
    }
}

// Main funkcija, pocetna tacka ovog programa
int main(int argc, const char * argv[]) {
    // Kreiramo vektor naziva fajlova prosledjenih kroz argumente komandne linije i ucitavamo ih odatle. Takodje kreiramo i dodatnu promenljivu za apsolutnu putanju u projektu.
    vector<string> files;
    string startingPath = "/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/";
    
    for (int i = 1; i < argc; ++i)
    {
        files.push_back(argv[i]);
    }
    
    // Podesavamo random seed da uvek daje nasumicne brojeve
    srand(unsigned(time(0)));
    
    // Pozivanje testova, inicijalno zakomentarisno
    //SudokuTest test;
    //test.test();
    
    // Ispis dobrodoslice korisniku
    cout << "DOBRO DOSLI U SUDOKU IZAZOV!\n=========================" << endl;
    
    // Dok korisnik ne odluci da prestane sa igranjem, ponavljamo igre
    while(true)
    {
        // Nudimo pocetne opcije korisniku
        cout << "Ukoliko zelite da ucitate sudoku izazov unesite 1, a ukoliko zelite da Vam program izgenerise izazov unesite broj 2: ";
        string input;
        cin >> input;
        
        int option = choice(files, input == "2");
        
        // Ucitavamo igru na nacin na koji je korisnik specifirao, nudimo mu opcije za resavanje i resavanje se vrsi na nacin na koji je specifirao
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
        
        // Dajemo korisniku opciju za kraj igre
        cout << "Ukoliko zelite prekinuti igranje unesite broj 1: ";
        cin >> input;
        
        if(input == "1")
        {
            break;
        }
        
        cout << "=========================" << endl;
    }
    
    return 0;
}

// DODATI:
// 1. SPOJITI KONSTRUKTORE ZA SUDOKUGAME
// 2. DODATI TESTOVE ZA RESAVANJE ZA SUDOKUGAME (AKO IMA NESTO PAMETNO, POPUT KAD KORISNIK PROSLEDI POGRESAN FAJL)
