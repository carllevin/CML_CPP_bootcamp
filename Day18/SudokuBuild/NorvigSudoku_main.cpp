#include "NorvigSudoku.hpp"



int main(int argc, char ** argv){
    auto start = std::chrono::high_resolution_clock::now();
    
    std::ifstream infile("SudokuListFromSlack.txt");
    std::string s;
    while(std::getline(infile, s)){
        numberOfGuesses = 0;
        std::cout << "\nSudoku to Solve: \n" << s << std::endl;

        Square **grid = new Square*[9];
        for(int i = 0; i < 9; i++){
            grid[i] = new Square[9];
        }
        
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
            std::cout << "It took " << numberOfGuesses << " guesses to solve the sudoku."<< std::endl;    
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
