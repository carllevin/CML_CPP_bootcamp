#include "../include/NorvigSudoku.hpp"
int numberOfGuesses;

bool used_in_row(Square **grid, const int row, const int value){
	for (int col = 0; col < 9; col++)
		if (grid[row][col].getCommitValue() == value){
			return true;
		}
	return false;
}

bool used_in_col(Square **grid, const int col, const int value){
	for (int row = 0; row < 9; row++)
		if (grid[row][col].getCommitValue() == value){
			return true;
		}
	return false;
}

bool used_in_box(Square **grid, const int box_start_rpw, const int box_start_col, const int value){
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + box_start_rpw][col + box_start_col].getCommitValue()  == value){
				return true;
			}
	return false;
}

bool isSafe(Square **grid, const int row, const int col, const int num){
// Returns a boolean which indicates whether it will be legal to assign
// num to the given row,col location.

	return !used_in_row(grid, row, num) &&
		!used_in_col(grid, col, num) &&
		!used_in_box(grid, row - row % 3, col - col % 3, num);
}

bool checkforUniqueInCol(Square **grid, const int baseRow, const int baseCol, int value){
    bool check = true;
    //Check in Col
    for(int row = 0; row < 9; row++){
        if(row != baseRow){
            if(grid[row][baseCol].possibleValues.size() == 0){
                if(value == grid[row][baseCol].getCommitValue()){
                    check = false;
                    return true;
                }
            }
            for(int peerValue : grid[row][baseCol].possibleValues){
                if(value == peerValue){
                    check = false;
                    return true; 
                }
            }
        }
    }
    if (check){
        if(isSafe(grid, baseRow , baseCol, value)){ 
            grid[baseRow][baseCol].commitValue(value);
            if(!removeInPeers(grid, baseRow, baseCol, value)){
                return false;
            }
        }
    }
    return true;
}

bool checkforUniqueInRow(Square **grid, const int baseRow, const int baseCol, int value){
    bool check = true;
    for(int col = 0; col < 9; col++){
        if(col != baseCol){
            if(grid[baseRow][col].possibleValues.size() == 0){
                if(value == grid[baseRow][col].getCommitValue()){
                    check = false;
                    return true;
                }
            }
            for(int peerValue : grid[baseRow][col].possibleValues){
                if(value == peerValue){
                    check = false;
                    return true;
                }
            }
        }
    }
    if(check){
        if(isSafe(grid, baseRow , baseCol, value)){ 
            grid[baseRow][baseCol].commitValue(value);
            if(!removeInPeers(grid, baseRow, baseCol, value)){
                return false;
            }
        }
    }
    return true;
}

bool checkforUniqueInBox(Square **grid, const int baseRow, const int baseCol, int value){
    //Check in Box
    bool check = true;
    int box_start_row =  baseRow - baseRow % 3;
    int box_start_col = baseCol - baseCol % 3;
    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++){
            if(box_start_row + row != baseRow || box_start_col + col != baseCol){
                if(grid[box_start_row + row ][box_start_col + col].possibleValues.size() == 0){
                    if(value == grid[box_start_row + row ][box_start_col + col].getCommitValue()){
                        check = false;
                        return true;            
                    }
                }
                for (int peerValue : grid[box_start_row + row ][box_start_col + col].possibleValues){
                    if(value == peerValue){
                        check = false;
                        return true;
                    }              
                }  
            }
        }
    }  
    if(check){
        if(isSafe(grid, baseRow , baseCol, value)){ 
            grid[baseRow][baseCol].commitValue(value);
            if(!removeInPeers(grid, baseRow, baseCol, value)){
                return false;
            }
        }
    }
    return true;
}

bool checkForUniqueInUnits(Square **grid, const int baseRow, const int baseCol){
    if (grid[baseRow][baseCol].getNumberOfPossibles() > 1){
        for(int value : grid[baseRow][baseCol].possibleValues){
            //Check in Col
            if(!checkforUniqueInCol(grid,baseRow, baseCol, value)){
                return false;
            }
            //Check in Row
            if(!checkforUniqueInRow(grid,baseRow, baseCol, value)){
                return false;
            }
            if(!checkforUniqueInBox(grid,baseRow, baseCol, value)){
                return false;
            }
        }
    } 
    return true;
}

bool removeInBox(Square **grid, const int baseRow, const int  baseCol, const int value){
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

                if(grid[box_start_row + row][box_start_col+col].getNumberOfPossibles() == 1){
                    if(isSafe(grid, box_start_row + row, box_start_col+col, grid[box_start_row + row][box_start_col+col].possibleValues[0])){    
                        grid[box_start_row + row][box_start_col+col].commitValue(grid[box_start_row + row][box_start_col+col].possibleValues[0]);
                        if(!removeInPeers(grid,box_start_row + row,box_start_col+col, grid[box_start_row + row][box_start_col+col].getCommitValue())){
                            return false;
                        }
                    } 
                }
                /*if(!checkForUniqueInUnits(grid, box_start_row + row ,box_start_col+col)){
                    return false;
                }*/   
            }
        }
    }
    return true;
}

bool removeInCol(Square **grid, const int baseRow, const int  baseCol, const int value){
    //Remove value from peers in col-unit
    for(int row = 0; row < 9; row++){
        if(row != baseRow){
            if(grid[row][baseCol].getNumberOfPossibles() == 1 && grid[row][baseCol].possibleValues[0] == value){
                return false;
            }
            grid[row][baseCol].removePossibleValue(value); 

            if(grid[row][baseCol].getNumberOfPossibles() == 1){
                if(isSafe(grid, row , baseCol, grid[row][baseCol].possibleValues[0])){ 
                    grid[row][baseCol].commitValue(grid[row][baseCol].possibleValues[0]);
                    if(!removeInPeers(grid, row, baseCol,grid[row][baseCol].getCommitValue())){
                        return false;
                    }
                }
            }
            /*if(!checkForUniqueInUnits(grid, row,baseCol)){
                return false;
            }*/   
        }
    }
    return true;
}

bool removeInRow(Square **grid, const int baseRow, const int  baseCol, const int value){
    //Remove value from peers in row-unit
    for(int col = 0; col < 9; col++){
        if(col != baseCol){
            if(grid[baseRow][col].getNumberOfPossibles() == 1 && grid[baseRow][col].possibleValues[0] == value){
                return false;
            }
            grid[baseRow][col].removePossibleValue(value);

            if(grid[baseRow][col].getNumberOfPossibles() == 1){
                if(isSafe(grid, baseRow , col, grid[baseRow][col].possibleValues[0])){  
                    grid[baseRow][col].commitValue(grid[baseRow][col].possibleValues[0]);
                    if(!removeInPeers(grid, baseRow, col,grid[baseRow][col].getCommitValue())){
                        return false;
                    }
                }
            }
            /*if(!checkForUniqueInUnits(grid, baseRow,col)){
                return false;
            }*/
        }
    }
    return true;
}

bool removeInPeers(Square **grid, const int baseRow, const int  baseCol, const int value){
    if(!(removeInBox(grid, baseRow, baseCol, value) &&
     removeInCol(grid, baseRow, baseCol, value) &&
      removeInRow(grid, baseRow, baseCol, value))){
          return false;
      }

    //Rule no 2
    for(int i = 0; i <9; i++){
        for(int j = 0; j < 9; j++){
            if(!checkForUniqueInUnits(grid, i, j)){
                return false;
            }
        }
    }
    
    /*for(int col = 0; col < 9; col++){
        checkForUniqueInUnits(grid, baseRow, col);
    }
    for(int row = 0; row <9; row++){
        checkForUniqueInUnits(grid, row, baseCol);
    }
    int box_start_row =  baseRow - baseRow % 3;
    int box_start_col = baseCol - baseCol % 3;
    for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
            checkForUniqueInUnits(grid, box_start_row+row, box_start_col+col);
        }
    }*/
    return true;
}

std::pair<int, int> getLocationOfLeastPossibles(Square **grid){
    int numberOfPossibles = 10;
    std::pair<int, int> leastPossiblesSquare;
    bool leastFound = false;
	for (int row = 0; row < 9 && !leastFound; row++)
		for (int col = 0; col < 9 && !leastFound; col++)
			if (grid[row][col].getNumberOfPossibles() < numberOfPossibles && grid[row][col].getNumberOfPossibles() >  0){
                numberOfPossibles = grid[row][col].getNumberOfPossibles();
				leastPossiblesSquare = std::make_pair(row, col);
			}
            if(numberOfPossibles == 2){
                leastFound = true;
            }

    if(numberOfPossibles == 10){
        leastPossiblesSquare = std::make_pair(10, 10);
    } 
    return leastPossiblesSquare;
}

bool guessSudoku(Square **grid){
	// If the Soduko grid has been filled, we are done
	if (getLocationOfLeastPossibles(grid).first == 10){
		return true; 
	}

	// Get the square with least possible solutions
	std::pair<int, int> row_and_col = getLocationOfLeastPossibles(grid);
	int row = row_and_col.first;
	int col = row_and_col.second;
    
    //Do a backup of the grid
    Square backupGrid[9][9];
    for(int i = 0; i <9; i++){
        for(int j = 0; j < 9; j++){
            backupGrid[i][j] = grid[i][j];
        }
    }
    
    //Start guessing
    std::vector<int> tempVector = grid[row][col].possibleValues;
    for(int value : tempVector){
        if (isSafe(grid, row, col, value)){
            numberOfGuesses ++;
            grid[row][col].commitValue(value);
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
    return false;
}

int parseAndConstraintPropagation(Square **grid, std::string s){
    //Parse through puzzle and apply rule (1) & (2)
    int row = 0;
    int col = 0;
    for(char c : s){
        if(c != '.'){
            grid[row][col].commitValue(c - '0');  
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

    return countOfUnCommitted;
}

void sudokuSearch(Square **grid){
    numberOfGuesses = 0;
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
    std::cout << "It took " << numberOfGuesses << " guesses to solve the sudoku."<< std::endl;    
    } else {
        std::cout << "Could not find a solution " << std::endl;
    }   
}

void solveSudoku(std::string s){
    
    Square **grid = new Square*[9];
    for(int i = 0; i < 9; i++){
        grid[i] = new Square[9];
    }
    
    //If only constraint propagation is not solving the sudoku begin to search
    if(parseAndConstraintPropagation(grid, s) > 0){
        sudokuSearch(grid);
    }
    
    for(int i = 0; i < 9; i++){
        delete [] grid[i];
    }
    delete [] grid;
}

void Square::printPossibleValues(){
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
}


