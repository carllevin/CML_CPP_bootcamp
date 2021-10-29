#include <iostream>
#include <fstream>
#include<sstream>
#include <chrono>


#define GRID_FULL std::make_pair(9, 9)

int **InputSudoku(){
    std::string filename;
    std::cout<< "Enter the name of the Sudoku-file: " << std::endl;
    std::cin >> filename; 
    int **SudokuMatrix = new int*[9];
    for(int i = 0; i < 9; i ++){
        SudokuMatrix[i] = new int[9];
    }
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
    return SudokuMatrix;
}
// Returns a boolean which indicates whether any assigned entry
// in the specified row matches the given number. 
bool used_in_row(int grid[9][9], int row, int num)
{
	for (int col = 0; col < 9; col++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

// Returns a boolean which indicates whether any assigned entry
// in the specified column matches the given number. 
bool used_in_col(int grid[9][9], int col, int num)
{
	for (int row = 0; row < 9; row++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

// Returns a boolean which indicates whether any assigned entry
// within the specified 3x3 box matches the given number. 
bool used_in_box(int grid[9][9], int box_start_rpw, int box_start_col, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + box_start_rpw][col + box_start_col] == num) 
			{
				return true;
			}
	return false;
}

// Returns a boolean which indicates whether it will be legal to assign
// num to the given row,col location.
bool is_safe(int grid[9][9], int row, int col, int num)
{
	// Check if 'num' is not already placed in current row,
	// current column and current 3x3 box 
	return !used_in_row(grid, row, num) &&
		!used_in_col(grid, col, num) &&
		!used_in_box(grid, row - row % 3, col - col % 3, num);
}

// Searches the grid to find an entry that is still unassigned. If
// found, the reference parameters row, col will be set the location
// that is unassigned, and true is returned. If no unassigned entries
// remain, false is returned. 
std::pair<int, int> get_unassigned_location(int grid[9][9])
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (grid[row][col] == 0)
			{
				return std::make_pair(row, col);
			}
	return GRID_FULL;
}

// Takes a partially filled-in grid and attempts to assign values to
// all unassigned locations in such a way to meet the requirements
// for Sudoku solution (non-duplication across rows, columns, and boxes) 
bool solve_soduko(int grid[9][9])
{
	// If the Soduko grid has been filled, we are done
	if (GRID_FULL == get_unassigned_location(grid))
	{
		return true; 
	}

	// Get an unassigned Soduko grid location
	std::pair<int, int> row_and_col = get_unassigned_location(grid);
	int row = row_and_col.first;
	int col = row_and_col.second;

	// Consider digits 1 to 9
	for (int num = 1; num <= 9; num++)
	{
		// If placing the current number in the current
		// unassigned location is valid, go ahead
		if (is_safe(grid, row, col, num))
		{
			// Make tentative assignment
			grid[row][col] = num;

			// Do the same thing again recursively. If we go through all of the recursions, and in the end return true,
            // then all of our number placements on the Soduko grid are valid and we have fully solved it
			if (solve_soduko(grid))
			{
				return true;
			}

			// As we were not able to validly go through all 
			// of the recursions, we must have an invalid number
			// placement somewhere. Lets go back and try a 
			// different number for this particular unassigned location
			grid[row][col] = 0;
		}
	}

	// If we have gone through all possible numbers for the current unassigned
	// location, then we probably assigned a bad number early. Lets backtrack 
	// and try a different number for the previous unassigned locations.
	return false; 
}

int **SolveSudoku(int **SudokuMatrix){
    int grid[9][9];


    for(int i = 0; i < 9; i++){
        for(int j = 0; j <9; j++){
        grid[i][j] =SudokuMatrix[i][j];
        }
    }

    if (true == solve_soduko(grid)){

        for(int i = 0; i < 9; i ++){
            for( int j = 0; j < 9; j++){
                SudokuMatrix[i][j] = grid[i][j];
            }
        }
        
    }
	return SudokuMatrix; 
}

void printSudoku(int **SudokuMatrix){    
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++ ){
            std::cout << SudokuMatrix[i][j] << " "; 
        }
        std::cout<< std::endl;    
    } 
}


int main (int argc, char ** argv) { 
    //Fetch a sudoku puzzle
    int **SudokuMatrix = InputSudoku();
	//Start timer
	auto start = std::chrono::high_resolution_clock::now();
    //Print puzzle
    std::cout<< "Input puzzle:" <<std::endl;  
    printSudoku(SudokuMatrix);
    //Solve sudoku
    SudokuMatrix = SolveSudoku(SudokuMatrix);
    //Print solution 
    std::cout<< "Solution:" <<std::endl;
    printSudoku(SudokuMatrix);
	//Stop timer
	auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time of execution: " << duration.count() << " microseconds" << std::endl;

    return 0;
}