#ifndef NORVIGSUDOKU_HPP
#define NORVIGSUDOKU_HPP

#include <iostream>
#include <fstream>
#include<sstream>
#include<vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

#define GRID_FULL std::make_pair(10, 10)
extern int numberOfGuesses;

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
        };
        void printPossibleValues();
        
        void commitValue(int value){
            this->commitVal = value;
            this->possibleValues.clear();
        }
        int getCommitValue(){
            return commitVal;
        }
        int getNumberOfPossibles(){
            return possibleValues.size();
        };
};

bool used_in_row(Square **grid, const int row, const int value);

bool used_in_col(Square **grid, const int col, const int value);

bool used_in_box(Square **grid, const int box_start_rpw, const int box_start_col, const int value);

bool isSafe(Square **grid, const int row, const int col, const int num);

bool checkForUniqueInUnits(Square **grid, const int baseRow, const int baseCol);

bool removeInPeers(Square **grid, const int baseRow, const int  baseCol, const int value);

std::pair<int, int> getLocationOfLeastPossibles(Square **grid);

bool guessSudoku(Square **grid);




#endif // NORVIGSUDOKU_HPP