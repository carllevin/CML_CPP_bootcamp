#include "include/NorvigSudoku.hpp"



int main(int argc, char ** argv){
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream infile("input/SudokuListFromSlack.txt");
    std::string s;
    while(std::getline(infile, s)){
        std::cout << "\nSudoku to Solve: \n" << s << std::endl;
        solveSudoku(s);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time of execution: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
