//
//  Sudoku9.cpp
//  Sudoku
//
//  Created by Veselin Roganovic on 24.12.23..
//

#include "Sudoku9.hpp"
#include <fstream>

Sudoku9::Sudoku9() : goodNums(0), badNums(0)
{
    this->createTable();
}

Sudoku9::Sudoku9(const string filePath) : goodNums(0), badNums(0)
{
    this->loadTable(filePath);
}

void Sudoku9::loadTable(const string filePath)
{
    ifstream file;
    
    file.open(filePath);
    
    string inputLine;
    
    int row = 0;
    
    while(getline(file, inputLine))
    {
        if(inputLine[0] != '_')
        {
            for(int i = 0;i < 9;i++)
            {
                if(inputLine[i * 2] == 'O')
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

void Sudoku9::saveTable(const string filePath)
{
    ofstream file;
    
    file.open(filePath);
    
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            if(this->table[i][j] == 0)
            {
                file << 'O';
            }
            else
            {
                file << this->table[i][j];
            }
            
            if(j != 8)
            {
                file << "|";
            }
        }
        
        if(i != 8)
        {
            file << "\n_________________\n";
        }
    }
    
    file.close();
}

bool Sudoku9::isOkay()
{
    set<int> elems;
    set<pair<int, int>> badElems;
    int numZeroes = 0;
    
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
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
        
        elems.clear();
    }
    
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
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
        
        elems.clear();
    }
    
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            for(int k = 0;k < 3;k++)
            {
                for(int l = 0;l < 3;l++)
                {
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
            
            elems.clear();
        }
    }
    
    this->badNums = int(badElems.size());
    this->goodNums = 81 - this->badNums - numZeroes;
    
    return badElems.empty();
}

bool Sudoku9::solveTableRec(int i, int j, set<int> (&rows)[9], set<int> (&cols)[9], set<int> (&boxes)[9])
{
    if(j == 9)
    {
        if(i == 8) return true;
        
        j = 0;
        i++;
    }
 
    if(this->table[i][j])
    {
        return solveTableRec(i, j + 1, rows, cols, boxes);
    }
    
    for(int k = 1; k <= 9; k++)
    {
        if((rows[i].find(k) == rows[i].end()) && (cols[j].find(k) == cols[j].end()) && (boxes[int(i / 3) * 3 + int(j / 3)].find(k) == boxes[int(i / 3) * 3 + int(j / 3)].end()))
        {
            this->table[i][j] = k;
            rows[i].insert(k);
            cols[j].insert(k);
            boxes[int(i / 3) * 3 + int(j / 3)].insert(k);
 
            if(solveTableRec(i, j + 1, rows, cols, boxes)) return true;
 
            rows[i].erase(k);
            cols[j].erase(k);
            boxes[int(i / 3) * 3 + int(j / 3)].erase(k);
            this->table[i][j] = 0;
        }
    }
    
    return false;
}

bool Sudoku9::solveTable()
{
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
    
    return this->solveTableRec(0, 0, rows, cols, boxes);
}

void Sudoku9::createTable()
{
    while(true)
    {
        for(int i = 0;i < 3;i++)
        {
            for(int j = 0;j < 3;j++)
            {
                if(i == j)
                {
                    vector<int> nums({1,2,3,4,5,6,7,8,9});
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
        
        if(this->solveTable())
        {
            for(int i = 0;i < 3;i++)
            {
                for(int j = 0;j < 3;j++)
                {
                    for(int numToDel = rand() % 6 + 3;numToDel > 0; numToDel--)
                    {
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

void Sudoku9::writeStats()
{
    cout << "Broj dobro postavljenih brojeva: " << this->goodNums << endl;
    cout << "Broj pogresaka: " << this->badNums << endl;
}

int Sudoku9::getTableNumberValue(const int i, const int j)
{
    return this->table[i][j];
}

int Sudoku9::getGoodNums()
{
    return this->goodNums;
}

int Sudoku9::getBadNums()
{
    return this->badNums;
}

void Sudoku9::setTableNumberValue(const int i, const int j, const int val)
{
    this->table[i][j] = val;
}
