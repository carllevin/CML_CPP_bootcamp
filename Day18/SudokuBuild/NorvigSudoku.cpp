#include "NorvigSudoku.hpp"
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

                if(grid[box_start_row + row][box_start_col+col].getNumberOfPossibles() == 1){
                    if(isSafe(grid, box_start_row + row, box_start_col+col, grid[box_start_row + row][box_start_col+col].possibleValues[0])){    
                        grid[box_start_row + row][box_start_col+col].commitValue(grid[box_start_row + row][box_start_col+col].possibleValues[0]);
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

            if(grid[row][baseCol].getNumberOfPossibles() == 1){
                if(isSafe(grid, row , baseCol, grid[row][baseCol].possibleValues[0])){ 
                    grid[row][baseCol].commitValue(grid[row][baseCol].possibleValues[0]);
                    if(!removeInPeers(grid, row, baseCol,grid[row][baseCol].getCommitValue())){
                        return false;
                    }
                }
            }
            if(!checkForUniqueInUnits(grid, row,baseCol)){
                return false;
            }   
        }
    }

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
            if(!checkForUniqueInUnits(grid, baseRow,col)){
                return false;
            }
        }
    }
    return true;
}

std::pair<int, int> getLocationOfLeastPossibles(Square **grid){
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
	if (GRID_FULL == getLocationOfLeastPossibles(grid)){
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