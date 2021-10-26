#include <iostream>
#include <fstream>
#include<sstream>
#include<vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

#define GRID_FULL std::make_pair(10, 10)

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
        void printPossibleValues(){
            if (possibleValues.size() > 0){
                for(int i = 0; i < possibleValues.size(); i++){
                    std::cout << possibleValues[i];
                }
            } else {
                std::cout << this->commitVal;
            }
            int count = 0;
            while(count < 9 - possibleValues.size()){
                std::cout << " ";
                count++;
            }
            if(possibleValues.size()>0){
                std::cout << " ";
            }
        };
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

bool used_in_row(Square **grid, int row, int value){
	for (int col = 0; col < 9; col++)
		if (grid[row][col].getCommitValue() == value){
			return true;
		}
	return false;
}

bool used_in_col(Square **grid, int col, int value){
	for (int row = 0; row < 9; row++)
		if (grid[row][col].getCommitValue() == value){
			return true;
		}
	return false;
}

bool used_in_box(Square **grid, int box_start_rpw, int box_start_col, int value){
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + box_start_rpw][col + box_start_col].getCommitValue()  == value){
				return true;
			}
	return false;
}

bool isSafe(Square **grid, int row, int col, int num){
// Returns a boolean which indicates whether it will be legal to assign
// num to the given row,col location.

	return !used_in_row(grid, row, num) &&
		!used_in_col(grid, col, num) &&
		!used_in_box(grid, row - row % 3, col - col % 3, num);
}

bool removeInPeers(Square **grid, const int baseRow, const int  baseCol, const int value);

bool checkForUniqueInUnits(Square **grid, const int baseRow, const int baseCol){
    if (grid[baseRow][baseCol].getNumberOfPossibles() > 1){
        for(int value : grid[baseRow][baseCol].possibleValues){
            bool check = true;
            //Check in Col
            for(int row = 0; row < 9; row++){
                if(row != baseRow){
                    if(grid[row][baseCol].possibleValues.size()==0){
                        if(value == grid[row][baseCol].getCommitValue()){
                            check = false;
                            goto endCheckCol;
                        }
                    }
                    for(int peerValue : grid[row][baseCol].possibleValues){
                        if(value == peerValue){
                            check = false;
                            goto endCheckCol;
                            
                        }
                    }
                }
            }
            endCheckCol:
            if (check){
                if(isSafe(grid, baseRow , baseCol, value)){ 
                    grid[baseRow][baseCol].commitValue(value);
                    grid[baseRow][baseCol].clearPossibles();
                    if(!removeInPeers(grid, baseRow, baseCol, value)){
                        return false;
                    }
                    
                }
                return true;
            }
            //Check in Row
            check = true;
            for(int col = 0; col < 9; col++){
                if(col != baseCol){
                    if(grid[baseRow][col].possibleValues.size() == 0){
                        if(value == grid[baseRow][col].getCommitValue()){
                            check = false;
                            goto endCheckRow;
                        }
                    }
                    for(int peerValue : grid[baseRow][col].possibleValues){
                        if(value == peerValue){
                            check = false;
                            goto endCheckRow;
                        }
                    }
                }
            }
            endCheckRow:
            if(check){
                if(isSafe(grid, baseRow , baseCol, value)){ 
                    grid[baseRow][baseCol].commitValue(value);
                    grid[baseRow][baseCol].clearPossibles();
                    if(!removeInPeers(grid, baseRow, baseCol, value)){
                        return false;
                    }
                }
                return true;
            }
            //Check in Box
            check = true;
            int box_start_row =  baseRow - baseRow % 3;
            int box_start_col = baseCol - baseCol % 3;
            for (int row = 0; row < 3; row++){
		        for (int col = 0; col < 3; col++){
                    if(box_start_row + row != baseRow || box_start_col + col != baseCol){
                        if(grid[box_start_row + row ][box_start_col + col].possibleValues.size() == 0){
                            if(value == grid[box_start_row + row ][box_start_col + col].getCommitValue()){
                                check = false;
                                goto endCheckBox;            
                            }
                        }
                        for (int peerValue : grid[box_start_row + row ][box_start_col + col].possibleValues){
                                if(value == peerValue){
                                    check = false;
                                    goto endCheckBox;
                                }              
                        }  
                    }
                }
            }
            endCheckBox:   
            if(check){
                if(isSafe(grid, baseRow , baseCol, value)){ 
                    grid[baseRow][baseCol].commitValue(value);
                    grid[baseRow][baseCol].clearPossibles();
                    if(!removeInPeers(grid, baseRow, baseCol, value)){
                        return false;
                    }
                }
                return true;
            }
            
        }
    } 
    return true;
}

bool removeInPeers(Square **grid, const int baseRow, const int  baseCol, const int value){
    
    //Remove value from peers in box-unit
    int box_start_row =  baseRow - baseRow % 3;
    int box_start_col = baseCol - baseCol % 3;

    for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
            if(box_start_row + row != baseRow || box_start_col + col != baseCol){
                if(grid[box_start_row + row ][box_start_col+col].getNumberOfPossibles() == 1 && grid[box_start_row + row ][box_start_col+col].possibleValues[0] == value ){
                    return false;
                }                
                grid[box_start_row + row ][box_start_col+col].removePossibleValue(value);
                /*if(!checkForUniqueInUnits(grid, box_start_row + row ,box_start_col+col)){
                    return false;
                }*/

                if(grid[box_start_row + row][box_start_col+col].getNumberOfPossibles() == 1){
                    if(isSafe(grid, box_start_row + row, box_start_col+col, grid[box_start_row + row][box_start_col+col].possibleValues[0])){    
                        grid[box_start_row + row][box_start_col+col].commitValue(grid[box_start_row + row][box_start_col+col].possibleValues[0]);
                        grid[box_start_row + row][box_start_col+col].clearPossibles();
                        if(!removeInPeers(grid,box_start_row + row,box_start_col+col, grid[box_start_row + row][box_start_col+col].getCommitValue())){
                            return false;
                        }
                    } 
                }
                if(!checkForUniqueInUnits(grid, box_start_row + row ,box_start_col+col)){
                    return false;
                }   
            }
        }
    }

    //Remove value from peers in col-unit
    for(int row = 0; row < 9; row++){
        if(row != baseRow){
            if(grid[row][baseCol].getNumberOfPossibles() == 1 && grid[row][baseCol].possibleValues[0] == value){
                return false;
            }
            grid[row][baseCol].removePossibleValue(value);
            /*if(!checkForUniqueInUnits(grid, row,baseCol)){
                return false;
            };*/  

            if(grid[row][baseCol].getNumberOfPossibles() == 1){
                if(isSafe(grid, row , baseCol, grid[row][baseCol].possibleValues[0])){ 
                    grid[row][baseCol].commitValue(grid[row][baseCol].possibleValues[0]);
                    grid[row][baseCol].clearPossibles();  
                    if(!removeInPeers(grid, row, baseCol,grid[row][baseCol].getCommitValue())){
                        return false;
                    }
                }
            }
            if(!checkForUniqueInUnits(grid, row,baseCol)){
                return false;
            };    
        }
    }

    //Remove value from peers in row-unit
    for(int col = 0; col < 9; col++){
        if(col != baseCol){
            if(grid[baseRow][col].getNumberOfPossibles() == 1 && grid[baseRow][col].possibleValues[0] == value){
                return false;
            }
            grid[baseRow][col].removePossibleValue(value);
            /*if(!checkForUniqueInUnits(grid, baseRow,col)){
                return false;
            }*/

            if(grid[baseRow][col].getNumberOfPossibles() == 1){
                if(isSafe(grid, baseRow , col, grid[baseRow][col].possibleValues[0])){  
                    grid[baseRow][col].commitValue(grid[baseRow][col].possibleValues[0]);
                    grid[baseRow][col].clearPossibles();
                    if(!removeInPeers(grid, baseRow, col,grid[baseRow][col].getCommitValue())){
                        return false;
                    }
                }
            }
            if(!checkForUniqueInUnits(grid, baseRow,col)){
                return false;
            }
        }
    }
    return true;
}

std::pair<int, int> getLeastPossiblesLocation(Square **grid){
    int numberOfPossibles = 10;
    std::pair<int, int> beginPair;
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (grid[row][col].getNumberOfPossibles() < numberOfPossibles && grid[row][col].getNumberOfPossibles() >  0){
                numberOfPossibles = grid[row][col].getNumberOfPossibles();
				beginPair = std::make_pair(row, col);
			}

    if(numberOfPossibles == 10){
        return GRID_FULL;
    } else {
        return beginPair;
    }
}

bool guessSudoku(Square **grid){
	// If the Soduko grid has been filled, we are done
	if (GRID_FULL == getLeastPossiblesLocation(grid)){
		return true; 
	}

	// Get the square with least possible solutions
	std::pair<int, int> row_and_col = getLeastPossiblesLocation(grid);
	int row = row_and_col.first;
	int col = row_and_col.second;
    
    //Do a backup of grid
    Square backupGrid[9][9];
    /*
    Square **backupGrid = new Square*[9];

    for(int i = 0; i < 9; i++){
        backupGrid[i] = new Square[9];

    }*/
    
    for(int i = 0; i <9; i++){
        for(int j = 0; j < 9; j++){
            backupGrid[i][j] = grid[i][j];
        }
    }
    
    //Start guessing
    std::vector<int> tempVector = grid[row][col].possibleValues;
    for(int value : tempVector){
        if (isSafe(grid, row, col, value)){
            grid[row][col].commitValue(value);
            grid[row][col].clearPossibles();
            if(removeInPeers(grid, row, col, value)){
                if(guessSudoku(grid)){
                    return true;
                }            
            }
            
            //Retrieve from backup
            for(int i = 0; i <9; i++){
                for(int j = 0; j < 9; j++){
                    grid[i][j] = backupGrid[i][j];    
                    
                }    
            }        
        }
    }
    /*
    for(int i = 0; i < 9; i++){
        delete [] backupGrid[i];
    }
    delete [] backupGrid;*/
   
    return false;
}

int main(int argc, char ** argv){
    auto start = std::chrono::high_resolution_clock::now();

    //std::string s = "...8.....789.1...6.....61....7....5.5.87.93.4.4....2....32.....8...7.439.....1...";
    //std::string s = "..............3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9";
    
    std::ifstream infile("SudokuListFromSlack.txt");
    std::string s;
    while(std::getline(infile, s)){
        
        Square **grid = new Square*[9];
        for(int i = 0; i < 9; i++){
            grid[i] = new Square[9];
        }
        std::cout << "\nSudoku to Solve: \n" << s << std::endl;
        //Parse through puzzle and apply rule (1) & (2)
        int row = 0;
        int col = 0;
        for(char c : s){
            if(c != '.'){
                grid[row][col].commitValue(c - '0');
                grid[row][col].clearPossibles();    
                if(removeInPeers(grid,row,col,grid[row][col].getCommitValue())){

                }  
            }
            col ++;
            if(col == 9){
                row++;
                col = 0;
            }
        }

        int countOfUnCommitted = 0;

        std::cout << "------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "After applying rule (1) & (2) "<< std::endl;
        for(int i=0; i<9; i++){
            for(int j=0; j < 9; j++){
                grid[i][j].printPossibleValues();
                std::cout << " . ";
                if(grid[i][j].getNumberOfPossibles() > 0){
                    countOfUnCommitted ++;
                }
            }
            std::cout << std::endl;
        }

        //Guess sudoku
        if(countOfUnCommitted > 0){
            if(guessSudoku(grid)){
                std::cout << "------------------------------------------------------------------------------------------------------------" << std::endl;
                std::cout << "After guessing "<< std::endl;
                for(int i=0; i<9; i++){
                    for(int j=0; j < 9; j++){
                        grid[i][j].printPossibleValues();
                        std::cout << " . ";
                    }
                    std::cout << std::endl;
                }
            } else {
                std::cout << "Could not find a solution " << std::endl;
            }
        }
        for(int i = 0; i < 9; i++){
            delete [] grid[i];
        }
        delete [] grid;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time of execution: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
