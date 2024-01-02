//
//  Sudoku9.cpp
//  Sudoku
//
//  Created by Veselin Roganovic on 24.12.23..
//

#include "Sudoku9.hpp"
#include <fstream>

// Podrazumevani konstruktor klase Sudoku9, poziva metodu za generisanje nove sudoku table i postavlja brojac dobrih i losih polja na 0
Sudoku9::Sudoku9() : goodNums(0), badNums(0)
{
    this->createTable();
}

// Konstruktor sa jednim parametrom klase Sudoku9, gde je taj parametar je put do fajla gde je smestena sudoku tabla koju treba ucitati, poziva metodu za ucitavanje table i postavlja brojac dobrih i losih polja na 0
Sudoku9::Sudoku9(const string filePath) : goodNums(0), badNums(0)
{
    this->loadTable(filePath);
}

// Metoda za ucitavanje table, prima jedan parametar koji predstavlja put do fajla gde je smestena sudoku tabla koju treba ucitati. Parsira jedan po jedan red tog fajla po unapred poznatom pravilu, a to je da se redovi koji razdvajaju redove brojeva (_________________) preskacu, a redovi sa brojevima se ucitavaju u matricu polja tako sto se preskacu razdvajaci polja (|), tj. ucitava se svaki drugi karakter i njegovu vrednost stavljamo u odgovarajuce polja matrice polja. Karakteri se parsiraju tako sto se brojevi 1-9 direktno takvi zapisuju, dok se karakter razmaka, koji predstavlja prazno polje, u matricu polja zapisuje kao 0.
void Sudoku9::loadTable(const string filePath)
{
    // Otvaramo zeljeni fajl i citamo iz njega red po red
    ifstream file;
    
    file.open(filePath);
    
    string inputLine;
    
    int row = 0;
    
    while(getline(file, inputLine))
    {
        // Ako red nije razdvajac redova, parsiramo i upisujemo karaktere
        if(inputLine[0] != '_')
        {
            // Prolazimo kroz sve karaktere i parsiramo ih i upisujemo
            for(int i = 0;i < 9;i++)
            {
                // Pristupamo karakteru polja iz datoteke i ako je on razmak upisujemo 0, a ako nije, upisujemo ga kao broj
                if(inputLine[i * 2] == ' ')
                {
                    this->table[row][i] = 0;
                }
                else
                {
                    this->table[row][i] = inputLine[i * 2] - '0';
                }
            }
            
            row++;
        }
    }
    
    file.close();
}

// Metoda za cuvanje table, prima jedan parametar koji predstavlja put do fajla gde treba smestiti sudoku tablu. Sudoku tablu smestamo tako sto svaki niz iz matrice polja predstavlja red u fajlu, gde je svako polje, tj vrednost elementa niza matrice, odvojeno sa |, a redovi sa _________________. Polja iz matrice koja nisu prazna predstavljamo takva kakva jesu, dok prazna polja zapisujemo kao razmak.
void Sudoku9::saveTable(const string filePath)
{
    // Otvaramo zeljeni fajl
    ofstream file;
    
    file.open(filePath);
    
    // Prolazimo niz po niz kroz matricu polja i onda element po element kroz svaki pojedinacni niz
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            // Ako je element prazno polje (0) upisujemo ga kao razmak, a ako je popunjeno polje upisujemo ga takvog kakav jeste
            if(this->table[i][j] == 0)
            {
                file << ' ';
            }
            else
            {
                file << this->table[i][j];
            }
            
            // svaka dva polja razdvajamo sa |
            if(j != 8)
            {
                file << "|";
            }
        }
        
        // Svaki red razdvajamo sa _________________
        if(i != 8)
        {
            file << "\n_________________\n";
        }
    }
    
    file.close();
}

// Metoda za proveru ispravnosti postavljenih polja na sudoku tabli. Takodje, metoda postavlja vrednosti brojaca dobro i lose postavljenih polja. Kao povratnu vrednost vraca informaciju da li su polja na tabli dobro postavljena. Napomena: ne proveravamo da li su sva polja popunjena! Ideja iza metode je da idemo redom kroz kolone, redove i 3x3 podmatrice i belezimo broj praznih polja i dodajemo lose postavljena polja u set (ona koja vec imamo u toj koloni, redu ili podmatrici). Nakon toga azuriramo vrednosti klase tako da je broj losih polja broj elemenata seta, a broj dobrih polja 81 - broj praznih polja - broj losih polja. Na kraju, ukoliko je broj lose postavljenih polja 0, vracamo true, u suprotnom false.
bool Sudoku9::isOkay()
{
    // Kreiramo pocetne pomocne promenljive
    set<int> elems; // Kreiramo prazan set u koji cemo dodavati vrednosti polja jednog reda ili jedne kolone ili jedne podmatrice
    set<pair<int, int>> badElems; // Kreiramo prazan set u koji cemo dodavati lose postavljene brojeve
    int numZeroes = 0; // Kreiramo brojac praznih polja
    
    // Prolazimo kroz sve elemente matrice, analizirajuci redove matrice
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            // Za svako polje u redu povecavamo brojac praznih polja ako je to prazno polje, a ako nije proveravamo da li vec postoji u setu elemenata reda, ako postoji dodajemo ga u set lose postavljenih polja, a ako ne postoji dodajemo mu vrednost u set vrednosti elemenata reda
            if(this->table[i][j] != 0)
            {
                if(elems.find(this->table[i][j]) != elems.end())
                {
                    badElems.insert(pair<int, int>(i, j));
                }
                else
                {
                    elems.insert(this->table[i][j]);
                }
            }
            else
            {
                numZeroes++;
            }
        }
        
        // Nakon analize jednog citavog reda, praznimo set vrednosti elemenata reda
        elems.clear();
    }
    
    // Prolazimo kroz sve elemente matrice, analizirajuci kolone matrice
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            // Za svako popunjeno polje u koloni proveravamo da li vec postoji u setu elemenata kolone, ako postoji dodajemo ga u set lose postavljenih polja, a ako ne postoji dodajemo mu vrednost u set vrednosti elemenata kolone
            if(this->table[j][i] != 0)
            {
                if(elems.find(this->table[j][i]) != elems.end())
                {
                    badElems.insert(pair<int, int>(j, i));
                }
                else
                {
                    elems.insert(this->table[j][i]);
                }
            }
        }
        
        // Nakon analize jedne citave kolone, praznimo set vrednosti elemenata kolone
        elems.clear();
    }
    
    // Prolazimo kroz sve elemente matrice, analizirajuci 3x3 podmatrice matrice
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            for(int k = 0;k < 3;k++)
            {
                for(int l = 0;l < 3;l++)
                {
                    // Za svako popunjeno polje u podmatrici proveravamo da li vec postoji u setu elemenata podmatrice, ako postoji dodajemo ga u set lose postavljenih polja, a ako ne postoji dodajemo mu vrednost u set vrednosti elemenata podmatrice
                    if(this->table[i * 3 + k][j * 3 + l] != 0)
                    {
                        if(elems.find(this->table[i * 3 + k][j * 3 + l]) != elems.end())
                        {
                            badElems.insert(pair<int, int>(i * 3 + k, j * 3 + l));
                        }
                        else
                        {
                            elems.insert(this->table[i * 3 + k][j * 3 + l]);
                        }
                    }
                }
            }
            
            // Nakon analize jedne citave kolone, praznimo set vrednosti elemenata podmatrice
            elems.clear();
        }
    }
    
    // Azuriramo brojace dobro i lose postavljenih polja i vracamo da li je tabla dobro popunjena ili ne
    this->badNums = int(badElems.size());
    this->goodNums = 81 - this->badNums - numZeroes;
    
    return badElems.empty();
}

// Pomocna metoda za resavanje sudoku table. Kao parametre prima trenutne koordinate za analizu, kao i reference na nizove setova vrednosti popunjenih polja redova, kolona i podmatrica. Kao povratnu vrednost vraca da li je tabla uspesno resena ili ne. Funkcija se realizuje rekurzivno, proveravajuci koje sve vrednosti je moguce staviti na prosledjene koordinate polja i azurirajuci parametre, te pravi dalje rekurzivne pozive pomerajuci koordinate za jedan, sve dok validno ne resi datu tablu ili ne dodje do toga da nema validnog resenja za datu tablu, tj ne dodje do slucaja da nijedna vrednost za prvo prazno polje ne moze da da validno resenje.
bool Sudoku9::solveTableRec(int i, int j, set<int> (&rows)[9], set<int> (&cols)[9], set<int> (&boxes)[9])
{
    // Ukoliko je brojac kolone na 9, treba povecati brojac reda i staviti brojac kolone na 0 (premestamo se na prvo polje u novom redu). Specijalan slucaj je da nema vise redova, i onda se vraca vrednost true, uspesno je resena tabla.
    if(j == 9)
    {
        if(i == 8) return true;
        
        j = 0;
        i++;
    }
 
    // Ukoliko je polje vec popunjeno, rekurzivno pozivamo funkciju nad narednim poljem
    if(this->table[i][j])
    {
        return solveTableRec(i, j + 1, rows, cols, boxes);
    }
    
    // Prolazimo kroz sve moguce vrednosti za trenutno polje
    for(int k = 1; k <= 9; k++)
    {
        // Ako trenutna vrednost iteracije moze biti postavljena na trenutno polje, postavljamo tu vrednost na polje i azuriramo set reda, kolone i podmatrice za to polje, tako da je sada dodata i ova nova vrednost
        if((rows[i].find(k) == rows[i].end()) && (cols[j].find(k) == cols[j].end()) && (boxes[int(i / 3) * 3 + int(j / 3)].find(k) == boxes[int(i / 3) * 3 + int(j / 3)].end()))
        {
            this->table[i][j] = k;
            rows[i].insert(k);
            cols[j].insert(k);
            boxes[int(i / 3) * 3 + int(j / 3)].insert(k);
 
            // Rekurzivno pozivamo funkciju nad narednim poljem, i ako ona vrati true, vracamo true kao rezultat i ovog poziva
            if(solveTableRec(i, j + 1, rows, cols, boxes)) return true;
            
            // Ako se ne desi da je ova iteracija dala validno resenje, azuriramo set reda, kolone i podmatrice za to polje tako sto brisemo ovu vrednost iz njih i vracamo vrednost polja na 0
            rows[i].erase(k);
            cols[j].erase(k);
            boxes[int(i / 3) * 3 + int(j / 3)].erase(k);
            this->table[i][j] = 0;
        }
    }
    
    // Ukoliko nijedno validno resenje nije pronadjeno za ovo polje, vracamo false
    return false;
}


// Metoda za resavanje table, kao povratnu vrednost vraca da li je tabla uspesno resena ili ne. Koristi pomocnu metodu za rekurzivno resavanje table, koju poziva nad pocetnim koordinatama polja 0,0 i prosledjuje nizove setova popunjenosti redova, kolona i podmatrica, koje prethodno popuni.
bool Sudoku9::solveTable()
{
    // Kreacija nizove setova popunjenosti redova, kolona i podmatrica i prolazak kroz sva polja table i inicijalno popunjavanje nizova setova vrednostima postavljenih polja za odgovarajuci niz
    set<int> rows[9], cols[9], boxes[9];
    
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            rows[i].insert(this->table[i][j]);
            cols[j].insert(this->table[i][j]);
            boxes[int(i / 3) * 3 + int(j / 3)].insert(this->table[i][j]);
        }
    }
    
    // Vracamo da li je uspesno resena tabla
    return this->solveTableRec(0, 0, rows, cols, boxes);
}

// Metoda za nasumicno generisanje table, ne prima parametre i ne vraca povratnu vrednost. Funkcionise tako sto nasumicno validno popuni dijagonalne podmatrice i nakon toga pokusava da resi datu tablu. Ako to ne uradi uspesno, radi sve ispocetka dok ne uspe, a kada uspe, izbrise nasumicna polja table tako da svaka podmatrica sadrzi maksimalno 6, a minimalno 1 popunjeno polje.
void Sudoku9::createTable()
{
    // Petlja koja se vrti dok ne dobijemo validno resenje table od koje pravimo generisanu tablu
    while(true)
    {
        // Prolazak kroz dijagonalne podmatrice
        for(int i = 0;i < 3;i++)
        {
            for(int j = 0;j < 3;j++)
            {
                if(i == j)
                {
                    vector<int> nums({1,2,3,4,5,6,7,8,9}); // Kreacija vektora sa dostupnim vrednostima za podmatricu
                    // Nasumicno popunjavanje podmatrice vrednostima od 1-9. Kada neku vrednost dodamo na neko polje, uklanjamo je iz vektora dostupnih vrednosti.
                    for(int k = 0;k < 3;k++)
                    {
                        for(int l = 0;l < 3;l++)
                        {
                            int index = rand() % nums.size();
                            
                            this->table[i * 3 + k][j * 3 + l] = nums[index];
                            
                            vector<int>::iterator it = nums.begin();
                            
                            for(int i = 0;i < index;i++)
                            {
                                it++;
                            }
                            
                            nums.erase(it);
                        }
                    }
                }
                else
                {
                    // Ako matrica nije dijagonalna, popunjavamo je praznim poljima (0)
                    for(int k = 0;k < 3;k++)
                    {
                        for(int l = 0;l < 3;l++)
                        {
                            this->table[i * 3 + k][j * 3 + l] = 0;
                        }
                    }
                }
            }
        }
        
        // Ako uspesno resimo ovako generisanu tablu, prolazimo kroz sve podmatrice i nasumicno izbacujemo polja
        if(this->solveTable())
        {
            for(int i = 0;i < 3;i++)
            {
                for(int j = 0;j < 3;j++)
                {
                    // Izbacujemo nasumicno odabran broj polja od 3 do 8
                    for(int numToDel = rand() % 6 + 3;numToDel > 0; numToDel--)
                    {
                        // Nasumicno trazimo popunjeno polje matrice koje cemo postaviti da bude prazno
                        while(true)
                        {
                            int ip = rand() % 3;
                            int jp = rand() % 3;
                            
                            if(this->table[i * 3 + ip][j * 3 + jp] != 0)
                            {
                                this->table[i * 3 + ip][j * 3 + jp] = 0;
                                break;
                            }
                        }
                    }
                }
            }
            
            break;
        }
    }
}

// Metoda za ispis statistickih informacija za sudoku tablu. Nema parametara, ni povratnih vrednosti. Ispisuje broj dobro postavljenih brojeva i broj pogresaka.
void Sudoku9::writeStats()
{
    cout << "Broj dobro postavljenih brojeva: " << this->goodNums << endl;
    cout << "Broj pogresaka: " << this->badNums << endl;
}

// Metoda za ispis tabele u konzolu. Ne prima nijedan parametar i ne vraca povratnu vrednost.
void Sudoku9::outputTable()
{
    // Prolazimo kroz sva polja matrice i njihove vrednosti ispisujemo na ekran. Prazno polje se predstavlja kao razmak. Redove razdvajamo sa razdvajacem (_________________) i svaki je odvojen u dodatnom novom redu.
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            // Ako je element prazno polje (0) upisujemo ga kao razmak, a ako je popunjeno polje upisujemo ga takvog kakav jeste
            if(this->table[i][j] == 0)
            {
                cout << ' ';
            }
            else
            {
                cout << this->table[i][j];
            }
            
            // svaka dva polja razdvajamo sa |
            if(j != 8)
            {
                cout << "|";
            }
        }
        
        // Svaki red razdvajamo sa _________________
        if(i != 8)
        {
            cout << "\n_________________\n";
        }
    }
    
    cout << endl << endl;
}

// Geter metoda za odredjeno polje table. Kao parametre dve celobrojne vrednosti, tj. koordinate polja, a vraca celobrojnu vrednost table na tom polju.
int Sudoku9::getTableNumberValue(const int i, const int j)
{
    return this->table[i][j];
}

// Geter metoda za brojac dobro postavljenih polja na sudoku tabli. Ne prima nijedan parametar, a vraca celobrojnu vrednost - broj dobro postavljenih polja na tabli.
int Sudoku9::getGoodNums()
{
    return this->goodNums;
}

// Geter metoda za brojac lose postavljenih polja na sudoku tabli. Ne prima nijedan parametar, a vraca celobrojnu vrednost - broj lose postavljenih polja na tabli.
int Sudoku9::getBadNums()
{
    return this->badNums;
}

// Seter metoda za odredjeno polje table. Kao parametre tri celobrojne vrednosti, koordinate polja i vrednost na koju treba postaviti polje, a ne vraca nista. Postavlja trazeno polje na zeljenu vrednost.
void Sudoku9::setTableNumberValue(const int i, const int j, const int val)
{
    this->table[i][j] = val;
}
