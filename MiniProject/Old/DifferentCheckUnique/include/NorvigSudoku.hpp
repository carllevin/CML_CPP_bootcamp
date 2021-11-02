#ifndef NORVIGSUDOKU_HPP
#define NORVIGSUDOKU_HPP

#include <iostream>
#include <fstream>
#include<sstream>
#include<vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

class Square{
    public:
        std::vector<int> possibleValues;
        int commitVal;
        Square(){
            possibleValues.assign({1,2,3,4,5,6,7,8,9});
            this->commitVal = 0;
        }
        void removePossibleValue(int value){
            possibleValues.erase(std::remove(possibleValues.begin(), possibleValues.end(), value), possibleValues.end());
        }
        void printPossibleValues();
        
        void commitValue(int value){
            this->commitVal = value;
            this->possibleValues.clear();
        }
        int getNumberOfPossibles(){
            return possibleValues.size();
        }
};

bool used_in_row(Square **grid, const int row, const int value);

bool used_in_col(Square **grid, const int col, const int value);

bool used_in_box(Square **grid, const int box_start_rpw, const int box_start_col, const int value);

bool isSafe(Square **grid, const int row, const int col, const int num);

bool checkforUniqueInCol2(Square **grid, const int value);

bool checkforUniqueInRow2(Square **grid, const int value);

bool checkforUniqueInBox2(Square **grid, const int value);

bool checkForUniqueInUnits2(Square **grid);

bool checkforUniqueInCol(Square **grid, const int baseRow, const int baseCol, int value);

bool checkforUniqueInRow(Square **grid, const int baseRow, const int baseCol, int value);

bool checkforUniqueInBox(Square **grid, const int baseRow, const int baseCol, int value);

bool checkForUniqueInUnits(Square **grid, const int baseRow, const int baseCol);

bool removeInBox(Square **grid, const int baseRow, const int  baseCol, const int value);

bool removeInCol(Square **grid, const int baseRow, const int  baseCol, const int value);

bool removeInRow(Square **grid, const int baseRow, const int  baseCol, const int value);

bool removeInPeers(Square **grid, const int baseRow, const int  baseCol, const int value);

std::pair<int, int> getLocationOfLeastPossibles(Square **grid);

bool guessSudoku(Square **grid, int numberOfGuesses);

int parseAndConstraintPropagation(Square **grid, std::string s);

void sudokuSearch(Square **grid);

void solveSudoku(std::string s);


#endif // NORVIGSUDOKU_HPP