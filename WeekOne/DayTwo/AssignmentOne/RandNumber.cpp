#include <iostream>
#include <cstdlib>
#include <ctime>



int main() {


    unsigned int a;
    int n, m;
    std::cout << "Enter the size of the array" << std::endl;
    std::cin >> n;   
    int *arr = new int[n];
    int arr2[m];
    std::cout << "Enter a positive number" << std::endl;
    std::cin >> a;
    
    std::cout << "With pointer" << std::endl;
    for (int i = 0; i < n; i++){
        unsigned int randomNumber = (rand() % a);
        *(arr+i) = randomNumber;
        std::cout << "[" << i << "]" << arr[i] << "\n";       
    }    
    std::cout << "Without pointer" << std::endl;
    for (int i = 0; i < m; i++){
        unsigned int randomNumber = (rand() % a);
        arr2[i] = randomNumber;
        std::cout << "[" << i << "]" << arr2[i] << "\n";       
    }    
    delete arr;
}