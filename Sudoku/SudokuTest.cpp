//
//  SudokuTest.cpp
//  Sudoku
//
//  Created by Veselin Roganovic on 25.12.23..
//

#include "SudokuTest.hpp"
#include "Sudoku9.hpp"

// Podrazumevani konstruktor bez parametara klase SudokuTest, postavlja sve bool atribute na true (da se sve funkcije testiraju), a sve int atribute na 3 (da se sve funkcije koje treba vise puta da se testiraju, testiraju po 3 puta)
SudokuTest::SudokuTest() : loadingTest(true), okayTest(true), creationTest(true), saveTest(3), solTest(3) {}

// Konstruktor sa parametrima za klasu SudokuTest, podesava koji testovi i koliko puta ce neki od njih biti izvedeni
SudokuTest::SudokuTest(bool creationTest, bool loadingTest, bool okayTest, int saveTest, int solTest) : creationTest(creationTest), loadingTest(loadingTest), okayTest(okayTest), saveTest(saveTest), solTest(solTest) {}

// Test za ucitavanje table iz datoteke
bool SudokuTest::tableLoadingTest()
{
    // Test za ucitavanje table sa svim praznim poljima O (polje u matrici ima vrednost 0), ako neko polje nije 0 test pada
    // Promenljiva indikator validnosti testa 1
    bool pass1 = true;
    
    // Ucitavanje table putem konstruktora koji koristi tu metodu
    Sudoku9 table1("/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/tablezeros");
    
    // Prolazak kroz sva polja table i provera da li su sva 0 (prazna), ako nisu ucitavanje nije dobro
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            if(table1.getTableNumberValue(i, j) != 0)
            {
                pass1 = false;
            }
        }
    }
    
    // Ispis rezultata testa
    cout << "Test ucitavanje prazne table: " << (pass1 ? "prosao" : "pao") << endl;
    
    // Test za ucitavanje table sa nekim popunjenim poljima, proveravamo da li sva polja imaju ocekivane vrednosti
    // Promenljiva indikator validnosti testa 2
    bool pass2 = true;
    
    // Ucitavanje table putem konstruktora koji koristi tu metodu
    Sudoku9 table2("/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/tablehalffull");
    
    // Ocekivana matrica za ovu tablu
    int expectedTable[9][9] = {{5,0,0,0,0,0,0,0,0}, {0,3,0,0,4,0,0,0,0}, {0,0,0,5,0,0,0,2,0}, {0,6,0,7,0,0,0,1,0}, {0,0,0,0,0,0,0,0,2}, {0,0,0,0,0,9,0,0,0}, {0,2,0,0,0,0,0,0,5}, {0,0,8,0,0,0,0,9,0}, {0,0,1,0,0,0,4,0,0}};
    
    // Prolazak kroz sva polja table i provera da li su vrednosti na svim poljima ocekivane
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            if(table2.getTableNumberValue(i, j) != expectedTable[i][j])
            {
                pass2 = false;
            }
        }
    }
    
    // Ispis rezultata testa
    cout << "Test ucitavanje table sa nekim popunjenim poljima: " << (pass2 ? "prosao" : "pao") << endl;
    
    // Test za ucitavanje potpuno pune table bez praznih polja, proveravamo da li sva polja imaju ocekivane vrednosti
    // Promenljiva indikator validnosti testa 3
    bool pass3 = true;
    
    // Ucitavanje table putem konstruktora koji koristi tu metodu
    Sudoku9 table3("/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/tablefull");
    
    // Ocekivana matrica za ovu tablu
    int expectedTable2[9][9] = {{5,4,7,1,8,2,3,6,9}, {1,3,2,9,4,6,7,5,8}, {8,9,6,5,3,7,1,2,4}, {2,6,9,7,5,4,8,1,3}, {3,5,4,2,1,8,9,7,6}, {7,8,1,3,6,9,5,4,2}, {9,2,5,8,7,1,4,3,6}, {4,7,8,6,2,3,5,9,1}, {6,1,3,4,9,5,2,7,8}};
    
    // Prolazak kroz sva polja table i provera da li su vrednosti na svim poljima ocekivane
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            if(table3.getTableNumberValue(i, j) != expectedTable2[i][j])
            {
                pass3 = false;
            }
        }
    }
    
    // Ispis rezultata testa
    cout << "Test ucitavanje table bez praznih polja: " << (pass3 ? "prosao" : "pao") << endl;
    
    // vracamo tacno ako svi testovi prolaze, netacno ako ne prolaze svi testovi
    return pass1 && pass2 && pass3;
}

// Test za proveru rada funkcije koja proverava da li je tabla dobro popunjena i podesava vrednosti dobrih i lose postavljenih polja
bool SudokuTest::isOkayTest()
{
    // Test za isOkay table sa svim praznim poljima O i provera da li funkcija vraca tacan rezultat, broj dobrih i lose postavljenih polja treba da bude 0
    // Promenljiva indikator validnosti testa 1
    bool pass1 = true;
    
    // Ucitavanje table putem konstruktora koji koristi tu metodu
    Sudoku9 table1("/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/tablezeros");
    
    // Poziv funkcije nad ovom tablom i smestanje vrednosti da li je tabla dobro popunjena u promenljivu okay
    bool okay = table1.isOkay();
    
    // Proveravamo ocekivane rezultate funkcije i podesavamo vrednost indikatora ako je pao test
    if(!okay || table1.getGoodNums() != 0 || table1.getBadNums() != 0)
    {
        pass1 = false;
    }
    
    // Ispis rezultata testa
    cout << "Test isOkay nad praznom tablom: " << (pass1 ? "prosao" : "pao") << endl;

    // Test za isOkay potpuno popunjene table koja nije ispravno popunjena, provera da li funkcija vraca netacan rezultat, ocekivan broj dobro postavljenih polja je 77, a losih 4
    // Promenljiva indikator validnosti testa 2
    bool pass2 = true;
    
    // Ucitavanje table putem konstruktora koji koristi tu metodu
    Sudoku9 table2("/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/tablefull");
    
    // Poziv funkcije nad ovom tablom i smestanje vrednosti da li je tabla dobro popunjena u promenljivu okay2
    bool okay2 = table2.isOkay();
    
    // Proveravamo ocekivane rezultate funkcije i podesavamo vrednost indikatora ako je pao test
    if(okay2 || table2.getGoodNums() != 77 || table2.getBadNums() != 4)
    {
        pass2 = false;
    }
    
    // Ispis rezultata testa
    cout << "Test isOkay nad potpuno popunjenom netacnom tablom: " << (pass2 ? "prosao" : "pao") << endl;
    
    // Test za isOkay potpuno popunjene table koja je ispravno popunjena, provera da li funkcija vraca tacan rezultat, ocekivan broj dobro postavljenih polja je 81, a losih 0
    // Promenljiva indikator validnosti testa 3
    bool pass3 = true;
    
    // Ucitavanje table putem konstruktora koji koristi tu metodu
    Sudoku9 table3("/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/tablegood");
    
    // Poziv funkcije nad ovom tablom i smestanje vrednosti da li je tabla dobro popunjena u promenljivu okay3
    bool okay3 = table3.isOkay();
    
    // Proveravamo ocekivane rezultate funkcije i podesavamo vrednost indikatora ako je pao test
    if(!okay3 || table3.getGoodNums() != 81 || table3.getBadNums() != 0)
    {
        pass3 = false;
    }
    
    // Ispis rezultata testa
    cout << "Test isOkay nad potpuno popunjenom tacnom tablom: " << (pass3 ? "prosao" : "pao") << endl;
    
    // Test za isOkay potpuno popunjene table koja ima samo jednu izmenu do dobre, provera da li funkcija vraca tacan rezultat, ocekivan broj dobro postavljenih polja je 78, a losih 3
    // Promenljiva indikator validnosti testa 4
    bool pass4 = true;
    
    // Ucitavanje table putem konstruktora koji koristi tu metodu
    Sudoku9 table4("/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/tablealmostgood");
    
    // Poziv funkcije nad ovom tablom i smestanje vrednosti da li je tabla dobro popunjena u promenljivu okay4
    bool okay4 = table4.isOkay();
    
    // Proveravamo ocekivane rezultate funkcije i podesavamo vrednost indikatora ako je pao test
    if(okay4 || table4.getGoodNums() != 78 || table4.getBadNums() != 3)
    {
        pass4 = false;
    }
    
    // Ispis rezultata testa
    cout << "Test isOkay nad potpuno popunjenom tablom kojoj fali jedna izmena da bude tacna: " << (pass4 ? "prosao" : "pao") << endl;
    
    return pass1 && pass2 && pass3 && pass4;
}

// Test za proveru rada funkcije za kreaciju nove table, ocekujemo da nijedna podmatrica nema vise od 6 brojeva i da su svi brojevi od 1-9 ili 0 za prazno polje, kao i da je moguce resiti ovakvu tablu
bool SudokuTest::tableCreationTest()
{
    // Kreacija nasumicne nove table putem konstruktora bez parametara
    Sudoku9 testTable;
    
    // Promenljive koje ce pokazivati rezultate testova
    // numNums = da li ima manje ili tacno 6 brojeva po svakoj podmatrici
    // allNums = da li su sve vrednosti validni brojevi
    // isOkay = da li je tabla resiva
    bool numNums = true, allNums = true, isOkay;
    
    // Prolazimo kroz sve elemente tako sto prolazimo kroz svaku podmatricu
    // Za svaku podmatricu brojimo broj elemenata i ako je on veci od 6, numElems postaje false
    // Svaki element proveravamo da li je u dobrom opsegu vrednosti, ako nije allNums postaje false
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            int numElems = 0;
            
            for(int k = 0;k < 3;k++)
            {
                for(int l = 0;l < 3;l++)
                {
                    int val = testTable.getTableNumberValue(i * 3 + k, j * 3 + l);
                    if(val >= 0 && val <= 9)
                    {
                        if(val != 0) numElems++;
                    }
                    else
                    {
                        allNums = false;
                    }
                }
            }
            
            if(numElems > 6)
            {
                numNums = false;
            }
            
            numElems = 0;
        }
    }
    
    // Proveravamo da li je moguce resiti ovakvu tablu
    testTable.solveTable();
    isOkay = testTable.isOkay() && testTable.getGoodNums() == 81;
    
    // Ispisi rezultata testova
    cout << "Test da li kreirana tabla ima manje ili tacno 6 brojeva po svakoj podmatrici: " << (numNums ? "prosao" : "pao") << endl;
    cout << "Test da li kreirana tabla su sve vrednosti validni brojevi: " << (allNums ? "prosao" : "pao") << endl;
    cout << "Test da li kreirana tabla je tabla resiva: " << (isOkay ? "prosao" : "pao") << endl;
    
    return numNums && allNums && isOkay;
}

// Test za cuvanje table u fajlu, proveravamo da li ta sacuvana tabla moze da se ucita sa ocuvanim stanjem (samim kriterijumom funkcije citanja mora biti napisana u lepom citljivom formatu u fajlu)
bool SudokuTest::tableSaveTest()
{
    // Kreiramo novu nasumicnu tablu konstruktorom bez parametara
    Sudoku9 testTable;
    
    // Cuvamo tablu na lokaciji test_cuvanje
    testTable.saveTable("/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/test_cuvanje");
    
    // Ucitavamo tablu u novu promenljivu putem funkcije za ucitavanje kroz konstruktor sa jednim parametrom
    Sudoku9 testTableNew("/Users/rogan003/Desktop/Fakultet/3. semestar/OOP 2/Projektni_zadatak/Sudoku/Sudoku/test_cuvanje");
    
    // Prolazimo kroz sve elemente obe table i ako se makar jedan ne poklapa ispisujemo pad testa i vracamo false
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            if(testTable.getTableNumberValue(i, j) != testTableNew.getTableNumberValue(i, j))
            {
                cout << "Test cuvanja table u datoteku: pao" << endl;
                return false;
            }
        }
    }
    
    // Ako su svi slucajevi prosli ispisujemo da je test prosao i vracamo true
    cout << "Test cuvanja table u datoteku: prosao" << endl;
    return true;
}

// Test za funkciju za resavanje date sudoku table, proveravamo da li je kompletno i ispravno popunjena
bool SudokuTest::solveTest()
{
    // Kreiramo nasumicnu novu sudoku tablu konstruktorom bez parametara
    Sudoku9 testTable;
    
    // Resavamo tu tablu
    testTable.solveTable();
    
    // Proveravamo ispravnost resenja tako sto proveravamo da li je tabla kompletno popunjena i da li su sva polja na validnim pozicijama, i ispravnost smestamo u promenljivu isOkay
    bool isOkay = testTable.isOkay() && testTable.getGoodNums() == 81;
    
    // Ispis rezultata testa
    cout << "Test za resavanje sudoku table: " << (isOkay ? "prosao" : "pao") << endl;
    
    return isOkay;
}

// Funkcija za testiranje klase SudokuTest, testira sve slucajeve koje smo zadali konstruktorom i na kraju ispisuje da li su svi testovi prosli ili ne
void SudokuTest::test()
{
    bool loadingTest = true, okayTest = true, creationTest = true, saveTest = true, solTest = true;
    
    if(this->loadingTest)
    {
        loadingTest = this->tableLoadingTest();
    }
    
    if(this->okayTest)
    {
        okayTest = this->isOkayTest();
    }
    
    if(this->creationTest)
    {
        creationTest = this->tableCreationTest();
    }
    
    for(int i = 0;i < this->saveTest;i++)
    {
        if(saveTest)
        {
            saveTest = this->tableSaveTest();
        }
        else
        {
            this->tableSaveTest();
        }
    }
    
    for(int i = 0;i < this->solTest;i++)
    {
        if(solTest)
        {
            solTest = this->solveTest();
        }
        else
        {
            this->solveTest();
        }
    }
    
    if(loadingTest && okayTest && creationTest && saveTest && solTest)
    {
        cout << "Testovi prosli!" << endl;
    }
    else
    {
        cout << "Testovi pali!" << endl;
    }
}
