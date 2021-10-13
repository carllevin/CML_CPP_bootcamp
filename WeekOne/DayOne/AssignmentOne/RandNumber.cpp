#include <iostream>
#include <cstdlib>
#include <ctime>



int main() {


    unsigned int a, M[8][9][11];
    std::cout << "Enter a positive number" << std::endl;
    std::cin >> a;
    

    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 9; j++ ){
            for(int k = 0; k < 11; k++){
                unsigned int randomNumber = (rand() % a);
                M[i][j][k] = randomNumber;
                std::cout << "[" << i << "][" << j << "][" << k << "] = " << M[i][j][k] << "\n";
            }
            

        }
    }    
}