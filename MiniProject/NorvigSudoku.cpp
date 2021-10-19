#include <iostream>
#include <fstream>
#include<sstream>
#include<vector>
#include <algorithm>
#include <iomanip>

class Square{
    public:
        std::vector<int> possibleValues;
        int commitVal;
        Square(){
            possibleValues.assign({1,2,3,4,5,6,7,8,9});
        }
        void removePossibleValue(int value){
            possibleValues.erase(std::remove(possibleValues.begin(), possibleValues.end(), value), possibleValues.end());
        };

        void printPossibleValues(){
            if (possibleValues.size() > 0){
                for(int i = 0; i < possibleValues.size(); i++){
                    std::cout << possibleValues[i];
                }
            } else {
                std::cout << this->commitVal;
            }
            int count = 0;
            while(count < 8 - possibleValues.size()){
                std::cout << " ";
                count++;
            }
            if(possibleValues.size()>0){
                std::cout << " ";
            }
        };
        void commitValue(int value){
            this->commitVal = value;
        }
        int getCommitValue(){
            return commitVal;
        }

        int getNumberOfPossibles(){
            return possibleValues.size();
        };
        void clearPossibles(){
            this->possibleValues.clear();
        } 
};

void InputSudoku(int (&SudokuMatrix)[9][9]){
    std::string filename;
    std::cout<< "Enter the name of the Sudoku-file: " << std::endl;
    std::cin >> filename; 

    std::string STRING;
	std::ifstream infile;
    int row = 0;
	infile.open (filename);
        while(getline(infile,STRING)) // To get you all the lines.
        {   
            int col = 0;
            std::stringstream str_strm; 
            str_strm << STRING;

            while(col <= 8){
                std::string temp_str;
                int temp_int;
                str_strm >> temp_str;
                temp_int = stoi(temp_str);
                SudokuMatrix[row][col] = temp_int;
                col++;
            }
	        row++;   
        }
    std::cout<< std::endl;
    infile.close();
}

void removeInPeers(Square (&grid)[9][9], const int baseRow,  const int  baseCol,  const int value);

void checkForUniqueInUnits(Square (&grid)[9][9], const int baseRow, const int baseCol){
    if (grid[baseRow][baseCol].getNumberOfPossibles() > 1){
        for(int value : grid[baseRow][baseCol].possibleValues){
            bool check = true;
            //Check in Col
            for(int row = 0; row < 9; row++){
                if(row != baseRow){
                    if(grid[row][baseCol].possibleValues.size()==0){
                        if(value == grid[row][baseCol].getCommitValue()){
                            check = false;
                            goto checkRow;
                        }
                    }
                    for(int peerValue : grid[row][baseCol].possibleValues){
                        if(value == peerValue){
                            check = false;
                            goto checkRow;
                            //return;
                        }
                    }
                }
            }
            if (check){
                grid[baseRow][baseCol].commitValue(value);
                grid[baseRow][baseCol].clearPossibles();
                removeInPeers(grid, baseRow, baseCol, value);
                return;
            }
            //Check in Row
            checkRow:
            check = true;
            for(int col = 0; col < 9; col++){
                if(col != baseCol){
                    if(grid[baseRow][col].possibleValues.size() == 0){
                        if(value == grid[baseRow][col].getCommitValue()){
                            check = false;
                            goto checkBox;
                        }
                    }
                    for(int peerValue : grid[baseRow][col].possibleValues){
                        if(value == peerValue){
                            check = false;
                            goto checkBox;
                        }
                    }
                }
            }
            if(check){
                grid[baseRow][baseCol].commitValue(value);
                grid[baseRow][baseCol].clearPossibles();
                removeInPeers(grid, baseRow, baseCol, value);
                return;
            }
            //Check in Box
            
            checkBox:
            check = true;
            int box_start_row =  baseRow - baseRow % 3;
            int box_start_col = baseCol - baseCol % 3;
            for (int row = 0; row < 3; row++){
		        for (int col = 0; col < 3; col++){
                    if(box_start_row + row != baseRow || box_start_col + col != baseCol){
                        if(grid[box_start_row + row ][box_start_col + col].possibleValues.size() == 0){
                            if(value == grid[box_start_row + row ][box_start_col + col].getCommitValue()){
                                check = false;            
                            }
                        }
                        for (int peerValue : grid[box_start_row + row ][box_start_col + col].possibleValues){
                                if(value == peerValue){
                                    check = false;
                                }              
                        }  
                    }
                }
            }    
            if(check){
                grid[baseRow][baseCol].commitValue(value);
                grid[baseRow][baseCol].clearPossibles();
                removeInPeers(grid, baseRow, baseCol, value);
                return;
            }
        }
    
    } 

}

void removeInPeers(Square (&grid)[9][9], const int baseRow, const int  baseCol, const int value){
    //Applying rule (1): 
    //Remove value from peers in box-unit
    int box_start_row =  baseRow - baseRow % 3;
    int box_start_col = baseCol - baseCol % 3;

    for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
            if(box_start_row + row != baseRow || box_start_col + col != baseCol){
                grid[box_start_row + row ][box_start_col+col].removePossibleValue(value);
                checkForUniqueInUnits(grid, box_start_row + row ,box_start_col+col);

                if(grid[box_start_row + row][box_start_col+col].getNumberOfPossibles() == 1){
                    grid[box_start_row + row][box_start_col+col].commitValue(grid[box_start_row + row][box_start_col+col].possibleValues[0]);
                    grid[box_start_row + row][box_start_col+col].clearPossibles();

                    removeInPeers(grid,box_start_row + row,box_start_col+col, grid[box_start_row + row][box_start_col+col].getCommitValue());
                } 
            }
        }
    }

    //Remove value from peers in col-unit
    for(int row = 0; row < 9; row++){
        if(row != baseRow){
           grid[row][baseCol].removePossibleValue(value);
           checkForUniqueInUnits(grid, row,baseCol);

           if(grid[row][baseCol].getNumberOfPossibles() == 1){
               grid[row][baseCol].commitValue(grid[row][baseCol].possibleValues[0]);
               grid[row][baseCol].clearPossibles();  
               removeInPeers(grid, row, baseCol,grid[row][baseCol].getCommitValue());
           }
        }
    }

    //Remove value from peers in row-unit
    for(int col = 0; col < 9; col++){
        if(col != baseCol){
           grid[baseRow][col].removePossibleValue(value);
           checkForUniqueInUnits(grid, baseRow,col);

           if(grid[baseRow][col].getNumberOfPossibles() == 1){
               grid[baseRow][col].commitValue(grid[baseRow][col].possibleValues[0]);
               grid[baseRow][col].clearPossibles();
               removeInPeers(grid, baseRow, col,grid[baseRow][col].getCommitValue());
           }

        }
    }
    
}

int main(int argc, char ** argv){
    int SudokuMatrix[9][9];
    InputSudoku(SudokuMatrix);
    Square grid[9][9];

    //Applying rule (1) & (2)
    for (int i=0; i<9; i++){
        for(int j=0; j < 9; j++){
            if(SudokuMatrix[i][j] != 0){
                grid[i][j].commitValue(SudokuMatrix[i][j]);
                grid[i][j].clearPossibles();    
                removeInPeers(grid,i,j,grid[i][j].getCommitValue());    
            }
        }
    }

    /*
    std::cout << "After applying rule (1) "<< std::endl;
    for(int i=0; i<9; i++){
        for(int j=0; j < 9; j++){
            grid[i][j].printPossibleValues();
            std::cout << " . ";
        }
        std::cout << std::endl;
    }
    
    //Applying rule (2)
    for (int i=0; i<9; i++){
        for(int j=0; j < 9; j++){
            checkForUniqueInUnits(grid, i,j);
        }
    }*/
    
    std::cout << "------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "After applying rule (1) & (2) "<< std::endl;
    for(int i=0; i<9; i++){
        for(int j=0; j < 9; j++){
            grid[i][j].printPossibleValues();
            std::cout << " . ";
        }
        std::cout << std::endl;
    }

    return 0;
}






